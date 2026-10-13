"""Compile all thirteen complete exam solution blocks and run documented examples."""
import argparse
import importlib.util
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('exam_solution_sync', ROOT / 'tools/sync_exam_solutions.py')
SYNC = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SYNC)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
    args = parser.parse_args()
    records = SYNC.sync(check=True)
    compiler = shutil.which(args.cxx) or args.cxx
    environment = dict(os.environ)
    environment['PATH'] = str(Path(compiler).resolve().parent) + os.pathsep + environment.get('PATH', '')
    with tempfile.TemporaryDirectory(prefix='exam-documents-build-') as folder:
        build = Path(folder)
        programs = {}
        for sample in records:
            document = sample['document_path']
            if document in programs:
                continue
            name = document.parent.parent.name + '_' + document.stem
            unit = build / (name + '.cpp')
            unit.write_text(SYNC.embedded_code(document), encoding='utf-8', newline='\n')
            executable = build / (name + ('.exe' if os.name == 'nt' else ''))
            result = subprocess.run([compiler, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic',
                                     str(unit), '-o', str(executable)], capture_output=True,
                                    text=True, encoding='utf-8', env=environment, timeout=30)
            if result.returncode or result.stderr:
                raise AssertionError(f'{document}: compilation failed or warned:\n{result.stderr}')
            programs[document] = executable
        for sample in records:
            with tempfile.TemporaryDirectory(prefix='exam-documents-example-') as case_folder:
                for filename, content in sample.get('files', {}).items():
                    (Path(case_folder) / filename).write_text(content, encoding='utf-8', newline='\n')
                result = subprocess.run([str(programs[sample['document_path']])], input=sample['stdin'],
                    capture_output=True, text=True, encoding='utf-8', env=environment,
                    cwd=case_folder, timeout=20)
            if (result.returncode != sample.get('returncode', 0) or result.stdout != sample['stdout']
                    or result.stderr != sample.get('stderr', '')):
                raise AssertionError(f"{sample['document_path']}: example mismatch\n"
                    f"actual status={result.returncode}; stdout={result.stdout!r}; stderr={result.stderr!r}\n"
                    f"expected status={sample.get('returncode', 0)}; stdout={sample['stdout']!r}")
    print(f'{len(programs)} complete exam solution blocks compiled without warnings; '
          f'{len(records)} documented exam examples passed.')


if __name__ == '__main__':
    main()
