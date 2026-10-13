"""Compile and check the six provided 2021 midterm problems with independent models."""
import argparse
import collections
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
parser.add_argument('tests', nargs='*', help='Optional unittest method names for a focused run.')
options = parser.parse_args()
repo = Path(__file__).resolve().parents[1]
source_folder = repo / 'exams' / '2021' / 'midterm'


class MidtermTests(unittest.TestCase):
    scenarios = 0
    model_cases = 0

    @classmethod
    def setUpClass(cls):
        compiler = shutil.which(options.cxx) or options.cxx
        cls.environment = dict(os.environ)
        if os.name == 'nt':
            cls.environment['PATH'] = str(Path(compiler).resolve().parent) + os.pathsep + cls.environment.get('PATH', '')
        cls.temporary = tempfile.TemporaryDirectory(prefix='exam-midterm-2021-')
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.programs = {}
        for letter in 'abcdef':
            source = source_folder / f'problem_{letter}.cpp'
            executable = Path(cls.temporary.name) / (source.stem + ('.exe' if os.name == 'nt' else ''))
            compiled = subprocess.run([compiler, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic', str(source), '-o', str(executable)],
                                      capture_output=True, text=True, encoding='utf-8', errors='replace', env=cls.environment, timeout=30)
            if compiled.returncode or compiled.stderr:
                raise AssertionError(f'{source.name}: compilation failed or warned:\n{compiled.stderr}')
            cls.programs[letter] = executable

    def run_program(self, letter, data, timeout=5):
        type(self).scenarios += 1
        run = subprocess.run([str(self.programs[letter])], input=data, capture_output=True,
                             text=True, encoding='utf-8', env=self.environment, timeout=timeout)
        self.assertEqual(run.returncode, 0, run.stderr)
        self.assertEqual(run.stderr, '')
        return run.stdout

    def test_a_exam_sample(self):
        self.assertEqual(self.run_program('a', '5\n16\n5\n15\n0\n0\n'), 'Chick 2 Rabbit 3\nno\nBye\n')

    def test_a_exhaustive_small_inputs_and_large_edges(self):
        cases = [(heads, legs) for heads in range(21) for legs in range(86) if (heads, legs) != (0, 0)]
        expected = []
        for heads, legs in cases:
            solutions = [(chicks, rabbits) for chicks in range(heads + 1) for rabbits in range(heads + 1)
                         if chicks + rabbits == heads and chicks * 2 + rabbits * 4 == legs]
            expected.append(f'Chick {solutions[0][0]} Rabbit {solutions[0][1]}' if solutions else 'no')
        large = [(1073741823, 2147483646, 'Chick 1073741823 Rabbit 0'),
                 (536870911, 2147483644, 'Chick 0 Rabbit 536870911'),
                 (2147483647, 2147483647, 'no'), (0, 1, 'no')]
        data = ''.join(f'{heads} {legs}\n' for heads, legs in cases)
        data += ''.join(f'{heads} {legs}\n' for heads, legs, answer in large) + '0 0\n'
        expected += [answer for heads, legs, answer in large] + ['Bye']
        self.assertEqual(self.run_program('a', data), '\n'.join(expected) + '\n')
        type(self).model_cases += len(cases) + len(large)

    @staticmethod
    def summing_model(number):
        expression = 'n'
        lines = []
        while number >= 10:
            expression = f'f({expression})'
            digits = str(number)
            number = sum(map(int, digits))
            lines.append(expression + '=' + '+'.join(digits) + '=' + str(number))
        lines.append('The summing digit is:' + str(number))
        return '\n'.join(lines) + '\n'

    def test_b_procedures_including_zero_digits(self):
        values = [0, 1, 9, 10, 99, 100, 1000000000, 1000102000, 1234567892, 2147483647]
        rng = random.Random(202101)
        values += [rng.randrange(2147483648) for _ in range(15)]
        for number in values:
            self.assertEqual(self.run_program('b', f'{number}\n'), self.summing_model(number))
        self.assertEqual(self.run_program('b', '-5\n2147483648\n1234567892\n'),
                         'You should input a positive integer\n' * 2 + self.summing_model(1234567892))
        type(self).model_cases += len(values) + 1

    def test_c_hanoi_legal_and_minimal_for_every_allowed_size(self):
        for disks in range(3, 11):
            output = self.run_program('c', f'{disks}\n')
            lines = output.splitlines()
            self.assertEqual(len(lines), 2**disks - 1)
            rods = {'A': list(range(disks, 0, -1)), 'B': [], 'C': []}
            for line in lines:
                matched = re.fullmatch(r'move disk (\d+) from ([ABC]) to ([ABC])', line)
                self.assertIsNotNone(matched, line)
                disk, source, target = matched.groups()
                disk = int(disk)
                self.assertTrue(rods[source])
                self.assertEqual(rods[source][-1], disk)
                self.assertTrue(not rods[target] or rods[target][-1] > disk)
                rods[target].append(rods[source].pop())
            self.assertEqual(rods, {'A': [], 'B': [], 'C': list(range(disks, 0, -1))})
        source = (source_folder / 'problem_c.cpp').read_text(encoding='utf-8')
        self.assertRegex(source.split('int main', 1)[0], r'void\s+Hanoi\([^;]+\);')
        self.assertRegex(source.split('int main', 1)[1], r'void\s+Hanoi\([^;]+\)\s*\{')
        type(self).model_cases += 8

    def test_b_huge_token_at_eof_and_before_valid_input(self):
        huge = '9' * 80
        error = 'You should input a positive integer\n'
        self.assertEqual(self.run_program('b', huge), error)
        self.assertEqual(self.run_program('b', huge + ' 1234567892\n'), error + self.summing_model(1234567892))
        self.assertEqual(self.run_program('b', '1x +10\n'), error + self.summing_model(10))
        type(self).model_cases += 3

    @staticmethod
    def armstrong_multiset_model():
        # Independent sorted tuples + Counter verification, not the C++ count-tree recursion.
        result = set()
        for length in range(1, 11):
            powers = [digit**length for digit in range(10)]
            for digits in itertools.combinations_with_replacement(range(10), length):
                value = sum(powers[digit] for digit in digits)
                if value <= 2147483647 and collections.Counter(map(int, str(value))) == collections.Counter(digits):
                    result.add(value)
        return sorted(result)

    @staticmethod
    def armstrong_output(values):
        return ' & '.join(map(str, values)) + ' \n' if values else 'none\n'

    def test_d_full_int_range_and_independent_small_scan(self):
        expected = self.armstrong_multiset_model()
        small_scan = [number for number in range(100001)
                      if sum(int(digit)**len(str(number)) for digit in str(number)) == number]
        self.assertEqual([value for value in expected if value <= 100000], small_scan)
        self.assertEqual(self.run_program('d', '0 2147483647\n', timeout=5), self.armstrong_output(expected))
        for lower, upper in [(100, 999), (10, 99), (0, 0), (0, 9), (153, 153), (154, 154),
                             (2147483647, 2147483647), (999, 100)]:
            self.assertEqual(self.run_program('d', f'{lower} {upper}\n'),
                             self.armstrong_output([value for value in expected if lower <= value <= upper]))
        type(self).model_cases += 100001 + 9

    @staticmethod
    def revenue_model(values):
        average = (min(values) + max(values)) // 2
        return (f'Decimal {average}\nOctet {average:o}\nBinary {average:b}\n'
                + ('The country is rich\n' if average >= 63 else 'Come on\n'))

    def test_e_sample_reloads_count_and_data(self):
        data = '3\n10\n15\n21\n4\n23\n10\n12\n30\n'
        self.assertEqual(self.run_program('e', data), 'Input again!\n' + self.revenue_model([23, 10, 12, 30]))
        self.assertEqual(self.run_program('e', '0\n2\n0\n1\n1\n63\n'),
                         'Input again!\nInput again!\n' + self.revenue_model([63]))
        type(self).model_cases += 2

    def test_e_threshold_zero_and_32_bit_sum(self):
        for values in [[0], [62], [63], [64], [2147483647, 2147483647], [0, 2147483646], [100, 102, 1000]]:
            self.assertEqual(self.run_program('e', str(len(values)) + '\n' + '\n'.join(map(str, values)) + '\n'),
                             self.revenue_model(values))
        values = [0] + list(range(99998)) + [2147483646]
        self.assertEqual(self.run_program('e', str(len(values)) + '\n' + ' '.join(map(str, values)) + '\n'), self.revenue_model(values))
        type(self).model_cases += 8

    @staticmethod
    def stamp_model(maximum_stamps, count):
        # Enumerate entire denomination sets within a universal mathematical bound.
        # Reachable sums are built by exactly 0..h stamps, independent of minimum-coin DP.
        if count == 1:
            return maximum_stamps
        last_bound = maximum_stamps
        for _ in range(count - 2):
            last_bound = maximum_stamps * (last_bound + 1)
        last_bound += 1
        best = 0
        for tail in itertools.combinations(range(2, last_bound + 1), count - 1):
            denominations = (1,) + tail
            layer = {0}
            reachable = {0}
            for _ in range(maximum_stamps):
                layer = {value + denomination for value in layer for denomination in denominations}
                reachable.update(layer)
            gap = 1
            while gap in reachable:
                gap += 1
            best = max(best, gap - 1)
        return best

    def test_f_all_36_legal_pairs_and_exhaustive_small_optima(self):
        pairs = [(h, k) for h in range(1, 9) for k in range(1, 9) if h + k <= 9]
        data = ''.join(f'{h} {k}\n' for h, k in pairs) + '0 0\n'
        output = self.run_program('f', data, timeout=10)
        self.assertEqual(len(output.splitlines()), len(pairs))
        answers = dict(zip(pairs, map(int, output.splitlines())))
        for (h, k), answer in answers.items():
            self.assertGreaterEqual(answer, h * k)
            self.assertLessEqual(answer, sum(h**exponent for exponent in range(1, k + 1)))
            if h + k <= 6:
                self.assertEqual(answer, self.stamp_model(h, k), (h, k))
            if k == 1: self.assertEqual(answer, h)
            if h == 1: self.assertEqual(answer, k)
            if (h + 1, k) in answers: self.assertGreaterEqual(answers[h + 1, k], answer)
            if (h, k + 1) in answers: self.assertGreaterEqual(answers[h, k + 1], answer)
        self.assertEqual(self.run_program('f', '3 2\n5 1\n3 2\n0 0\n'), '7\n5\n7\n')
        self.assertEqual(self.run_program('f', '0 0\n'), '')
        type(self).model_cases += len(pairs) + 4


if __name__ == '__main__':
    suite = (unittest.defaultTestLoader.loadTestsFromNames(options.tests, module=sys.modules[__name__])
             if options.tests else unittest.defaultTestLoader.loadTestsFromTestCase(MidtermTests))
    result = unittest.TextTestRunner(verbosity=2).run(suite)
    print(f'2021 midterm: 6 exercises compiled; {MidtermTests.scenarios} executable scenarios; '
          f'{MidtermTests.model_cases} independent model cases checked.')
    sys.exit(not result.wasSuccessful())
