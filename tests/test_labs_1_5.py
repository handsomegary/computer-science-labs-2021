"""Compile and verify 2021 Labs 1-5 using only the Python standard library."""
import argparse
import datetime
import itertools
import math
import os
from pathlib import Path
import random
import re
import shutil
import subprocess
import sys
import tempfile
import unittest


PARSER = argparse.ArgumentParser(description=__doc__)
PARSER.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
OPTIONS = PARSER.parse_args()
REPO = Path(__file__).resolve().parents[1]


class LabTests(unittest.TestCase):
    executions = 0

    @classmethod
    def setUpClass(cls):
        compiler = shutil.which(OPTIONS.cxx) or OPTIONS.cxx
        cls.environment = dict(os.environ)
        if os.name == 'nt':
            cls.environment['PATH'] = str(Path(compiler).resolve().parent) + os.pathsep + cls.environment.get('PATH', '')
        cls.temporary = tempfile.TemporaryDirectory(prefix='labs-1-5-')
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.programs = {}
        for source in sorted(REPO.glob('lab0[1-5]/lab*.cpp')):
            target = Path(cls.temporary.name) / (source.stem + ('.exe' if os.name == 'nt' else ''))
            result = subprocess.run(
                [compiler, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic', str(source), '-o', str(target)],
                capture_output=True, text=True, encoding='utf-8', errors='replace',
                env=cls.environment, timeout=30,
            )
            if result.returncode or result.stderr:
                raise AssertionError(f'{source.name}: compilation failed or warned:\n{result.stderr}')
            cls.programs[source.stem] = target
        if len(cls.programs) != 13:
            raise AssertionError(f'Expected 13 exercises, found {len(cls.programs)}')

    def run_program(self, name, data='', successful=True):
        type(self).executions += 1
        result = subprocess.run(
            [str(self.programs[name])], input=data, capture_output=True, text=True,
            encoding='utf-8', errors='strict', env=self.environment, timeout=3,
        )
        if successful:
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual(result.stderr, '')
        else:
            self.assertNotEqual(result.returncode, 0)
            self.assertTrue(result.stderr)
        return result.stdout

    def test_hello_and_introduction(self):
        self.assertEqual(self.run_program('lab1_1'), 'Hello\nworld!\n')
        output = self.run_program('lab1_2')
        self.assertTrue(output.startswith('My name is "<NAME>"\nI come from \\<SCHOOL>\\\n'))
        self.assertIn("My student ID is '<STUDENT_ID>'\n", output)
        self.assertIn('[Introduction to Computer I] course\n', output)
        art = output.split('\n\n')[1].splitlines()
        self.assertEqual(len(art), 9)
        self.assertTrue(all(len(line) == 40 for line in art))
        self.assertNotIn('using namespace std', (REPO / 'lab01/lab1_2.cpp').read_text(encoding='utf-8'))

    def test_temperature(self):
        prefix = 'Please input temperature value in Celsius degree: The corresponding value in Fahrenheit degree is: '
        for celsius, fahrenheit in [(25.5, '77.9'), (0, '32'), (-40, '-40'), (100, '212'), (-273.15, '-459.67')]:
            with self.subTest(celsius=celsius):
                self.assertEqual(self.run_program('lab2_1', f'{celsius}\n'), prefix + fahrenheit + '\n')

    def test_arithmetic_operations(self):
        prefix = 'Please input 2 different integers: \nPlease input the operation: \n'
        for first, second in [(8, 7), (-9, 4), (-2147483648, 2147483647), (2147483646, 2147483647)]:
            expected = [f'Summation is {first + second}', f'Multiplication is {first * second}',
                        f'Larger number is {max(first, second)}', f'Smaller number is {min(first, second)}']
            for operation, answer in enumerate(expected, 1):
                with self.subTest(first=first, second=second, operation=operation):
                    self.assertEqual(self.run_program('lab2_2', f'{first} {second} {operation}\n'), prefix + answer + '\n')

    def test_bmi_boundaries_and_sample(self):
        for weight, height, classification in [
            (18.49, 1, 'You need to eat more'), (18.5, 1, 'You are healthy'),
            (23.99, 1, 'You are healthy'), (24, 1, 'You need to control your diet'),
            (74.1, 1.706, 'You need to control your diet'),
        ]:
            with self.subTest(weight=weight, height=height):
                output = self.run_program('lab2_3', f'{weight} {height}\n')
                self.assertTrue(output.startswith('Please enter your weight: Please enter your height: Your BMI is '))
                self.assertTrue(output.endswith(classification + '\n'))
                value = float(re.search(r'Your BMI is (\S+)', output).group(1))
                self.assertAlmostEqual(value, weight / height ** 2, delta=0.0001)

    def test_sort_all_orders_and_integer_limits(self):
        for numbers in itertools.permutations([-2147483648, -1, 2147483647]):
            output = self.run_program('lab3_1', ' '.join(map(str, numbers)) + '\n')
            self.assertEqual(output, 'Please enter 3 different integers: \n'
                             'The sorting result from small to large is -2147483648->-1->2147483647\n')
        self.assertTrue(self.run_program('lab3_1', '2 2 1\n').endswith('1->2->2\n'))

    def test_factorial_entire_domain(self):
        for number in range(21):
            with self.subTest(number=number):
                self.assertEqual(self.run_program('lab3_2', f'{number}\n'),
                                 'Please enter a nonnegative integer: '
                                 f'The corresponding factorial is {math.factorial(number)}\n')

    def test_binary_examples_and_limits(self):
        for binary in ['0', '1', '101', '111', '1011', '1111', '101011', '111111',
                       '1101', '1000000000000000000', '1111111111111111111', '0000101']:
            with self.subTest(binary=binary):
                self.assertEqual(self.run_program('lab3_3', binary + '\n'),
                                 'Please input an unsigned binary number: '
                                 f'The corresponding decimal number is {int(binary, 2)}\n')

    def test_factorization(self):
        cases = {2: '2', 4: '2*2', 1260: '2*2*3*3*5*7', 97: '97',
                 2147483647: '2147483647', 2147483646: '2*3*3*7*11*31*151*331',
                 1073741824: '*'.join(['2'] * 30)}
        for number, factors in cases.items():
            with self.subTest(number=number):
                self.assertEqual(self.run_program('lab4_1', f'{number}\n'), f'Enter a number: {number} = {factors}\n')

    def test_factorization_recovers_invalid_input(self):
        self.assertEqual(self.run_program('lab4_1', '-222\n1\n1260\n'),
                         'Enter a number: Please enter a correct number: Please enter a correct number: '
                         '1260 = 2*2*3*3*5*7\n')
        self.assertTrue(self.run_program('lab4_1', 'x\n2147483648\n2\n').endswith('2 = 2\n'))

    def test_weekdays_against_independent_calendar(self):
        dates = [(2021, 1, 1), (2021, 10, 14), (2024, 2, 29), (2100, 3, 1),
                 (2400, 2, 29), (2421, 1, 1), (9999, 12, 31)]
        generator = random.Random(2021)
        for _ in range(100):
            year, month = generator.randint(2021, 9999), generator.randint(1, 12)
            day = generator.randint(1, 28)
            dates.append((year, month, day))
        for year, month, day in dates:
            with self.subTest(year=year, month=month, day=day):
                date = year * 10000 + month * 100 + day
                weekday = datetime.date(year, month, day).strftime('%A')
                self.assertEqual(self.run_program('lab4_2', f'{date}\n'),
                                 f'Enter a date (ex. 20211014): {date} is {weekday}.\n')
        for year, month, day in [(922337203685477, 12, 31), (922337203685200, 2, 29), (100000000002021, 1, 1)]:
            date = year * 10000 + month * 100 + day
            equivalent = 2021 + (year - 2021) % 400
            weekday = datetime.date(equivalent, month, day).strftime('%A')
            self.assertTrue(self.run_program('lab4_2', f'{date}\n').endswith(f'{date} is {weekday}.\n'))

    def test_date_validation_and_repeated_recovery(self):
        prompt = ('This date does not exist or is within the calculation range. '
                  'Please enter a correct date (ex. 20211014): ')
        invalid = ['20200101', '20210001', '20211301', '20210100', '20210431', '20210229',
                   '21000229', '20240230', '9223372036854775807', '9223372036854775808', 'x']
        output = self.run_program('lab4_2', '\n'.join(invalid + ['20211014']) + '\n')
        self.assertEqual(output, 'Enter a date (ex. 20211014): ' + prompt * len(invalid)
                         + '20211014 is Thursday.\n')
        text = (REPO / 'lab04/lab4_2.cpp').read_text(encoding='utf-8')
        self.assertIsNone(re.search(r'\bif\s*\(', text), 'Lab 4.2 requires switch instead of if/else')

    def test_diamond_examples_and_even_size_review_behavior(self):
        cases = [(3, '** **\n*   *\n** **\n'),
                 (5, '*** ***\n**   **\n*     *\n**   **\n*** ***\n'),
                 (4, '*** ***\n**   **\n*     *\n**   **\n*** ***\n')]
        for size, diamond in cases:
            self.assertEqual(self.run_program('lab5_1', f'{size}\n'), 'Enter the size of the diamond: ' + diamond)
        self.assertTrue(self.run_program('lab5_1', '2\n5\n').startswith('Enter the size of the diamond: Enter again: *** ***\n'))
        self.assertTrue(self.run_program('lab5_1', 'x\n2147483648\n3\n').endswith('** **\n*   *\n** **\n'))

    def test_pyramid_shape_and_continuous_sequence(self):
        self.assertEqual(self.run_program('lab5_2', '0\n'), 'Enter number of rows: ')
        self.assertEqual(self.run_program('lab5_2', '3\n'),
                         'Enter number of rows:            1\n       2   3   4\n   5   6   7   8   9\n')
        output = self.run_program('lab5_2', '11\n').removeprefix('Enter number of rows: ')
        lines = output.splitlines()
        self.assertEqual(len(lines), 11)
        self.assertEqual([len(line.split()) for line in lines], list(range(1, 22, 2)))
        self.assertEqual([int(value) for value in output.split()], list(range(1, 122)))

    def test_full_adder_entire_truth_table(self):
        combinations = list(itertools.product([0, 1], repeat=3))
        data = ''.join(' '.join(map(str, combination)) + '\n' for combination in combinations) + '-1\n'
        output = self.run_program('lab5_3', data)
        rows = [tuple(map(int, row)) for row in re.findall(r'^\s*(\d)\s+(\d)\s+(\d)\s+(\d)\s+(\d)\s*$', output, re.MULTILINE)]
        self.assertEqual(rows, [combination + (sum(combination) % 2, sum(combination) // 2) for combination in combinations])
        self.assertEqual(output.count('  A  B  Cin  SumCout\n'), 8)
        self.assertTrue(output.endswith('Enter a: Bye~\n'))

    def test_full_adder_retry_and_a_only_exit(self):
        output = self.run_program('lab5_3', '0 -1 0\n1 1 0\n-1\n')
        self.assertEqual(output.count('!!! Enter the inputs again !!!'), 1)
        self.assertIn('  1  1    0   0    1\n', output)
        output = self.run_program('lab5_3', '5 1 1\n-1\n')
        self.assertTrue(output.endswith('!!! Enter the inputs again !!!\nEnter a: Bye~\n'))
        self.assertTrue(self.run_program('lab5_3', 'x\n-1\n').endswith('Enter a: Bye~\n'))
        self.assertEqual(self.run_program('lab5_3', '-1\n'), 'Enter a: Bye~\n')

    def test_invalid_values_fail_without_invalid_calculations(self):
        for program, data in [('lab2_1', 'x'), ('lab2_2', '1 2 9'), ('lab2_3', '70 0'),
                              ('lab3_1', '1 2 x'), ('lab3_2', '21'), ('lab3_2', '-1'),
                              ('lab3_3', '102'), ('lab3_3', '-1'), ('lab3_3', '11111111111111111111'),
                              ('lab5_2', '-1')]:
            with self.subTest(program=program, data=data):
                self.run_program(program, data + '\n', successful=False)

    def test_eof_does_not_hang_interactive_loops(self):
        for program, data in [('lab4_1', ''), ('lab4_1', '1\n'), ('lab4_2', ''),
                              ('lab4_2', '20210229\n'), ('lab5_1', ''), ('lab5_1', '2\n'),
                              ('lab5_3', ''), ('lab5_3', '1\n'), ('lab5_3', '1 0\n')]:
            with self.subTest(program=program, data=data):
                self.run_program(program, data)


if __name__ == '__main__':
    suite = unittest.defaultTestLoader.loadTestsFromTestCase(LabTests)
    runner = unittest.TextTestRunner(verbosity=2)
    result = runner.run(suite)
    print(f'Labs 1-5: 13 exercises compiled; {LabTests.executions} program scenarios executed.')
    sys.exit(not result.wasSuccessful())
