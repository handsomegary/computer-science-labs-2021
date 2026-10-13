"""Compile the complete code embedded in solution pages and verify every sample."""
import argparse
import importlib.util
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('sync_solutions', ROOT / 'tools/sync_solutions.py')
SYNC = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SYNC)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
    args = parser.parse_args()
    records = SYNC.sync(check=True)
    compiler = shutil.which(args.cxx) or args.cxx
    env = os.environ.copy()
    env['PATH'] = str(Path(compiler).resolve().parent) + os.pathsep + env.get('PATH', '')
    with tempfile.TemporaryDirectory(prefix='solution-docs-') as folder:
        directory = Path(folder)
        programs = {}
        for sample in records:
            document = sample['document_path']
            if document in programs:
                continue
            unit = directory / (document.stem + '.cpp')
            unit.write_text(SYNC.embedded_code(document), encoding='utf-8', newline='\n')
            executable = directory / (document.stem + ('.exe' if os.name == 'nt' else ''))
            compiled = subprocess.run([compiler, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic',
                                       str(unit), '-o', str(executable)], capture_output=True,
                                      text=True, encoding='utf-8', env=env, timeout=30)
            if compiled.returncode or compiled.stderr:
                raise AssertionError(f'{document}: embedded code failed or warned:\n{compiled.stderr}')
            programs[document] = executable
        for sample in records:
            result = subprocess.run([str(programs[sample['document_path']])],
                                    input=sample['stdin'], text=True, encoding='utf-8',
                                    capture_output=True, env=env, timeout=10)
            expected_status = sample.get('returncode', 0)
            if (result.returncode != expected_status or result.stdout != sample['stdout']
                    or result.stderr != sample.get('stderr', '')):
                raise AssertionError(f"{sample['document_path']}: example mismatch\n"
                    f"status={result.returncode}, expected={expected_status}\n"
                    f"actual={result.stdout!r}\nexpected={sample['stdout']!r}\n{result.stderr}")
    print(f'{len(programs)} complete solution code blocks compiled without warnings; '
          f'{len(records)} documented examples passed.')


if __name__ == '__main__':
    main()
