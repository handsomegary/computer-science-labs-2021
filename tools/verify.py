"""Run every lab regression suite without retaining executable files."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
    args = parser.parse_args()
    compiler = shutil.which(args.cxx) or args.cxx
    if not Path(compiler).is_file():
        parser.error('C++ compiler not found: use --cxx /path/to/g++')
    env = os.environ.copy()
    env['CXX'] = compiler
    env['PATH'] = str(Path(compiler).resolve().parent) + os.pathsep + env.get('PATH', '')
    root = Path(__file__).resolve().parents[1]
    suites = sorted((root / 'tests').glob('test_*.py'))
    if not suites:
        parser.error('No regression suites found')
    for suite in suites:
        print(f'Running {suite.name}', flush=True)
        result = subprocess.run([sys.executable, str(suite)], cwd=root, env=env)
        if result.returncode:
            return result.returncode
    print(f'All {len(suites)} suites passed.', flush=True)
    return 0

if __name__ == '__main__':
    sys.exit(main())
