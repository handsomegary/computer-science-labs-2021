"""Check published course PDF/companion presence, bytes and documented omissions.

This checks preserved original and privacy-transformed files, not whether the
reconstructed solution tests pass. --require-complete also rejects known missing
official starter originals, which cannot be recovered from the supplied sources.
"""
import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import sys
import zipfile

ROOT = Path(__file__).resolve().parents[1]


def inside_repo(name):
    value = PurePosixPath(name)
    if value.is_absolute() or '..' in value.parts or ':' in name or '\\' in name:
        raise ValueError('Manifest path must be a repository-relative POSIX path: ' + name)
    return ROOT.joinpath(*value.parts)


def check_materials():
    manifest = json.loads((ROOT / 'course-materials.json').read_text(encoding='utf-8'))
    if manifest['schema_version'] != 1:
        raise ValueError('Unsupported course materials manifest version')
    records = manifest['documents'] + manifest['resources']
    seen = {}; documents = {}; errors = []
    for row in records:
        name = row['path']; path = inside_repo(name)
        if name in seen:
            errors.append('Duplicate manifest file: ' + name)
            continue
        seen[name] = row
        if not path.is_file():
            errors.append('Missing preserved course file: ' + name)
            continue
        data = path.read_bytes()
        if len(data) != row['size'] or hashlib.sha256(data).hexdigest() != row['sha256']:
            errors.append('Changed original or transformed course file: ' + name)
        if row in manifest['documents']:
            documents[name] = row
            if not data.startswith(b'%PDF-') or row['page_count'] < 1 or not row['byte_exact']:
                errors.append('Invalid original PDF record: ' + name)
        if row.get('status') == 'original_private_data_replaced' and row.get('byte_exact'):
            errors.append('Privacy replacement incorrectly marked byte-exact: ' + name)
        if row.get('role') == 'spelling_alias_for_pdf_reference':
            original = inside_repo(row['source_path'])
            if not original.is_file() or original.read_bytes() != data:
                errors.append('Spelling alias differs from its preserved original: ' + name)
        if row.get('role') == 'synthetic_membership_example':
            values = [line.split() for line in data.decode('utf-8').splitlines() if line.strip()]
            if len(values) - 1 != row['record_count'] or any(len(value) != row['column_count'] for value in values):
                errors.append('Synthetic membership format or record count changed: ' + name)
            if any(not value[0].startswith('guest-') for value in values[1:]):
                errors.append('Synthetic membership names no longer use random aliases: ' + name)
        if row.get('role') == 'privacy_transformed_membership_package':
            try:
                with zipfile.ZipFile(path) as package:
                    if package.namelist() != ['3_1.txt']:
                        errors.append('Anonymized archive member layout changed: ' + name)
                    elif package.read('3_1.txt') != inside_repo('course_support/2021/lab14/examples/3_1.txt').read_bytes():
                        errors.append('Anonymized archive and extracted membership example differ: ' + name)
            except (OSError, zipfile.BadZipFile) as error:
                errors.append('Cannot read anonymized membership archive: ' + name + ': ' + str(error))
    for reference in manifest['companion_references']:
        name = reference['document']; page = reference['pdf_page']
        if name not in documents or not 1 <= page <= documents[name]['page_count']:
            errors.append('Companion reference has no preserved PDF/page: ' + name)
        target = reference.get('resource_path')
        if target and (target not in seen or not inside_repo(target).is_file()):
            errors.append('Companion reference has no preserved resource: ' + target)
    missing = manifest['missing_original_companions']
    if any(row['status'] != 'not_provided' or row.get('resource_path') for row in missing):
        errors.append('Known original-source gap is incorrectly labelled as a preserved file')
    return {
        'preserved_integrity_passed': not errors,
        'original_course_attachment_set_complete': not missing and not errors,
        'original_pdfs_checked': len(manifest['documents']),
        'companion_resources_checked': len(manifest['resources']),
        'reference_items_checked': len(manifest['companion_references']),
        'known_missing_official_originals': [row['reference'] for row in missing],
        'errors': errors,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--require-complete', action='store_true', help='return failure for known original-source gaps as well as missing/changed preserved files')
    parser.add_argument('--json', action='store_true', help='print the structured integrity and completeness result')
    args = parser.parse_args()
    try:
        result = check_materials()
    except (OSError, ValueError, KeyError) as error:
        print('Cannot verify course materials: ' + str(error), file=sys.stderr)
        return 1
    if args.json:
        print(json.dumps(result, ensure_ascii=False, indent=2))
    else:
        print(f"Preserved materials: {result['original_pdfs_checked']} original PDFs, {result['companion_resources_checked']} companion resources, {result['reference_items_checked']} references checked.")
        for error in result['errors']: print(error, file=sys.stderr)
        for item in result['known_missing_official_originals']: print('Known unavailable official original: ' + item)
        print('Preserved-file integrity: ' + ('PASS' if result['preserved_integrity_passed'] else 'FAIL'))
        print('Original course attachment set complete: ' + ('YES' if result['original_course_attachment_set_complete'] else 'NO (see the recorded source gaps)'))
    if not result['preserved_integrity_passed']: return 1
    if args.require_complete and not result['original_course_attachment_set_complete']: return 2
    return 0


if __name__ == '__main__':
    sys.exit(main())
