#!/usr/bin/env python3
"""Verify preservation of supplied lab sources/data, without executing originals."""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import sys
import xml.etree.ElementTree as ET
import zipfile

ROOT = Path(__file__).resolve().parents[1]
ARCHIVE = ROOT / "source_archive"
MANIFEST = ARCHIVE / "source-manifest.json"
DOC_EXT = {".pdf", ".docx", ".doc", ".png", ".jpg", ".jpeg", ".pptx", ".ppt"}
STATUSES = {
    "original_source_or_local_draft_unverified", "original_local_data_unverified",
    "program_generated_local_output_unverified", "original_project_configuration_unverified",
    "original_personal_membership_data_anonymized", "original_data_archive_privacy_transformed",
}
TOKEN = re.compile(
    rb'//[^\r\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_][A-Za-z_0-9]*|\d+(?:\.\d*)?(?:[eE][+-]?\d+)?|[^\s]', re.M)


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def nonliteral_digest(data: bytes) -> str:
    values = [m.group() for m in TOKEN.finditer(data)
              if not m.group().startswith((b"//", b"/*"))]
    return digest(b"\0".join(b"<STRING_LITERAL>" if token.startswith(b'"') else token for token in values))


def safe_path(path: Path) -> Path:
    resolved = path.resolve()
    if not resolved.is_relative_to(ROOT):
        raise ValueError("An archive reference escapes the repository")
    return resolved


def classification(path: Path, data: bytes) -> str:
    if path.suffix.lower() in {".layout", ".depend"}:
        return "codeblocks_generated_ide_state"
    if data.startswith(b"MZ"):
        return "student_pe_compiled_executable"
    if path.suffix.lower() in {".o", ".obj"}:
        return "student_compiled_object"
    if path.suffix.lower() in DOC_EXT:
        return "document_or_image_separate_manifest"
    return "source_or_small_data"


def check(source_root: Path | None = None) -> dict:
    manifest = json.loads(MANIFEST.read_text(encoding="utf-8"))
    seen = set()
    code_count = output_count = 0
    declared_gaps = {(g["project"], g["reference"]) for g in manifest["original_project_reference_gaps"]}
    observed_gaps = set()
    for item in manifest["files"]:
        name = item["path"]
        path = safe_path(ROOT / name)
        if not path.is_relative_to(ARCHIVE) or name in seen:
            raise ValueError("Duplicate or misplaced archived source file")
        seen.add(name)
        data = path.read_bytes()
        if digest(data) != item["archived_sha256"] or len(data) != item["size"]:
            raise ValueError(f"Archived content changed: {name}")
        if not re.fullmatch(r"[0-9a-f]{64}", item["source_sha256"]):
            raise ValueError(f"Invalid original-source hash: {name}")
        if not item["content_transformed"] and item["source_sha256"] != item["archived_sha256"]:
            raise ValueError(f"Incorrect content-transformation flag: {name}")
        if item["status"] not in STATUSES:
            raise ValueError(f"Unclassified archive status: {name}")
        if re.search(r"(?<!\d)\d{9}(?!\d)", name + item["source_filename_sanitized"]):
            raise ValueError(f"A source filename contains a student ID: {name}")
        if classification(path, data) != "source_or_small_data":
            raise ValueError(f"Compiled/cache/document payload in source-only archive: {name}")
        if "code_kind" in item:
            code_count += 1
            if nonliteral_digest(data) != item["original_cpp_nonliteral_token_sha256"]:
                raise ValueError(f"Original algorithm tokens changed: {name}")
            # Require an actual C++ drive prefix, rather than mistaking a prompt
            # ending in a letter and ':\n' for an absolute Windows pathname.
            if re.search(rb'"[A-Za-z]:(?:\\\\|/)', data):
                raise ValueError(f"An absolute local path remains: {name}")
        elif path.suffix.lower() == ".cbp":
            for unit in ET.fromstring(data).findall(".//Unit"):
                reference = unit.attrib["filename"]
                target = safe_path(path.parent / reference)
                if not target.is_file():
                    if (name, reference) not in declared_gaps:
                        raise ValueError(f"Unrecorded missing legacy project reference: {name}")
                    observed_gaps.add((name, reference))
        elif path.suffix.lower() == ".zip":
            with zipfile.ZipFile(path) as archive:
                members = item["archived_zip_members"]
                if archive.namelist() != [m["name"] for m in members]:
                    raise ValueError(f"Data archive member structure changed: {name}")
                if [m["name"] for m in members] != [m["name"] for m in item["original_zip_members"]]:
                    raise ValueError(f"Original data archive member names lost: {name}")
                for member in members:
                    body = archive.read(member["name"])
                    if digest(body) != member["archived_sha256"] or body.startswith(b"MZ"):
                        raise ValueError(f"Invalid data archive member: {name}")
        output_count += item["status"] == "program_generated_local_output_unverified"
    if observed_gaps != declared_gaps:
        raise ValueError("The historical project-gap inventory no longer matches the supplied configurations")
    actual = {p.relative_to(ROOT).as_posix() for p in ARCHIVE.rglob("*") if p.is_file()
              and p not in {MANIFEST, ARCHIVE / "README.md"}}
    if actual != seen:
        raise ValueError("New, missing or unclassified files in the source archive")
    pe_count = legacy_pe_count = 0
    for excluded in manifest["excluded_regenerable_files"]:
        magic = bytes.fromhex(excluded["magic_prefix_hex"])
        if excluded["reason"] == "student_pe_compiled_executable":
            if not magic.startswith(b"MZ"):
                raise ValueError("An executable exclusion lacks the actual MZ signature")
            pe_count += 1
            legacy_pe_count += Path(excluded["source_filename_sanitized"]).suffix.lower() != ".exe"
        elif excluded["reason"] not in {"student_compiled_object", "codeblocks_generated_ide_state"}:
            raise ValueError("Unclassified source-folder exclusion")
    if len(seen) != manifest["source_counts"]["source_or_small_data"]:
        raise ValueError("Source-folder coverage count mismatch")
    if source_root is not None:
        original_files = [p for p in source_root.rglob("*") if p.is_file()]
        classified = Counter()
        original_hashes = Counter()
        excluded_hashes = Counter()
        for original in original_files:
            data = original.read_bytes()
            kind = classification(original, data)
            classified[kind] += 1
            if kind == "source_or_small_data":
                original_hashes[digest(data)] += 1
            elif kind != "document_or_image_separate_manifest":
                excluded_hashes[digest(data)] += 1
        if original_hashes != Counter(item["source_sha256"] for item in manifest["files"]):
            raise ValueError("The original folder contains changed, new or unclassified noncompiled inputs")
        if excluded_hashes != Counter(item["source_sha256"] for item in manifest["excluded_regenerable_files"]):
            raise ValueError("The original compiled/cache exclusion inventory changed")
        if classified["document_or_image_separate_manifest"] != manifest["source_counts"]["documents_or_images_separate_manifest"]:
            raise ValueError("The separate original-document inventory changed")
    return {"archived_files": len(seen), "source_or_saved_draft_files": code_count,
            "historical_txt_outputs": output_count, "excluded_mz_executables": pe_count,
            "legacy_extension_mz_executables": legacy_pe_count,
            "recorded_missing_original_cbp_units": len(declared_gaps),
            "preservation_check": "passed", "original_algorithm_validation": "not_performed"}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source-root", type=Path, help="Optional private original folder for full input-coverage comparison")
    args = parser.parse_args()
    print(json.dumps(check(args.source_root)))
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (ValueError, KeyError, OSError) as exc:
        print(f"Source archive preservation failed: {exc}", file=sys.stderr)
        raise SystemExit(1)
