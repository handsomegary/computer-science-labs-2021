"""Check original-document preservation using only the Python standard library."""

from pathlib import Path, PurePosixPath
import hashlib
import json
import posixpath
import re
import struct
import zipfile
import xml.etree.ElementTree as ET

HERE = Path(__file__).resolve().parent
REPO = HERE.parent
MANIFEST = HERE / "manifest.json"


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def safe_path(relative):
    path = PurePosixPath(relative)
    assert not path.is_absolute() and ".." not in path.parts, relative
    resolved = (REPO / relative).resolve()
    assert resolved.is_relative_to(REPO.resolve()), relative
    return resolved


def check_docx(path, record):
    with zipfile.ZipFile(path) as package:
        assert package.testzip() is None, path
        names = set(package.namelist())
        members = record["members"]
        assert names == {member["path"] for member in members}, path
        changed = []
        for member in members:
            data = package.read(member["path"])
            assert sha256(data) == member["published_sha256"], (path, member["path"])
            if member["byte_exact"]:
                assert member["source_sha256"] == member["published_sha256"]
            else:
                changed.append(member["path"])
            if member["path"].endswith((".xml", ".rels")):
                root = ET.fromstring(data)
                if member["path"].endswith(".rels"):
                    parent = posixpath.dirname(posixpath.dirname(member["path"]))
                    for relation in root:
                        if relation.get("TargetMode") == "External":
                            continue
                        target = relation.attrib["Target"]
                        resolved = posixpath.normpath(posixpath.join(parent, target))
                        assert resolved in names, (path, member["path"], target)
        assert sorted(changed) == sorted(record["privacy_transform"]["changed_members"])
        # Content and layout XML were preserved rather than regenerated.
        for required in ("word/document.xml", "word/styles.xml", "word/_rels/document.xml.rels"):
            assert next(m for m in members if m["path"] == required)["byte_exact"]
        core = ET.fromstring(package.read("docProps/core.xml"))
        for element in core:
            if element.tag.rsplit("}", 1)[-1] in {"creator", "lastModifiedBy"}:
                assert re.fullmatch(r"[a-z]+-[a-z]+-[0-9a-f]{4}", element.text or ""), path
    verification = record["verification"]
    qa = verification["word_readonly_fallback_qa"]
    assert verification["verified_render_page_count"] == qa["verified_word_pdf_page_count"] > 0
    assert len(qa["pages"]) == verification["verified_render_page_count"]
    assert qa["source_and_published_DOCX_input_hashes_unchanged"]
    assert all(page["visually_reviewed"] and page["native_pdf_text_unchanged"]
               and page["render_unchanged_outside_identity_regions"] for page in qa["pages"])
    assert "unavailable" in verification["canonical_docx_renderer_status"]


def check_png_metadata(data, record):
    assert data.startswith(b"\x89PNG\r\n\x1a\n")
    offset = 8
    chunks = []
    while offset < len(data):
        length = struct.unpack(">I", data[offset:offset + 4])[0]
        kind = data[offset + 4:offset + 8]
        chunks.append(kind)
        offset += 12 + length
        if kind == b"IEND":
            break
    assert offset == len(data), record["path"]
    if not record["byte_exact"]:
        assert set(chunks).issubset({b"IHDR", b"IDAT", b"IEND"}), record["path"]
        assert record["verification"]["final_image_visually_reviewed"]


def main():
    manifest = json.loads(MANIFEST.read_text(encoding="utf-8"))
    records = manifest["files"]
    assert manifest["schema_version"] == 1
    excluded = manifest["excluded"]
    assert len(records) == manifest["retained_item_count"] == 50
    assert len(records) + len(excluded) == manifest["scope_count"] == 54
    assert len({record["path"] for record in records}) == len(records)
    assert sum(record["status"] == "already preserved byte-exact" for record in records) == 37
    assert manifest["new_file_count"] == 13
    assert len(excluded) == 4
    assert sum(row["status"] == "intentionally_excluded_superseded" for row in excluded) == 1
    assert sum(row["status"] == "intentionally_excluded_user_request" for row in excluded) == 3
    for row in excluded:
        assert not safe_path(row["former_published_path"]).exists(), row
        if row["status"] == "intentionally_excluded_superseded":
            assert safe_path(row["replacement_path"]).is_file(), row
        else:
            assert "replacement_path" not in row
    assert not any((HERE / "exemption_rules").rglob("*.pdf"))
    counts = {"pdf": 0, "docx": 0, "png": 0}
    for record in records:
        path = safe_path(record["path"])
        data = path.read_bytes()
        assert len(data) == record["published_bytes"], path
        assert sha256(data) == record["published_sha256"], path
        assert not data.startswith(b"version https://git-lfs.github.com/spec/"), path
        if record["byte_exact"]:
            assert record["source_sha256"] == record["published_sha256"]
        counts[record["format"]] += 1
        if record["format"] == "pdf":
            assert data.startswith(b"%PDF-"), path
        elif record["format"] == "docx":
            check_docx(path, record)
        elif record["format"] == "png":
            check_png_metadata(data, record)
        else:
            raise AssertionError(record["format"])
        for companion in record.get("companion_files", []):
            assert safe_path(companion["path"]).is_file(), companion
    assert counts == {"pdf": 37, "docx": 3, "png": 10}, counts
    assert sum(row["verification"]["verified_render_page_count"] for row in records if row["format"] == "docx") == 28
    print("Original document archive OK: 54 inventoried; 50 retained (37 existing PDFs + 13 added files), 3 waiver documents and 1 superseded instruction excluded.")
    print("All file hashes, DOCX member hashes and relationships, and anonymous PNG containers verified.")
    print("Read-only Word fallback QA: 3 DOCX, 28 pages reviewed; canonical render_docx.py unavailable. Original layout XML retained byte-exact.")


if __name__ == "__main__":
    main()
