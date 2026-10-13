"""Synchronize exam statements, executable examples, and complete solutions."""
import argparse
from collections import defaultdict
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
BASE_SPEC = importlib.util.spec_from_file_location('lab_solution_format', ROOT / 'tools/sync_solutions.py')
BASE = importlib.util.module_from_spec(BASE_SPEC)
BASE_SPEC.loader.exec_module(BASE)
CODE_START, CODE_END = BASE.CODE_START, BASE.CODE_END
SAMPLES_START, SAMPLES_END = BASE.SAMPLES_START, BASE.SAMPLES_END
embedded_code = BASE.embedded_code


def load_records():
    records = []
    for manifest in sorted((ROOT / 'exams/2021').glob('*/solutions/samples*.json')):
        rows = json.loads(manifest.read_text(encoding='utf-8-sig'))
        if not isinstance(rows, list):
            raise ValueError(f'{manifest}: expected a sample array')
        for row in rows:
            for field in ('document', 'source', 'stdin', 'stdout'):
                if not isinstance(row.get(field), str):
                    raise ValueError(f'{manifest}: missing string field {field}')
            document = BASE.within(manifest.parent / row['document'], manifest.parent)
            source = BASE.within(ROOT / row['source'], ROOT / 'exams/2021')
            if (document.suffix != '.md' or source.suffix != '.cpp' or document.stem != source.stem
                    or document.parent.parent != source.parent):
                raise ValueError(f'{manifest}: mismatched document/source')
            if not document.is_file() or not source.is_file():
                raise ValueError(f'{manifest}: document or source missing')
            if not isinstance(row.get('returncode', 0), int) or not isinstance(row.get('stderr', ''), str):
                raise ValueError(f'{manifest}: invalid expected exit status/stderr')
            files = row.get('files', {})
            if not isinstance(files, dict):
                raise ValueError(f'{manifest}: files must be a filename/content map')
            for filename, content in files.items():
                if (not isinstance(filename, str) or not filename or filename in ('.', '..')
                        or re.search(r'[\\/:]', filename) or not isinstance(content, str)):
                    raise ValueError(f'{manifest}: unsafe or invalid sample attachment')
            records.append(dict(row, document_path=document, source_path=source))
    expected = {ROOT / 'exams/2021' / kind / f'problem_{letter}.cpp'
                for kind, letters in (('midterm', 'abcdef'), ('final', 'abcdefg'))
                for letter in letters}
    covered = {record['source_path'] for record in records}
    actual = set((ROOT / 'exams/2021').glob('*/problem_*.cpp'))
    if expected != covered or expected != actual:
        raise ValueError('Expected all six midterm and seven final exercises with documented samples')
    return records


def order(document):
    kind = document.parent.parent.name
    return (0 if kind == 'midterm' else 1, document.name)


def index_text(grouped):
    lines = ['# 考古題與完整 solution', '',
             '110 學年度第一學期（2021 課程）期中 6 題、期末 7 題，合計 13 題。'
             '每頁都有繁中題目、輸入輸出、採用規則、實測範例、解法及完整 C++11 程式碼。', '',
             '| 考試 | 題號 | 題目與完整 solution | 獨立程式 |',
             '| --- | --- | --- | --- |']
    for document, samples in sorted(grouped.items(), key=lambda item: order(item[0])):
        source = samples[0]['source_path']
        title = document.read_text(encoding='utf-8').splitlines()[0].lstrip('# ').replace('|', '\\|')
        kind = '期中' if source.parent.name == 'midterm' else '期末'
        letter = source.stem.rsplit('_', 1)[1].upper()
        doc_path = document.relative_to(ROOT / 'exams').as_posix()
        source_path = source.relative_to(ROOT / 'exams').as_posix()
        lines.append(f'| {kind} | {letter} | [{title}]({doc_path}) | [{source.name}]({source_path}) |')
    lines += ['', '[JSON 題目集](problems.json) 的每筆 `solution.code` 都包含完整程式碼；'
              '檔案型題目的範例附件在 `examples[].files`。', '',
              '執行 `python tools/sync_exam_solutions.py` 可同步文件；'
              'CI 檢查同步狀態、編譯 solution 內嵌程式碼，並逐筆實測範例。', '']
    return '\n'.join(lines)


def dataset_text(grouped):
    result = []
    for document, samples in sorted(grouped.items(), key=lambda item: order(item[0])):
        text = document.read_text(encoding='utf-8')
        without_source = BASE.replace_section(text, CODE_START, CODE_END, '')
        sections = re.split(r'(?m)(^## [^\n]+\n)', without_source)
        problem, explanation = [sections[0]], []
        for index in range(1, len(sections), 2):
            heading, body = sections[index:index + 2]
            solution_section = any(term in heading.lower() for term in
                                   ('solution', '解法', '題解', '解答程式', '編譯與執行'))
            (explanation if solution_section else problem).extend([heading, body])
        def clean(parts):
            return re.sub(r'(?m)^<!-- (?:SOLUTION_CODE|SAMPLES)_(?:BEGIN|END) -->\n?', '',
                          ''.join(parts)).strip()
        source = samples[0]['source_path']
        code = source.read_text(encoding='utf-8')
        kind = source.parent.name.capitalize()
        result.append({
            'id': f'2021-{kind}-{source.stem.rsplit("_", 1)[1].upper()}',
            'title': text.splitlines()[0].lstrip('# '),
            'status': 'provided-exam-with-documented-clarifications',
            'problem': {'statement_markdown': clean(problem),
                        'document': document.relative_to(ROOT).as_posix()},
            'solution': {'language': 'C++11', 'explanation_markdown': clean(explanation),
                         'code': code, 'source': source.relative_to(ROOT).as_posix(),
                         'source_sha256': hashlib.sha256(code.encode('utf-8')).hexdigest()},
            'examples': [dict(stdin=sample['stdin'], stdout=sample['stdout'],
                              stderr=sample.get('stderr', ''), returncode=sample.get('returncode', 0),
                              **({'files': sample['files']} if sample.get('files') else {}))
                         for sample in samples],
        })
    return json.dumps(result, ensure_ascii=False, indent=2) + '\n'


def sync(check=False):
    records = load_records()
    grouped = defaultdict(list)
    for sample in records:
        grouped[sample['document_path']].append(sample)
    stale = []
    for document, samples in sorted(grouped.items(), key=lambda item: order(item[0])):
        original = document.read_text(encoding='utf-8')
        code = samples[0]['source_path'].read_text(encoding='utf-8')
        updated = BASE.replace_section(original, CODE_START, CODE_END, BASE.fenced(code, 'cpp'))
        examples = ['下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。']
        for index, sample in enumerate(samples, 1):
            for filename, content in sorted(sample.get('files', {}).items()):
                examples += [f'\n### 範例 {index} 附件 `{filename}`\n', BASE.fenced(content, 'text')]
            examples += [f'\n### 範例 {index} 輸入\n', BASE.fenced(sample['stdin'], 'text'),
                         f'\n### 範例 {index} 輸出\n', BASE.fenced(sample['stdout'], 'text')]
            if sample['stdout'] and not sample['stdout'].endswith('\n'):
                examples.append('\n此範例 stdout 最後沒有換行；code fence 結束行只用於排版。')
            if sample.get('stderr'):
                examples += [f'\n### 範例 {index} 標準錯誤\n', BASE.fenced(sample['stderr'], 'text')]
            if sample.get('returncode', 0):
                examples.append(f'\n程式結束碼：{sample["returncode"]}。')
        updated = BASE.replace_section(updated, SAMPLES_START, SAMPLES_END, '\n'.join(examples))
        updated = updated.rstrip('\n') + '\n'
        if updated != original:
            stale.append(str(document.relative_to(ROOT)))
            if not check:
                document.write_text(updated, encoding='utf-8', newline='\n')
    for path, wanted in ((ROOT / 'exams/SOLUTIONS.md', index_text(grouped)),
                         (ROOT / 'exams/problems.json', dataset_text(grouped))):
        current = path.read_text(encoding='utf-8') if path.exists() else ''
        if current != wanted:
            stale.append(str(path.relative_to(ROOT)))
            if not check:
                path.write_text(wanted, encoding='utf-8', newline='\n')
    if check and stale:
        raise ValueError('Stale exam solution documents: ' + ', '.join(stale))
    print(f'{"Checked" if check else "Synchronized"} {len(grouped)} exam solutions and '
          f'{len(records)} executable examples with complete solution.code.')
    return records


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    try:
        sync(args.check)
    except (ValueError, OSError, KeyError) as error:
        print(str(error), file=sys.stderr)
        raise SystemExit(1)
