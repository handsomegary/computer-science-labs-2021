"""Self-contained C++11 regression tests for the supplied 2024 Labs 3-5 Reviews."""
import argparse
import datetime
import itertools
import os
from pathlib import Path
import random
import re
import shutil
import subprocess
import sys
import tempfile
import unittest

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
options = parser.parse_args()
repo = Path(__file__).resolve().parents[1]


class Labs2024Tests(unittest.TestCase):
    scenarios = 0

    @classmethod
    def setUpClass(cls):
        compiler = shutil.which(options.cxx) or options.cxx
        cls.environment = dict(os.environ)
        if os.name == 'nt':
            cls.environment['PATH'] = str(Path(compiler).resolve().parent) + os.pathsep + cls.environment.get('PATH', '')
        cls.temporary = tempfile.TemporaryDirectory(prefix='2024-labs-3-5-')
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.programs = {}
        for source in sorted((repo / '2024').glob('lab0[3-5]/lab*.cpp')):
            executable = Path(cls.temporary.name) / (source.stem + ('.exe' if os.name == 'nt' else ''))
            result = subprocess.run([compiler, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic',
                                     str(source), '-o', str(executable)],
                                    capture_output=True, text=True, encoding='utf-8', errors='replace',
                                    env=cls.environment, timeout=30)
            if result.returncode or result.stderr:
                raise AssertionError(f'{source}: compilation failed or warned:\n{result.stderr}')
            cls.programs[source.stem] = executable
        if len(cls.programs) != 12:
            raise AssertionError(f'Expected 12 exercises; found {len(cls.programs)}')

    def run_program(self, program, data, successful=True):
        type(self).scenarios += 1
        result = subprocess.run([str(self.programs[program])], input=data, capture_output=True,
                                text=True, encoding='utf-8', env=self.environment, timeout=4)
        if successful:
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual(result.stderr, '')
        else:
            self.assertNotEqual(result.returncode, 0)
            self.assertTrue(result.stderr)
        return result.stdout

    def test_candy_open_and_close(self):
        opening = 'The candy bar is open!\nHow many candy do you want to take: '
        closing = 'The candy bar is closed!\n'
        self.assertEqual(self.run_program('lab3_1', '10\n3\n7\n'), opening * 2 + closing)
        self.assertEqual(self.run_program('lab3_1', '0\n'), closing)
        self.assertEqual(self.run_program('lab3_1', '4\n0\n8\n'), opening * 2 + closing)
        self.assertIn('Invalid candy count. Enter again: ', self.run_program('lab3_1', '4\n-1\n4\n'))
        self.assertTrue(self.run_program('lab3_1', '9223372036854775807\n9223372036854775807\n').endswith(closing))

    def test_height_thresholds(self):
        for ride, minimum in [(1, 140), (2, 120), (3, 100)]:
            for heights in [(minimum - 1, minimum, minimum + 1), (minimum,) * 3, (0,) * 3]:
                expected = sum(height >= minimum for height in heights)
                self.assertEqual(self.run_program('lab3_2', ' '.join(map(str, heights)) + f' {ride}\n'), f'{expected}\n')

    def test_palindromes_with_safe_large_integers(self):
        values = [0, 1, 10, 11, 121, 16461, 12321, 12021, 1001, 10001,
                  9223372036854775807, 8999999999999999998, -121, -9223372036854775808]
        rng = random.Random(113011)
        values += [rng.randrange(0, 2**63) for _ in range(15)]
        for value in values:
            expected = 'YES' if value >= 0 and str(value) == str(value)[::-1] else 'NO'
            self.assertEqual(self.run_program('lab3_3', f'{value}\n'), expected + '\n')

    def test_bomb_range_and_round_count(self):
        self.assertEqual(self.run_program('lab3_4', '50\n65\n30\n50\n'),
                         'Enter the bomb number (0~100): Range 0~100: Range 0~65: Range 30~65: '
                         'Bomb number: 50\nRounds: 3\n')
        output = self.run_program('lab3_4', '0\n100\n1\n0\n1\n')
        self.assertEqual(output.count('Out of range! Please enter again: '), 3)
        self.assertTrue(output.endswith('Bomb number: 1\nRounds: 1\n'))
        output = self.run_program('lab3_4', '50\n65\n65\n50\n')
        self.assertTrue(output.endswith('Bomb number: 50\nRounds: 2\n'))

    @staticmethod
    def deposits(output):
        return [(int(year), float(amount)) for year, amount in
                re.findall(r'^\s*(\d+)\s+(\d+\.\d{2})\s*$', output, re.MULTILINE)]

    def test_annual_interest_review_example(self):
        output = self.run_program('lab4_1', '1000 0.05\n')
        expected = [1050.00, 2152.50, 3310.12, 4525.63, 5801.91,
                    7142.01, 8549.11, 10026.56, 11577.89, 13206.79]
        self.assertEqual(self.deposits(output), list(enumerate(expected, 1)))
        self.assertEqual(self.deposits(self.run_program('lab4_1', '100 0\n')),
                         [(year, float(year * 100)) for year in range(1, 11)])
        self.assertEqual(self.deposits(self.run_program('lab4_1', '0 1\n')),
                         [(year, 0.0) for year in range(1, 11)])

    def test_company_comparison_and_validation(self):
        output = self.run_program('lab4_2', '0.05 0.04 0.03\n1\n1000\n2\n1000\n3\n1000\n4\n')
        tables = self.deposits(output)
        self.assertEqual(len(tables), 30)
        for offset, rate in [(0, .05), (10, .04), (20, .03)]:
            balance = 0
            for year in range(1, 11):
                balance = (balance + 12000) * (1 + rate)
                self.assertEqual(tables[offset + year - 1][0], year)
                self.assertAlmostEqual(tables[offset + year - 1][1], balance, delta=.00501)
        self.assertIn('1. Andy company (5.00%)', output)
        output = self.run_program('lab4_2', '-0.1\n1.1\n0\n1\n0.5\n9\n4\n')
        self.assertEqual(output.count('Out of range, interest rate should be in the range [0.00, 1.00]'), 2)
        self.assertIn('Invalid selection.', output)

    def test_luggage_against_exhaustive_bounded_search(self):
        rng = random.Random(113015)
        cases = [(55, (0, 0, 3, 1, 1)), (30, (0, 0, 3, 1, 0)), (0, (0,) * 5),
                 (1, (0,) * 5), (5, (5, 0, 0, 0, 0)), (10, (0, 1, 0, 0, 0))]
        for _ in range(100):
            cases.append((rng.randrange(200), tuple(rng.randrange(5) for _ in range(5))))
        capacities = (1, 5, 10, 25, 50)
        for weight, counts in cases:
            reachable = {sum(count * size for count, size in zip(combination, capacities))
                         for combination in itertools.product(*(range(count + 1) for count in counts))}
            expected = 'YES' if weight in reachable else 'NO'
            data = ' '.join(map(str, (weight,) + counts)) + '\n'
            with self.subTest(weight=weight, counts=counts):
                self.assertEqual(self.run_program('lab4_3', data), expected + '\n')
        maximum = 9223372036854775807
        self.assertEqual(self.run_program('lab4_3', f'{maximum} {maximum} {maximum} {maximum} {maximum} {maximum}\n'), 'YES\n')
        self.assertEqual(self.run_program('lab4_3', f'{maximum} 0 0 0 0 {maximum}\n'), 'NO\n')

    def test_banking_loan_kept_until_successful_repayment(self):
        output = self.run_program('lab4_4', '4\n3\n100\n4\n1\n1\n10\n4\n1\n4\n5\n')
        self.assertEqual(output.count('No outstanding loan to repay.'), 2)
        self.assertIn('Insufficient balance to repay the loan.', output)
        self.assertIn('Total amount to repay: $105.00', output)
        self.assertIn('Balance after repayment: $5.00', output)
        output = self.run_program('lab4_4', '1\n50\n2\n60\n2\n25\n3\n100\n3\n4\n0\n5\n')
        self.assertIn('Insufficient balance to withdraw.', output)
        self.assertIn('Repay the outstanding loan before borrowing again.', output)
        self.assertIn('Balance after repayment: $25.00', output)

    def test_calculator_switch_and_overflow(self):
        output = self.run_program('lab5_1', '?\n+ 2147483647 2147483647\n- 0 1\n* 2147483647 2147483647\n^ 2 62\n^ 0 0\n^ 1 2147483647\n^ 0 2147483647\n^ 2 63\ne\n')
        values = re.findall(r'Calculation result: a [^\n]+ = (-?\d+)', output)
        self.assertEqual(list(map(int, values)), [4294967294, -1, 4611686014132420609,
                                                4611686018427387904, 1, 1, 0])
        self.assertIn('Incorrect mathematical operator entered. Enter a new one.', output)
        self.assertIn('Calculation result is out of range.', output)
        self.assertTrue(output.endswith('Goodbye~\n'))
        self.assertIn('a + b = 5', self.run_program('lab5_1', '+ -1 1\n2 3\ne\n'))

    def test_cookie_combinations_and_order(self):
        for total, quantities in [(12, (6, 2, 3)), (1, (2, 3, 6)), (0, (1, 2, 3)), (15, (4, 7, 1)), (30, (5, 9, 2))]:
            output = self.run_program('lab5_2', f'{total}\n' + ' '.join(map(str, quantities)) + '\n')
            lists = [list(map(int, body.split(','))) if body else []
                     for body in re.findall(r'^\[([\d,]*)\]$', output, re.MULTILINE)]
            first, second, third = sorted(quantities)
            expected = []
            for a in range(total // first + 1):
                for b in range(total // second + 1):
                    for c in range(total // third + 1):
                        if a * first + b * second + c * third == total:
                            expected.append((a, a + b + c, [first] * a + [second] * b + [third] * c))
            expected.sort(key=lambda item: item[:2])
            self.assertEqual(lists, [item[2] for item in expected])
            if not expected:
                self.assertIn('There is no way to finish the cookies.', output)
        output = self.run_program('lab5_2', '12\n2 2 3\n0 2 3\n2 11 3\n2 3 6\n')
        self.assertEqual(output.count('Wrong quantities. Enter three quantities again.'), 3)

    def test_juice_review_date_and_calendar_boundaries(self):
        cases = [(datetime.date(2024, 9, 3), 47, '0512002'),
                 (datetime.date(2024, 12, 31), 44, '6666666'),
                 (datetime.date(2024, 2, 28), 7, '1111111'),
                 (datetime.date(2100, 2, 28), 7, '1111111'),
                 (datetime.date(2400, 2, 28), 7, '1111111')]
        rng = random.Random(113019)
        for _ in range(30):
            start = datetime.date(rng.randrange(2024, 2500), rng.randrange(1, 13), rng.randrange(1, 29))
            schedule = ''.join(str(rng.randrange(0, 7)) for _ in range(7))
            if sum(map(int, schedule)) >= 5:
                cases.append((start, rng.randrange(1, 400), schedule))
        for start, bottles, schedule in cases:
            finish = start
            remaining = bottles
            while True:
                remaining -= int(schedule[finish.weekday()])
                if remaining <= 0: break
                finish += datetime.timedelta(days=1)
            data = f'{start.year} {start.month} {start.day} {start.isoweekday()}\n{bottles}\n{schedule}\n'
            output = self.run_program('lab5_3', data)
            abbreviation = ['Mon.', 'Tue.', 'Wed.', 'Thu.', 'Fri.', 'Sat.', 'Sun.'][finish.weekday()]
            self.assertTrue(output.endswith(f'Finish all the juice on {finish:%Y/%m/%d} ({abbreviation}).\n'), output)
        output = self.run_program('lab5_3', '2024 9 3 2\n47\n5975110\n0000001\n66666666\n0512002\n')
        self.assertEqual(output.count('Wrong 7-digit number entered. Please enter again!'), 3)
        self.assertTrue(output.endswith('Finish all the juice on 2024/10/03 (Thu.).\n'))
        distant = datetime.date(2024, 1, 1) + datetime.timedelta(days=1999999)
        abbreviation = ['Mon.', 'Tue.', 'Wed.', 'Thu.', 'Fri.', 'Sat.', 'Sun.'][distant.weekday()]
        self.assertTrue(self.run_program('lab5_3', '2024 1 1 1\n2000000\n1111111\n').endswith(
            f'Finish all the juice on {distant:%Y/%m/%d} ({abbreviation}).\n'))
        self.assertTrue(self.run_program('lab5_3', '2024 1 1 1\n2147483647\n1111111\n').endswith(' (Mon.).\n'))

    def test_monopoly_turns_corners_rewards_and_winner(self):
        rng = random.Random(113020)
        for sequence in ['.', 'a', 'A', 'a.Bz', 'ABCDEFGH']:
            height, width = 6, 7
            route = 2 * (height + width - 2)
            positions, scores, moves, records = [0, 0], [100, 100], [], []
            while all(position < route for position in positions):
                for player in (0, 1):
                    steps = rng.randrange(1, 7)
                    moves.append(steps)
                    positions[player] += steps
                    if positions[player] in (height - 1, height + width - 2, 2 * height + width - 3):
                        positions[player] -= 2
                    positions[player] = min(positions[player], route)
                    if positions[player] < route:
                        symbol = sequence[(positions[player] - 1) % len(sequence)]
                        if symbol.islower(): scores[player] += ord(symbol) - ord('a') + 1
                        elif symbol.isupper(): scores[player] -= ord(symbol) - ord('A') + 1
                records.append((tuple(positions), tuple(scores)))
            output = self.run_program('lab5_4', f'{height} {width}\n{sequence}\n' + '\n'.join(map(str, moves)) + '\n')
            actual_positions = [tuple(map(int, row)) for row in re.findall(r'A and B are at position (\d+) and (\d+)', output)]
            actual_scores = [tuple(map(int, row)) for row in re.findall(r'A and B have score (-?\d+) and (-?\d+)', output)]
            self.assertEqual(list(zip(actual_positions, actual_scores)), records)
            ending = ('Player A wins the game!' if scores[0] > scores[1] else
                      'Player B wins the game!' if scores[1] > scores[0] else 'The two players are tied!')
            self.assertTrue(output.endswith(ending + '\n'))
        # Landing on the first corner at position 2 returns A to start.
        output = self.run_program('lab5_4', '3 3\na\n0\n7\n2\n1\n6\n6\n6\n6\n')
        self.assertEqual(output.count('Out of the bound. Enter again.'), 2)
        self.assertIn('A and B are at position 0 and 1', output)
        self.assertTrue(output.endswith('The two players are tied!\n'))

    def test_eof_and_invalid_inputs_are_finite(self):
        for program, data in [('lab3_1', '4\n'), ('lab3_4', ''), ('lab4_2', ''),
                              ('lab4_4', ''), ('lab5_1', ''), ('lab5_2', '12\n'),
                              ('lab5_3', '2024 1 1 1\n10\n'), ('lab5_4', '3 3\n.\n')]:
            self.run_program(program, data)
        for program, data in [('lab3_1', '-1\n'), ('lab3_2', '140 140 140 4\n'),
                              ('lab3_3', '9223372036854775808\n'), ('lab4_1', '-1 0.05\n'),
                              ('lab4_3', '1 0 0 -1 0 0\n'), ('lab5_2', '-1\n'),
                              ('lab5_3', '2100 2 29 1\n'), ('lab5_4', '2 3\n')]:
            self.run_program(program, data, successful=False)


if __name__ == '__main__':
    result = unittest.TextTestRunner(verbosity=2).run(unittest.defaultTestLoader.loadTestsFromTestCase(Labs2024Tests))
    print(f'2024 Labs 3-5: 12 exercises compiled; {Labs2024Tests.scenarios} program scenarios executed.')
    sys.exit(not result.wasSuccessful())
