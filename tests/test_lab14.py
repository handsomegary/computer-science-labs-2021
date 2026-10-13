"""Lab14 regression tests. Compiles standalone C++11 files in a temporary directory."""
import argparse
import os
from pathlib import Path
import random
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


def reference(expression):
    tokens = re.findall(r'\d+|[+*/%\-]', expression)
    term = int(tokens[0])
    total, sign = 0, 1
    for i in range(1, len(tokens), 2):
        operation, value = tokens[i], int(tokens[i + 1])
        if operation == '*':
            term *= value
        elif operation == '/':
            term //= value
        elif operation == '%':
            term %= value
        else:
            total += sign * term
            term = value
            sign = 1 if operation == '+' else -1
    return total + sign * term


class Lab14Tests(unittest.TestCase):
    executions = 0
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix='cslab14-')
        cls.addClassCleanup(cls.temp.cleanup)
        cls.executables = {}
        compiler = os.environ.get('CXX', 'g++')
        resolved = shutil.which(compiler) or compiler
        cls.env = os.environ.copy()
        cls.env['PATH'] = str(Path(resolved).parent) + os.pathsep + cls.env.get('PATH', '')
        for exercise in ('1', '2', '4'):
            executable = Path(cls.temp.name) / ('lab14_' + exercise + ('.exe' if os.name == 'nt' else ''))
            result = subprocess.run(
                [compiler, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic',
                 str(ROOT / 'lab14' / f'lab14_{exercise}.cpp'), '-o', str(executable)],
                capture_output=True, text=True, env=cls.env, check=True)
            if result.stderr:
                raise AssertionError(result.stderr)
            cls.executables[exercise] = executable

    def run_lab(self, exercise, input_text):
        type(self).executions += 1
        return subprocess.run([str(self.executables[exercise])], input=input_text + '\n',
                              text=True, encoding='utf-8', capture_output=True,
                              timeout=5, env=self.env)

    def test_arithmetic_handout_and_regressions(self):
        cases = ['1+2+3+4+5+6/2', '1*2*3*4*5*6%2', '1+2+3+4+5+6%5',
                 '10-0+2', '5-0*100-2', '1-2*3+4', '20/3/2', '20%6*2',
                 '0', '000001+002', '0-2147483647-1', '2147483647',
                 '2147483647*2147483647*2147483647/2147483647/2147483647',
                 '2147483647*2147483647*2147483647-2147483647*2147483647*2147483647+7',
                 '0-2147483647*2147483647+2147483647*2147483647-3',
                 '+'.join(['1'] * 150)]
        for expression in cases:
            with self.subTest(expression=expression):
                result = self.run_lab('1', expression)
                self.assertEqual(result.returncode, 0)
                self.assertEqual(result.stdout, f'Please enter the arithmetic: {reference(expression)}\n')

    def test_arithmetic_randomized_integer_oracle(self):
        randomizer = random.Random(2021)
        for _ in range(150):
            expression = str(randomizer.randrange(0, 101))
            for _ in range(randomizer.randrange(1, 20)):
                operation = randomizer.choice(['+', '-', '*', '/', '%'])
                value = randomizer.randrange(1 if operation in '/%' else 0, 101)
                expression += operation + str(value)
            expected = reference(expression)
            result = self.run_lab('1', expression)
            if -(2**31) <= expected < 2**31:
                self.assertEqual(result.returncode, 0, expression)
                self.assertEqual(result.stdout, f'Please enter the arithmetic: {expected}\n', expression)
            else:
                self.assertNotEqual(result.returncode, 0, expression)
                self.assertTrue(result.stdout.endswith('error\n'), expression)

    def test_arithmetic_invalid_input(self):
        for expression in ['', '1+', '-1', '1++2', '1  +2', '1a2', '(1+2)',
                           '1/0', '1%0', '2147483648', '2147483647+1', '0-2147483647-2']:
            with self.subTest(expression=expression):
                result = self.run_lab('1', expression)
                self.assertNotEqual(result.returncode, 0)
                self.assertEqual(result.stdout, 'Please enter the arithmetic: error\n')

    def test_digit_masking_preserves_spaces_and_original(self):
        for text in ['abc123def456ghi789jk0', '123 456 789 zxcvbnm,./', '',
                     '  0a!9  ', 'no digits!', '9' * 300]:
            with self.subTest(text=text):
                result = self.run_lab('2', text)
                count = sum('0' <= c <= '9' for c in text)
                masked = ''.join('*' if '0' <= c <= '9' else c for c in text)
                self.assertEqual(result.returncode, 0)
                self.assertEqual(result.stdout, 'Please enter a string.\n'
                    f'str1 = {text}\nThe number of the digits in the str1 is {count}.\nstr2 = {masked}\n')

    def test_reverse_empty_single_even_odd_and_spaces(self):
        for text in ['abcdefgh123456789!@#$%', '1 2 3 4 5 6 7 8 9 / * -', '',
                     'x', 'abc', 'abcd', '  !1? ', 'a' * 500 + 'b']:
            with self.subTest(text=text):
                result = self.run_lab('4', text)
                self.assertEqual(result.returncode, 0)
                self.assertEqual(result.stdout, 'Please enter a string:\n\n'
                                 f'After reversed, the string is:\n{text[::-1]}\n')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
    args, remaining = parser.parse_known_args()
    os.environ['CXX'] = args.cxx
    result = unittest.main(argv=[__file__] + remaining, verbosity=2, exit=False).result
    print(f'Lab 14.1/2/4: 3 exercises compiled; {Lab14Tests.executions} program scenarios executed.')
    raise SystemExit(not result.wasSuccessful())
