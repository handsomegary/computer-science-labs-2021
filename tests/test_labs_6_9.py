"""Compile and exercise Labs 6-9, including integer boundary/regression cases.

Usage: python tests/test_labs_6_9.py [--cxx /path/to/g++]
Only Python's standard library and a C++11 compiler are required.
"""
import argparse
import math
import os
from pathlib import Path
import random
import re
import subprocess
import tempfile


ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
    args = parser.parse_args()
    env = os.environ.copy()
    compiler_dir = str(Path(args.cxx).resolve().parent)
    env['PATH'] = compiler_dir + os.pathsep + env.get('PATH', '')
    checks = 0
    with tempfile.TemporaryDirectory(prefix='labs6_9_') as temporary:
        directory = Path(temporary)
        binaries = {}
        for source in sorted(ROOT.glob('lab0[6-9]/*.cpp')):
            target = directory / (source.stem + ('.exe' if os.name == 'nt' else ''))
            compiled = subprocess.run([args.cxx, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic',
                                       str(source), '-o', str(target)], text=True, capture_output=True, env=env)
            assert compiled.returncode == 0, f'{source.name}: {compiled.stderr}'
            assert not compiled.stderr.strip(), f'Compiler diagnostics for {source.name}: {compiled.stderr}'
            binaries[source.stem] = target

        def run(name, data, arguments=(), status=0):
            nonlocal checks
            result = subprocess.run([str(binaries[name]), *arguments], input=data, text=True,
                                    capture_output=True, env=env, timeout=10)
            assert result.returncode == status, f'{name} returned {result.returncode}: {result.stdout} {result.stderr}'
            assert not result.stderr, f'{name}: {result.stderr}'
            checks += 1
            return result.stdout

        assert run('lab6_1', '1 4 3\n') == 'Enter 3 nums: GCD of 1 and 24 and 6 is 1\n'
        for a, b, c in [(6, 12, 9), (20, 20, 20), (19, 17, 18), (1, 1, 1)]:
            expected = math.factorial(min(a, b, c))
            assert run('lab6_1', f'{a} {b} {c}\n').endswith(f'is {expected}\n')
        assert 'out of range' in run('lab6_1', '21 1 1\n', status=1)
        assert run('lab6_1_big', '30 22 25\n').endswith(f'is {math.factorial(22)}\n')
        assert 'error\nInput 3 Numbers:' in run('lab6_2', '1 1 2\n4 4 5\n')
        assert run('lab6_2', '3 4 5\n').endswith('Area of the triangle: 6\n')
        assert 'Perimeter of the rectangle: 8589934588\n' in run('lab6_2', '2147483647 2147483647 2147483647\n')
        one = run('lab6_3', '1\n')
        counts = [int(n) for n in re.findall(r'[ABCDF]: (\d+)', one)]
        assert len(counts) == 5 and sum(counts) == 1
        mean = float(re.search(r'Mean: (\d+\.\d{2})', one).group(1))
        assert 1 <= mean <= 100 and mean.is_integer()
        assert one.endswith('STD Deviation: 0.00\n')

        # Inject a known random-number stream at link time: all grade boundaries.
        stub = directory / 'random_stub.cpp'
        stub.write_text('extern "C" int rand(void) {\n'
                        '  static int i = 0;\n'
                        '  const int scores[] = {1,59,60,69,70,79,80,89,90,100};\n'
                        '  return scores[i++ % 10] - 1;\n}\n', encoding='utf-8')
        fixed_rng = directory / ('grades_fixed.exe' if os.name == 'nt' else 'grades_fixed')
        result = subprocess.run([args.cxx, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic',
                                 str(ROOT / 'lab06/lab6_3.cpp'), str(stub), '-o', str(fixed_rng)],
                                text=True, capture_output=True, env=env)
        assert result.returncode == 0 and not result.stderr, result.stderr
        binaries['grades_fixed'] = fixed_rng
        scores = [1, 59, 60, 69, 70, 79, 80, 89, 90, 100]
        avg = sum(scores) / len(scores)
        sd = math.sqrt(sum((s - avg) ** 2 for s in scores) / len(scores))
        known = run('grades_fixed', '10\n')
        assert re.findall(r'[ABCDF]: (\d+)', known) == ['2'] * 5
        assert known.endswith(f'Mean: {avg:.2f}\nSTD Deviation: {sd:.2f}\n')

        rng = random.Random(2021)
        roots = [0, 1, 2, 5, 15, 16, 999999999999999999, 9223372036854775807]
        roots += [rng.randrange(2**63) for _ in range(25)]
        for number in roots:
            scaled = math.isqrt(number * 10**20)
            expected = f'{scaled // 10**10}.{scaled % 10**10:010d}'
            assert run('lab7_1', f'{number}\n') == f'Enter a number: {expected}\n'
        retry = run('lab7_1', '-222\n1.5\nabc\n9223372036854775808\n5\n')
        assert retry.count('The number is out of range.') == 4
        assert retry.endswith('2.2360679774\n')
        for first, second in [('147258369', '741852963'), ('999999999999999999', '111111111111111111'),
                              ('9', '1'), ('1122', '222')]:
            sorted_first, sorted_second = ''.join(sorted(first)), ''.join(sorted(second))
            merged = ''.join(sorted(first + second, reverse=True))
            output = run('lab7_2', first + '\n' + second + '\n')
            assert f'first sequence number: {sorted_first}\n' in output
            assert f'second sequence number: {sorted_second}\n' in output
            assert output.endswith(f'Result: {merged}\n')
        source = (ROOT / 'lab07/lab7_2.cpp').read_text(encoding='utf-8')
        assert not re.search(r'\b(?:for|while)\s*\(|\bdo\s*\{', source)
        calc = run('lab7_3', '1\n1\n2\n3\n4\n')
        assert 'The number now is 3\n' in calc and '2 = 1,2\n' in calc
        calc = run('lab7_3', 'abc\n5\n2\n3\n4\n')
        assert calc.count('Enter error!!') == 2 and 'No factorization\n' in calc
        calc = run('lab7_3', '1\n3\n1\n1\n1\n3\n4\n')
        assert '1 = 1\n' in calc and '10 = 1,2,5,10\n' in calc

        assert run('lab8_1', '30 50 80\n') == ('Please enter the scores of three students:\n'
                                                           'avg = 53.333\nfail:\n1: 30\n2: 50\n')
        assert 'fail:' not in run('lab8_1', '60 60 100\n')
        assert run('lab8_2', '1 4 5\n').endswith('The arithmetical series: 1 + 5 + 9 + 13 + 17 = 45\n')
        assert run('lab8_2', '-1 -2 3\n').endswith('The arithmetical series: (-1) + (-3) + (-5) = (-9)\n')
        arithmetic = run('lab8_2', '2147483647 2147483647 101\n')
        assert arithmetic.endswith(f'= {sum(2147483647 * i for i in range(1, 102))}\n')
        assert 'Invalid input' in run('lab8_2', '1 1 0\n', status=1)
        pascal = run('lab8_3', '1\n4\n30\n0\n')
        last_row = '  '.join(str(math.comb(29, i)) for i in range(30))
        assert last_row in pascal and '1  3  3  1\n' in pascal
        assert run('lab8_4', '1\n3\n3\n2\n0\n') == '-----Menu-----\nTotal Cost: 155\n'
        assert run('lab8_4', '1\n2\n3\n2\n0\n') == '-----Menu-----\nTotal Cost: 140\n'
        receipt = run('lab8_4', '1\n1\n1\n1\n2\n8\n0\n', ['--receipt'])
        assert 'Coca Cola x 2: 80\n' in receipt and 'Iced Rose Latte x 1: 110\n' in receipt
        assert receipt.endswith('Total Cost: 190\n')
        invalid = run('lab8_4', '9\n3\n9\n4\n0\n')
        assert invalid.count('Invalid input') == 2 and invalid.endswith('Total Cost: 100\n')

        assert run('lab9_1', 'an apple a day\nkeeps the doctor away\n') == (
            'Input Line1: Input Line2: Output Line: An Apple A Day Keeps The Doctor Away\n')
        assert run('lab9_1', '  hello  world! \n\n').endswith('Output Line:   Hello  World!  \n')
        for values in [[1, 3, 4, 2, 6, 7], [5, 4, 4, 2, 7], [-2, -1], [-2147483648, 2147483647],
                       [2147483647, 2147483647], [7], [rng.randrange(-50, 51) for _ in range(131)],
                       [rng.randrange(-2147483648, 2147483648) for _ in range(20000)]]:
            arranged = sorted(values)
            mid = len(values) // 2
            median = arranged[mid] if len(values) % 2 else (arranged[mid-1] + arranged[mid]) // 2
            output = run('lab9_2', f'{len(values)}\n' + ' '.join(map(str, values)) + '\n')
            assert 'After sorting:\n' + ' '.join(map(str, arranged)) + ' \n' in output
            assert output.endswith(f'Median value of this series is: {median}\n')

        theater = run('lab9_3', '1\ny\n2\n1\ny\n2\n0\n16\n3\n2\n0\n16\n2\n2\n2\n1\nn\n4\n5\n')
        assert 'The seat has been reserved' in theater
        assert theater.count('Invalid input') == 4
        assert 'The seat number 2 is available now' in theater
        assert 'The seat is not reserved' in theater
        assert 'The seat number 1 is reserved for you' in theater
        full = run('lab9_3', '1\nn\n' * 15 + '1\n2\n8\n1\nn\n5\n')
        assert 'All seats have been reserved\n' in full
        assert full.count('The seat number 8 is reserved for you') == 2
        assert full.endswith('Thank you for using our system\nHave a nice day~~\n')
        assert 'Invalid input' in run('lab9_3', 'xyz\n2.5\n5\n')

        # Independent direction-walking oracle for all legal spiral dimensions.
        for size in range(3, 32):
            grid = [[0] * size for _ in range(size)]
            row = col = direction = 0
            directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
            for value in range(1, size * size + 1):
                grid[row][col] = value
                dr, dc = directions[direction]
                nr, nc = row + dr, col + dc
                if not (0 <= nr < size and 0 <= nc < size) or grid[nr][nc]:
                    direction = (direction + 1) % 4
                    dr, dc = directions[direction]
                row, col = row + dr, col + dc
            width = len(str(size * size))
            expected = ''.join(''.join(f'{v:0{width}d} ' for v in line) + '\n' for line in grid)
            assert run('lab9_4', f'{size}\n-1\n') == 'Input dimension: \n' + expected + '\nInput dimension: \n'
        assert run('lab9_4', '-1\n') == 'Input dimension: \n'
        assert 'Invalid input' in run('lab9_4', '2\n32\n-1\n')
    print(f'Labs 6-9: 15 programs compiled without warnings; {checks} executions passed.')


if __name__ == '__main__':
    main()
