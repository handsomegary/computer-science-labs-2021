"""Verify 2021 final A-F with independent geometric/partition/DP models."""
import argparse
from collections import Counter
from decimal import Decimal, ROUND_HALF_UP
import json
import os
from pathlib import Path
import random
import shutil
import subprocess
import tempfile


ROOT = Path(__file__).resolve().parents[1]
FOLDER = ROOT / 'exams/2021/final'


def spiral_order(row, column):
    """Closed-form index on the infinite spiral, not a walking simulation."""
    radius = max(abs(row), abs(column))
    if radius == 0:
        return 1
    maximum = (2*radius+1)**2
    if row == -radius:
        return maximum - radius + column
    if column == -radius:
        return maximum - 3*radius - row
    if row == radius:
        return maximum - 5*radius - column
    return maximum - 7*radius + row


def spiral(rows, columns, origin_row, origin_column):
    points = sorted((spiral_order(r-origin_row, c-origin_column), r, c)
                    for r in range(rows) for c in range(columns))
    grid = [[0]*columns for _ in range(rows)]
    for value, (_, r, c) in enumerate(points, 1):
        grid[r][c] = value
    width = len(str(rows*columns))
    return ''.join(' '.join(f'{v:0{width}d}' for v in line) + '\n' for line in grid)


def tree_postorder(values):
    """Partition input order at each root, without building pointer nodes."""
    if not values:
        return []
    pivot = values[0]
    return (tree_postorder([v for v in values[1:] if v < pivot])
            + tree_postorder([v for v in values[1:] if v > pivot]) + [pivot])


def stock_model(prices):
    cash, held = 0, float('-inf')
    for price in prices:
        cash, held = max(cash, held+price), max(held, cash-price)
    return int(cash)


def cipher_model(message, encrypt):
    result = bytearray(message)
    for i, value in enumerate(message):
        if value == 32:
            continue
        delta = 9 if i % 2 == 0 else -3
        result[i] = (value + (delta if encrypt else -delta)) % 256
    return bytes(result)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
    args = parser.parse_args()
    compiler = shutil.which(args.cxx) or args.cxx
    env = os.environ.copy()
    env['PATH'] = str(Path(compiler).resolve().parent) + os.pathsep + env.get('PATH', '')
    count = 0
    with tempfile.TemporaryDirectory(prefix='exam_2021_final_') as temporary:
        directory = Path(temporary)
        binaries = {}
        for letter in 'abcdef':
            name = f'problem_{letter}'
            binary = directory / (name + ('.exe' if os.name == 'nt' else ''))
            result = subprocess.run([compiler, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic',
                                     str(FOLDER / f'{name}.cpp'), '-o', str(binary)],
                                    text=True, capture_output=True, env=env)
            assert result.returncode == 0 and not result.stderr, f'{name}: {result.stderr}'
            binaries[name] = binary

        def run_bytes(name, data, status=0):
            nonlocal count
            result = subprocess.run([str(binaries[name])], input=data, capture_output=True,
                                    cwd=directory, env=env, timeout=10)
            assert result.returncode == status, f'{name}: {result.returncode}, {result.stdout!r}, {result.stderr!r}'
            assert not result.stderr, result.stderr
            count += 1
            return result.stdout.replace(b'\r\n', b'\n')

        def run(name, data, status=0):
            return run_bytes(name, data.encode(), status).decode()

        # Recorded examples include all prompts and are also checked by root's
        # synchronization/verification tools.
        samples = json.loads((FOLDER / 'solutions/samples.json').read_text(encoding='utf-8'))
        for sample in samples:
            for filename, contents in sample.get('files', {}).items():
                destination = directory / filename
                assert destination.resolve().is_relative_to(directory.resolve())
                destination.parent.mkdir(parents=True, exist_ok=True)
                destination.write_text(contents, encoding='utf-8')
            name = Path(sample['source']).stem
            assert run(name, sample['stdin'], sample.get('returncode', 0)) == sample['stdout']
            assert sample.get('stderr', '') == ''

        example = '20 16 07 08 09\n19 15 06 01 02\n18 14 05 04 03\n17 13 12 11 10\n'
        assert run('problem_a', '4 5\n1 3\n') == example
        assert run('problem_a', 'Width,Length\n4 5\nx,y\n1 3\n') == example
        randomizer = random.Random(2021)
        dimensions = [(3,3),(3,31),(31,3),(31,31),(4,5),(10,22)]
        for rows, cols in dimensions:
            origins = {(0,0),(0,cols-1),(rows-1,0),(rows-1,cols-1),(rows//2,cols//2)}
            for x,y in origins:
                assert run('problem_a', f'{rows} {cols} {x} {y}\n') == spiral(rows,cols,x,y)
        for _ in range(25):
            rows, cols = randomizer.randrange(3,32), randomizer.randrange(3,32)
            x, y = randomizer.randrange(rows), randomizer.randrange(cols)
            assert run('problem_a', f'{rows} {cols} {x} {y}\n') == spiral(rows,cols,x,y)
        assert run('problem_a', '3 3 3 0\n', 1) == 'error\n'

        trees = [[26,17,41,14,21,30,47], list(range(1,8)), list(range(7,0,-1)),
                 [-2147483648,2147483647,0,-1,1,-2,2]]
        trees += [randomizer.sample(range(-1000,1001),7) for _ in range(40)]
        for values in trees:
            expected = ' '.join(map(str, tree_postorder(values))) + '\n'
            assert run('problem_b', ' '.join(map(str,values)) + '\n') == expected
        assert run('problem_b', '1 2 3 4 5 6 6\n', 1) == 'error\n'
        assert run('problem_b', '2147483648 2 3 4 5 6 7\n', 1) == 'error\n'

        stocks = [[7,1,5,3,6,4],[10,9,8,7],[0],[0,104,0,104],[104]*312]
        stocks += [[randomizer.randrange(105) for _ in range(randomizer.randrange(1,313))] for _ in range(25)]
        # Outside the official literal price limit, exercise the deliberate
        # 64-bit extension and a result greater than INT_MAX.
        stocks += [[0,2147483647]*156]
        for values in stocks:
            (directory/'model_stock.txt').write_text('sample\nprices: ' + ' '.join(map(str,values)) + '\n', encoding='utf-8')
            assert run('problem_c','model_stock.txt\n') == f'File: Maximum profit: {stock_model(values)}\n'
        assert run('problem_c', 'missing_stock.txt\n', 1) == 'File: Cannot open file.\n'
        (directory/'bad_stock.txt').write_text('sample\nprices: 1 -1 3\n', encoding='utf-8')
        assert run('problem_c','bad_stock.txt\n',1) == 'File: Invalid stock data.\n'
        (directory/'bad_stock.txt').write_text('sample\nprices: ' + '0 '*313+'\n', encoding='utf-8')
        assert run('problem_c','bad_stock.txt\n',1) == 'File: Invalid stock data.\n'
        (directory/'bad_stock.txt').write_text('sample\nprices: 1 999999999999999999999999999999999999', encoding='utf-8')
        assert run('problem_c','bad_stock.txt\n',1) == 'File: Invalid stock data.\n'

        words = [('anagram','naagrma'),('rat','cat'),('a','a'),('aab','abb'),('triangle','integral'),
                 ('a'*1000000,'a'*1000000)]
        for _ in range(30):
            first = ''.join(randomizer.choice('abcdefxyz') for _ in range(randomizer.randrange(1,101)))
            chars = list(first)
            randomizer.shuffle(chars)
            second = ''.join(chars)
            words.append((first,second))
            words.append((first,second+'a'))
        for first,second in words:
            expected = "Yes! It's anagram.\n" if Counter(first)==Counter(second) else 'No! It is not anagram.\n'
            assert run('problem_d',first+' '+second+'\n') == expected

        menu = b'Welcome to encryption system!\nEnter 1 to encrypt\nEnter 2 to decrypt\n\nInput information: '
        messages = [b'', b'Test is a good message', b'  a  b c  ', b'1234567890', b'!$%&()*+-./:;<=>?@[]^_`{|}~']
        for _ in range(20):
            data = bytearray(randomizer.randrange(32,127) for _ in range(randomizer.randrange(1,201)))
            # The exam's preserved space is a reserved symbol. Avoid a
            # non-space character mapping to space in round-trip fixtures.
            for at in range(1,len(data),2):
                if data[at] == 35:
                    data[at] = 36
            messages.append(bytes(data))
        for message in messages:
            encoded = cipher_model(message, True)
            assert run_bytes('problem_e', b'1\n'+message+b'\n') == menu+b'Encrypted information: '+encoded+b'\n'
            assert run_bytes('problem_e', b'2\n'+encoded+b'\n') == menu+b'Decrypted information: '+message+b'\n'
        # Outside the stated round-trip domain, the reserved space collision is
        # intentional and documented: odd-index '#' maps to an unchanged space.
        assert run_bytes('problem_e', b'1\nA#\n') == menu+b'Encrypted information: J \n'
        assert run_bytes('problem_e', b'2\nJ \n') == menu+b'Decrypted information: A \n'
        assert run('problem_e','3\n',1).endswith('error\n')

        score_sets = [[30,40,50],[20,40,60,70],[70],[0],[100]*50,[0]*50,[1]+[0]*7,[69,70,71]]
        score_sets += [[randomizer.randrange(101) for _ in range(randomizer.randrange(1,51))] for _ in range(30)]
        for scores in score_sets:
            average = (Decimal(sum(scores))/Decimal(len(scores))).quantize(Decimal('.01'),rounding=ROUND_HALF_UP)
            value = format(average,'f').rstrip('0').rstrip('.')
            expected = 'Please enter the scores of all students:\navg = '+value+'\n'
            failed = [(i+1,s) for i,s in enumerate(scores) if s < 70]
            if failed:
                expected += 'fail:\n' + ''.join(f'{i}: {s}\n' for i,s in failed)
            assert run('problem_f','\n'.join(map(str,scores))+'\n') == expected
        for data in ['', '101\n', '-1\n', '70\n'*51, '1.5\n', '70 999999999999999999999999999999999999']:
            assert run('problem_f',data,1).endswith('error\n')
    print(f'2021 final A-F: 6 programs compiled without warnings; {count} executions passed.')


if __name__ == '__main__':
    main()
