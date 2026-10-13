"""Embed canonical C++ and executable samples into reconstructed solution pages."""
import argparse
from collections import defaultdict
import hashlib
import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
CODE_START = '<!-- SOLUTION_CODE_BEGIN -->'
CODE_END = '<!-- SOLUTION_CODE_END -->'
SAMPLES_START = '<!-- SAMPLES_BEGIN -->'
SAMPLES_END = '<!-- SAMPLES_END -->'
NAV_START = '<!-- SOLUTIONS_NAV_BEGIN -->'
NAV_END = '<!-- SOLUTIONS_NAV_END -->'


def within(path, parent):
    path = path.resolve()
    if parent.resolve() not in path.parents:
        raise ValueError(f'Path outside permitted document tree: {path}')
    return path


def load_records():
    records = []
    for manifest in sorted((ROOT / '2024').glob('lab*/solutions/samples*.json')):
        data = json.loads(manifest.read_text(encoding='utf-8-sig'))
        if not isinstance(data, list):
            raise ValueError(f'{manifest}: expected a JSON array')
        for sample in data:
            for field in ('document', 'source', 'stdin', 'stdout'):
                if not isinstance(sample.get(field), str):
                    raise ValueError(f'{manifest}: missing string {field}')
            document = within(manifest.parent / sample['document'], manifest.parent)
            source = within(ROOT / sample['source'], ROOT / '2024')
            if document.suffix != '.md' or source.suffix != '.cpp':
                raise ValueError(f'{manifest}: invalid document/source type')
            if document.stem != source.stem or document.parent.parent != source.parent:
                raise ValueError(f'{manifest}: document and source must belong to the same exercise')
            if not document.is_file() or not source.is_file():
                raise ValueError(f'{manifest}: document/source does not exist')
            if not isinstance(sample.get('returncode', 0), int):
                raise ValueError(f'{manifest}: returncode must be an integer')
            if not isinstance(sample.get('stderr', ''), str):
                raise ValueError(f'{manifest}: stderr must be a string')
            records.append(dict(sample, document_path=document, source_path=source))
    expected = set((ROOT / '2024').glob('lab*/lab*_*.cpp'))
    covered = {sample['source_path'] for sample in records}
    if covered != expected:
        missing = sorted(str(p.relative_to(ROOT)) for p in expected - covered)
        extra = sorted(str(p.relative_to(ROOT)) for p in covered - expected)
        raise ValueError(f'Exercise sample coverage mismatch; missing={missing}, extra={extra}')
    return records


def replace_section(text, start, end, content):
    if text.count(start) != 1 or text.count(end) != 1:
        raise ValueError(f'Expected exactly one marker pair: {start} / {end}')
    left, right = text.index(start) + len(start), text.index(end)
    if right < left:
        raise ValueError(f'Reversed marker pair: {start}')
    return text[:left] + '\n' + content + '\n' + text[right:]


def fenced(text, language):
    longest = max((len(m.group(0)) for m in re.finditer(r'`+', text)), default=0)
    ticks = '`' * max(3, longest + 1)
    return f'{ticks}{language}\n{text}' + ('' if text.endswith('\n') else '\n') + ticks


def embedded_code(document):
    text = document.read_text(encoding='utf-8')
    body = text.split(CODE_START, 1)[1].split(CODE_END, 1)[0].strip('\n')
    lines = body.splitlines(keepends=True)
    if not lines or not re.fullmatch(r'`{3,}cpp\n', lines[0]):
        raise ValueError(f'{document}: complete solution must be a cpp code fence')
    fence = lines[0].rstrip('\n')[:-3]
    if lines[-1].rstrip('\n') != fence:
        raise ValueError(f'{document}: mismatched solution code fence')
    return ''.join(lines[1:-1])


def index_text(grouped):
    lines = ['# 2024 重建題目與 solution 索引', '',
        '依詳解程式碼重建的 40 題練習，每頁都有完整題目、輸入輸出、限制、'
        '實測範例、解法及完整 C++11 程式碼。講義規則與自行補定的內容分開註明；'
        '這些是本 repo 的重建版，不冒稱教授原題。', '',
        '| 題號 | 題目與完整 solution | 獨立程式 |',
        '| --- | --- | --- |']
    for document, samples in sorted(grouped.items()):
        title = document.read_text(encoding='utf-8').splitlines()[0].lstrip('# ').replace('|', '\\|')
        source = samples[0]['source_path']
        source_relative = source.relative_to(ROOT / '2024').as_posix()
        doc_relative = document.relative_to(ROOT / '2024').as_posix()
        number = source.stem.replace('lab', '').replace('_', '.')
        lines.append(f'| {number} | [{title}]({doc_relative}) | [{source.name}]({source_relative}) |')
    lines += ['', '[機器可讀題目集](problems.json) 同時保存 `problem` 與 `solution`；'
        '完整題解程式碼在每筆的 `solution.code`，另有解法與範例。', '',
        '各 solution 的完整程式碼與範例由 `tools/sync_solutions.py` 同步。'
        'CI 會檢查區塊沒有過期、直接編譯嵌入的程式碼，並核對全部範例輸出。', '']
    return '\n'.join(lines)


def dataset_text(grouped):
    dataset = []
    for document, samples in sorted(grouped.items()):
        text = document.read_text(encoding='utf-8')
        # Preserve explanatory snippets in solution; the complete source gets
        # its own explicit solution.code field rather than an external link.
        without_source = replace_section(text, CODE_START, CODE_END, '')
        parts = re.split(r'(?m)(^## [^\n]+\n)', without_source)
        problem_parts = [parts[0]]
        solution_parts = []
        for at in range(1, len(parts), 2):
            heading, body = parts[at], parts[at + 1]
            is_solution = any(term in heading.lower() for term in
                              ('solution', '解法', '題解', '解答程式', '編譯與執行'))
            (solution_parts if is_solution else problem_parts).extend([heading, body])
        clean = lambda content: re.sub(r'(?m)^<!-- (?:SOLUTION_CODE|SAMPLES)_(?:BEGIN|END) -->\n?', '',
                                      ''.join(content)).strip()
        source = samples[0]['source_path']
        code = source.read_text(encoding='utf-8')
        dataset.append({
            'id': '2024-Lab' + source.stem.replace('lab', '').replace('_', '.'),
            'title': text.splitlines()[0].lstrip('# '),
            'status': 'reconstructed',
            'problem': {'statement_markdown': clean(problem_parts),
                        'document': document.relative_to(ROOT).as_posix()},
            'solution': {'language': 'C++11', 'explanation_markdown': clean(solution_parts),
                         'code': code, 'source': source.relative_to(ROOT).as_posix(),
                         'source_sha256': hashlib.sha256(code.encode('utf-8')).hexdigest()},
            'examples': [{'stdin': s['stdin'], 'stdout': s['stdout'],
                          'stderr': s.get('stderr', ''), 'returncode': s.get('returncode', 0)}
                         for s in samples],
        })
    return json.dumps(dataset, ensure_ascii=False, indent=2) + '\n'


def sync_lab_navigation(grouped, check, stale):
    labs = defaultdict(list)
    for document, samples in grouped.items():
        labs[samples[0]['source_path'].parent].append(document)
    for lab, documents in sorted(labs.items()):
        readme = lab / 'README.md'
        original = readme.read_text(encoding='utf-8')
        content = ['## 完整重建題目與 solution', '',
                   '以下各頁包含明確題目、補定規則、實測範例、題解核心片段與完整 C++11 程式碼。', '']
        for document in sorted(documents):
            number = document.stem.replace('lab', '').replace('_', '.')
            content.append(f'- [Lab {number} 題目與 solution](solutions/{document.name})')
        content += ['', '[全部 40 題索引](../SOLUTIONS.md) · '
                    '[problem / solution 資料集](../problems.json)']
        navigation = '\n'.join(content)
        if NAV_START not in original:
            heading, separator, body = original.partition('\n')
            original_for_update = heading + separator + '\n' + NAV_START + '\n' + NAV_END + '\n' + body
        else:
            original_for_update = original
        updated = replace_section(original_for_update, NAV_START, NAV_END, navigation)
        if updated != original:
            stale.append(str(readme.relative_to(ROOT)))
            if not check:
                readme.write_text(updated, encoding='utf-8', newline='\n')


def sync(check=False):
    records = load_records()
    grouped = defaultdict(list)
    for sample in records:
        grouped[sample['document_path']].append(sample)
    stale = []
    for document, samples in sorted(grouped.items()):
        original = document.read_text(encoding='utf-8')
        source_code = samples[0]['source_path'].read_text(encoding='utf-8')
        updated = replace_section(original, CODE_START, CODE_END, fenced(source_code, 'cpp'))
        examples = ['以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。']
        for index, sample in enumerate(samples, 1):
            examples += [f'\n### 範例 {index} 輸入\n', fenced(sample['stdin'], 'text'),
                         f'\n### 範例 {index} 輸出\n', fenced(sample['stdout'], 'text')]
            if sample['stdout'] and not sample['stdout'].endswith('\n'):
                examples.append('\n此範例的標準輸出最後沒有換行；code fence 的結束行只用於排版。')
            if sample.get('stderr'):
                examples += [f'\n### 範例 {index} 標準錯誤\n', fenced(sample['stderr'], 'text')]
        updated = replace_section(updated, SAMPLES_START, SAMPLES_END, '\n'.join(examples))
        updated = updated.rstrip('\n') + '\n'
        if updated != original:
            stale.append(str(document.relative_to(ROOT)))
            if not check:
                document.write_text(updated, encoding='utf-8', newline='\n')
    sync_lab_navigation(grouped, check, stale)
    index = ROOT / '2024/SOLUTIONS.md'
    wanted_index = index_text(grouped)
    current_index = index.read_text(encoding='utf-8') if index.exists() else ''
    if current_index != wanted_index:
        stale.append('2024/SOLUTIONS.md')
        if not check:
            index.write_text(wanted_index, encoding='utf-8', newline='\n')
    # Read the final pages after embedding; in check mode those pages must
    # already match the canonical source/sample sections above.
    dataset = ROOT / '2024/problems.json'
    wanted_dataset = dataset_text(grouped)
    current_dataset = dataset.read_text(encoding='utf-8') if dataset.exists() else ''
    if current_dataset != wanted_dataset:
        stale.append('2024/problems.json')
        if not check:
            dataset.write_text(wanted_dataset, encoding='utf-8', newline='\n')
    if check and stale:
        raise ValueError('Stale solution pages; run python tools/sync_solutions.py: ' + ', '.join(stale))
    print(f'{"Checked" if check else "Synchronized"} {len(grouped)} solution pages, '
          f'{len(records)} executable samples, and full embedded C++ sources.')
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
