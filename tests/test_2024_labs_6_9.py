"""2024 Labs 6-9 reference contracts; standalone C++11 compilation and tests.

Some slides omit original OJ I/O; the per-lab READMEs state those assumptions.
Lab 7.4 has its own root-owned test suite and is excluded here.
"""
import argparse
from decimal import Decimal, ROUND_HALF_UP
import itertools
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
    parser.add_argument('--input-validation-only', action='store_true',
                        help='compile only the four unsigned-input regressions')
    args = parser.parse_args()
    env = os.environ.copy()
    env['PATH'] = str(Path(args.cxx).resolve().parent) + os.pathsep + env.get('PATH', '')
    checks = 0
    sources = sorted(s for s in (ROOT / '2024').glob('lab0[6-9]/*.cpp') if s.stem != 'lab7_4')
    if args.input_validation_only:
        sources = [s for s in sources if s.stem in {'lab7_2', 'lab7_3', 'lab8_3', 'lab8_4'}]
    assert len(sources) == (4 if args.input_validation_only else 15), [str(s) for s in sources]
    with tempfile.TemporaryDirectory(prefix='2024_labs6_9_') as temporary:
        directory = Path(temporary)
        binaries = {}

        def compile_source(source, name, flags=()):
            executable = directory / (name + ('.exe' if os.name == 'nt' else ''))
            result = subprocess.run([args.cxx, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic',
                                     *flags, str(source), '-o', str(executable)],
                                    text=True, capture_output=True, env=env)
            assert result.returncode == 0, f'{source.name}: {result.stderr}'
            assert not result.stderr.strip(), f'{source.name}: {result.stderr}'
            binaries[name] = executable

        for source in sources:
            compile_source(source, source.stem)
        if not args.input_validation_only:
            compile_source(ROOT / '2024/lab07/lab7_3.cpp', 'prime_power', ['-DALMOST_PRIME_MODE=1'])
            compile_source(ROOT / '2024/lab07/lab7_3.cpp', 'two_distinct', ['-DALMOST_PRIME_MODE=2'])

        def run(name, data, status=0):
            nonlocal checks
            result = subprocess.run([str(binaries[name])], input=data, text=True, capture_output=True,
                                    timeout=10, env=env)
            assert result.returncode == status, f'{name}: {result.returncode}, {result.stdout}, {result.stderr}'
            assert not result.stderr, result.stderr
            checks += 1
            return result.stdout

        # Negative text must be rejected before unsigned conversion; otherwise
        # -2^64+1 or -2^32+1 can wrap to a small apparently valid value.
        for name, data in [('lab7_2', '-18446744073709551615\n'),
                           ('lab7_2', '-1\n'),
                           ('lab7_3', '-18446744073709551615 10\n'),
                           ('lab7_3', '1 -18446744073709551606\n'),
                           ('lab8_3', '-4294967295 123\n'),
                           ('lab8_3', '3 -4294967173\n'),
                           ('lab8_4', '-18446744073709551604\n'),
                           ('lab8_4', '-1\n')]:
            run(name, data, 1)
        assert run('lab7_2', '9223372036854775807\n') == 'off\n'
        assert run('lab7_3', '0 0\n') == 'decimal: 0\nbinary: 0\nhex: 0\n'
        assert run('lab8_3', '0 123\n') == '1\n'
        assert run('lab8_4', '0\n') == '0\n'
        if args.input_validation_only:
            print(f'2024 unsigned-input regressions: 4 programs compiled without warnings; {checks} executions passed.')
            return

        for numbers in [(3.25, -2.5, 9.75), (1, 1, 1), (-8, -7, -9), (0, 2, 1), (1e100, 3e99, 2e100)]:
            assert float(run('lab6_1', ' '.join(map(str, numbers)) + '\n')) == min(numbers)
        for first, second in [(3, 4), (21, 6), (1, 2147483647), (100000, 200000), (2147483647, 2147483647)]:
            expected = first // math.gcd(first, second) * second
            assert run('lab6_2', f'{first} {second}\n') == f'{expected}\n'
        assert run('lab6_2', '0 8\n', 1) == 'error\n'
        assert run('lab6_2', '2147483647 2147483646\n', 1) == 'error\n'

        membership_cases = [(True, 0, '500 dollars coupon'), (True, 4999, '500 dollars coupon'),
                            (True, 5000, '1000 dollars coupon'), (True, 10000, '1000 dollars coupon'),
                            (True, 10001, '3000 dollars coupon and one lottery ticket'),
                            (False, 6999, 'do not have any bonus'), (False, 7000, '500 dollars coupon'),
                            (False, 10000, '500 dollars coupon'),
                            (False, 10001, '1500 dollars coupon and become a store member')]
        for member, spending, expected in membership_cases:
            output = run('lab6_3', f'Y\n{"y" if member else "n"}\n{spending}\nn\n')
            assert expected in output and 'GOOD BYE!' in output
        assert 'GOOD BYE!' in run('lab6_3', 'n\n')
        assert 'Invalid input' in run('lab6_3', 'x\nn\n')
        for x, y, z in [(3, 5, 4), (2, 4, 3), (2, 4, 6), (6, 10, 14), (6, 10, 17),
                        (2147483647, 2147483646, 4294967293)]:
            expected = z <= x+y and z % math.gcd(x, y) == 0
            assert run('lab6_4', f'{x} {y} {z}\n') == f'{int(expected)}\n'

        assert run('lab7_1', '3 4 5\n') == 'perimeter: 12\narea: 6\n'
        for sides in [(1, 1, 2), (0, 4, 5), (-1, 4, 5)]:
            assert run('lab7_1', ' '.join(map(str, sides)) + '\n') == 'error\n'
        output = run('lab7_1', '1 1 1\n')
        assert math.isclose(float(output.split('area: ')[1]), math.sqrt(3) / 4, rel_tol=1e-6)
        for number in [0, 1, 2, 4, 15, 16, 17, 3037000499**2, 3037000499**2-1, 9223372036854775807]:
            expected = math.isqrt(number) ** 2 == number
            assert run('lab7_2', f'{number}\n') == ('on\n' if expected else 'off\n')

        def factorization(number):
            factors = []
            divisor = 2
            while divisor * divisor <= number:
                while number % divisor == 0:
                    factors.append(divisor)
                    number //= divisor
                divisor += 1
            if number > 1:
                factors.append(number)
            return factors

        for name, predicate in [('lab7_3', lambda f: len(f) == 2),
                                ('prime_power', lambda f: len(f) >= 2 and len(set(f)) == 1),
                                ('two_distinct', lambda f: len(set(f)) == 2)]:
            for low, high in [(0, 3), (4, 10), (1, 100), (49, 49), (64, 64), (100, 257)]:
                count = sum(predicate(factorization(n)) for n in range(max(2, low), high + 1))
                expected = f'decimal: {count}\nbinary: {count:b}\nhex: {count:X}\n'
                assert run(name, f'{low} {high}\n') == expected
        source = (ROOT / '2024/lab07/lab7_3.cpp').read_text(encoding='utf-8')
        source = re.sub(r'//[^\n]*', '', source)
        assert 'vector' not in source and 'string' not in source and not re.search(r'\w\s*\[', source)

        for m, n in [(0, 0), (5, 2), (20, 10), (67, 33), (100, 50), (1000, 500), (4294967295, 1)]:
            assert run('lab8_1', f'{m} {n}\n') == f'ans: {math.comb(m, n)}\n'

        def is_prime(number):
            return number >= 2 and all(number % d for d in range(2, math.isqrt(number) + 1))

        for first, second in [(5, 8), (8, 12), (1, 8), (15, 21), (20, 20), (2147483647, 2147483646)]:
            x, y = first, second
            while not (is_prime(x) or is_prime(y)):
                x, y = max(x, y) // 2, min(x, y)
            assert run('lab8_2', f'{first} {second}\n') == f'{x*y}\n'
        assert run('lab8_2', '1 1\n') == 'error\n'

        for amount, digits in [(0, 123), (4, 123), (8, 248), (9, 333), (8, 333), (18, 123), (361, 888)]:
            steps = [int(d) for d in str(digits)]
            counts = [1] + [0] * amount
            for at in range(1, amount + 1):
                counts[at] = sum(counts[at-step] for step in steps if step <= at)
            assert run('lab8_3', f'{amount} {digits}\n') == f'{counts[amount]}\n'
        assert run('lab8_3', '100 111\n', 1) == 'error\n'
        assert run('lab8_3', '8 203\n', 1) == 'error\n'

        # A stack evaluates balanced score sequences independently of digit-range
        # recursion: concatenations add, nested pairs multiply by five.
        def balanced_score(word):
            stack = [0]
            for digit in word:
                if digit == '1':
                    stack.append(0)
                else:
                    inner = stack.pop()
                    stack[-1] += 1 if inner == 0 else inner * 5
            return stack[0]

        for length in range(1, 5):
            for digits in itertools.product('12', repeat=2*length):
                word = ''.join(digits)
                balance = 0
                valid = True
                for digit in word:
                    balance += 1 if digit == '1' else -1
                    if balance < 0:
                        valid = False
                        break
                if valid and balance == 0:
                    assert run('lab8_4', word + '\n') == f'{balanced_score(word)}\n'
        for number, expected in [(0, 0), (1, 0), (2, 0), (1112, 1), (212, 1), (1213, 1), (132, 0), (12121122, 7)]:
            assert run('lab8_4', f'{number}\n') == f'{expected}\n'
        for lab in ['lab8_3', 'lab8_4']:
            source = (ROOT / '2024/lab08' / f'{lab}.cpp').read_text(encoding='utf-8')
            source = re.sub(r'//[^\n]*', '', source)
            assert 'vector' not in source and 'string' not in source

        for index in [0, 4, 9]:
            assert run('lab9_1', f'{index}\n').endswith(f'{1 + 2*index}\n')
        retry = run('lab9_1', '12\n-1\nabc\n5\n')
        assert retry.count('Invalid index.') == 3 and retry.endswith('11\n')
        for values, begin, end in [(['-1.5','-3.5','3.0','-2.4','-1.8','-3.0','4.5','5.7','-8.9','3.4'],2,5),
                                   (['1.15','2.35','3.45'],0,2), (['-0.1'],0,0),
                                   (['2147483647.0','2147483647.0'],0,1)]:
            expected = sum(Decimal(n).quantize(Decimal('.1'), rounding=ROUND_HALF_UP) for n in values[begin:end+1])
            data = f'{len(values)}\n' + ' '.join(values) + f'\n{begin} {end}\n'
            assert run('lab9_2', data).endswith(f'[{begin}, {end}] is: {expected:.1f}\n')
        invalid = run('lab9_2', '0\n3\n1 2 3\n2 1\n0 2\n')
        assert invalid.count('Wrong Input!') == 2 and invalid.endswith('[0, 2] is: 6.0\n')

        for sequence in [[1], [2,1,3], [-1,4,0], [6,5,4,3,2,1]]:
            expected = ''.join(' '.join(map(str, p)) + '\n' for p in itertools.permutations(sorted(sequence)))
            data = f'{len(sequence)}\n' + ' '.join(map(str, sequence)) + '\n'
            assert run('lab9_3', data) == expected
        assert run('lab9_3', '3\n1 1 2\n', 1) == 'error\n'

        rng = random.Random(2024)
        images = [[[100]*3 for _ in range(3)], [[255]*5 for _ in range(4)],
                  [[rng.randrange(256) for _ in range(6)] for _ in range(5)]]
        for bit in range(8):
            grid = [[0]*3 for _ in range(3)]
            grid[1][1] = 100
            neighbors = [(r, c) for r in range(3) for c in range(3) if (r,c) != (1,1)]
            r,c = neighbors[bit]
            grid[r][c] = 101
            images.append(grid)
        for grid in images:
            rows, cols = len(grid), len(grid[0])
            output = [[0]*cols for _ in range(rows)]
            offsets = [(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]
            for r in range(1, rows-1):
                for c in range(1, cols-1):
                    output[r][c] = sum((grid[r+dr][c+dc] >= grid[r][c]) << bit
                                       for bit, (dr,dc) in enumerate(offsets))
            data = f'{rows} {cols}\n' + '\n'.join(' '.join(map(str, row)) for row in grid) + '\n'
            expected = 'LBP Matrix:\n' + ''.join(''.join(f'{n:5d}' for n in row) + '\n' for row in output)
            assert run('lab9_4', data).endswith(expected)
        assert 'at least 3x3' in run('lab9_4', '3 2\n')
        invalid = run('lab9_4', '3 3\n999\n0 0 0\n0 0 0\n0 0 0\n')
        assert 'Invalid input detected!' in invalid
        assert '  255' in invalid
    print(f'2024 Labs 6-9: 15 programs and 2 definition variants compiled without warnings; {checks} executions passed.')


if __name__ == '__main__':
    main()
