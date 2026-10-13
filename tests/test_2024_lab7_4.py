"""Verify the stated, configurable 2024 Feistel reference contract."""
import argparse
import os
from pathlib import Path
import random
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
PARSER = argparse.ArgumentParser()
PARSER.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
ARGS, REMAINING = PARSER.parse_known_args()


def scramble_oracle(control, value):
    bits = list(f'{value:08b}')
    if control & 16:
        bits[0], bits[2] = bits[2], bits[0]
    if control & 8:
        bits[5], bits[7] = bits[7], bits[5]
    return int(''.join(bits), 2)


def function_oracle(selector, right, key):
    if selector == 0:
        return right ^ key
    if selector == 1:
        return right & key
    if selector == 2:
        return right | key
    return ((right // 256) % (key // 256)) * 256 + (right % 256) % (key % 256)


class FeistelTests(unittest.TestCase):
    executions = 0

    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix='feistel-2024-')
        cls.addClassCleanup(cls.temp.cleanup)
        folder = Path(cls.temp.name)
        compiler = shutil.which(ARGS.cxx) or ARGS.cxx
        cls.env = os.environ.copy()
        cls.env['PATH'] = str(Path(compiler).resolve().parent) + os.pathsep + cls.env.get('PATH', '')
        cls.program = folder / ('lab7_4.exe' if os.name == 'nt' else 'lab7_4')
        cls.probe = folder / ('probe.exe' if os.name == 'nt' else 'probe')
        source = ROOT / '2024/lab07/lab7_4.cpp'
        harness = folder / 'probe.cpp'
        harness.write_text('#define main lab_main\n#include "' + source.as_posix()
            + '"\n#undef main\nint main() { unsigned c,v; while(std::cin>>c>>v) '
              'std::cout<<scramble(c,v)<<"\\n"; }\n', encoding='utf-8')
        for input_file, executable in [(source, cls.program), (harness, cls.probe)]:
            result = subprocess.run([compiler, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic',
                                     str(input_file), '-o', str(executable)],
                                    text=True, capture_output=True, env=cls.env, check=True)
            if result.stderr:
                raise AssertionError(result.stderr)

    def run_program(self, data):
        type(self).executions += 1
        return subprocess.run([str(self.program)], input=data, capture_output=True,
                              text=True, encoding='latin-1', env=self.env, timeout=5)

    def test_scramble_all_control_and_byte_values(self):
        pairs = [(control, value) for control in range(256) for value in range(256)]
        type(self).executions += 1
        result = subprocess.run([str(self.probe)],
            input=''.join(f'{control} {value}\n' for control, value in pairs),
            text=True, capture_output=True, env=self.env, timeout=10, check=True)
        actual = [int(value) for value in result.stdout.split()]
        self.assertEqual(actual, [scramble_oracle(c, v) for c, v in pairs])

    def test_fixed_rounds_and_both_keys(self):
        cases = [(0, 0x0102, 0x0304, 0x0102, 0x0304, 0x0304),
                 (1, 0x0102, 0x0304, 0x0102, 0x0304, 0x0002),
                 (2, 0x0102, 0x0304, 0x0102, 0x0304, 0x0204),
                 (3, 0x0102, 0x0304, 0x0102, 0x0304, 0x0102)]
        for selector, left, right, key, out_left, out_right in cases:
            with self.subTest(selector=selector):
                data = f'1 2 3 4\n-1 -1 -1 -1\nN {left//256} {left%256} {right//256} {right%256}\n1\nE 1 {selector}\n'
                result = self.run_program(data)
                self.assertEqual(result.returncode, 0)
                self.assertEqual(result.stdout, f'{out_left//256} {out_left%256} {out_right//256} {out_right%256}\n')
        result = self.run_program('1 2 3 4\n-1 -1 -1 -1\nN 1 2 3 4\n1\nE 2 0\n')
        self.assertEqual(result.stdout, '3 4 1 2\n')

    def test_explicit_scramble_mapping(self):
        for control in [0, 8, 16, 24, 255]:
            for value in [0, 1, 4, 32, 128, 255]:
                result = self.run_program(f'{control} {value} {control} {value}\n-1 0 -1 2\nN 0 0 0 0\n1\nE 1 0\n')
                self.assertEqual(result.stdout, f'0 0 {control} {scramble_oracle(control,value)}\n')

    def test_randomized_schedule_and_inverse(self):
        randomizer = random.Random(113028)
        for _ in range(80):
            keys = [randomizer.randrange(1, 256) for _ in range(4)]
            key1, key2 = keys[0]*256 + keys[1], keys[2]*256 + keys[3]
            original = [randomizer.randrange(256) for _ in range(4)]
            left, right = original[0]*256+original[1], original[2]*256+original[3]
            schedule = [(randomizer.randrange(1, 3), randomizer.randrange(4)) for _ in range(randomizer.randrange(1, 20))]
            for which, selector in schedule:
                left, right = right, left ^ function_oracle(selector, right, key1 if which == 1 else key2)
            prefix = ' '.join(map(str, keys))+'\n-1 -1 -1 -1\nN '+' '.join(map(str, original))+'\n'
            result = self.run_program(prefix + str(len(schedule)) + '\n'
                + ''.join(f'E {which} {selector}\n' for which, selector in schedule))
            self.assertEqual(result.returncode, 0)
            self.assertEqual(result.stdout, f'{left//256} {left%256} {right//256} {right%256}\n')
            full_schedule = ''.join(f'E {which} {selector}\n' for which, selector in schedule)
            full_schedule += ''.join(f'D {which} {selector}\n' for which, selector in reversed(schedule))
            restored = self.run_program(prefix + str(2*len(schedule))+'\n'+full_schedule)
            self.assertEqual(restored.returncode, 0)
            self.assertEqual(restored.stdout, ' '.join(map(str, original))+'\n')

    def test_zero_rounds_text_whitespace_and_byte_edges(self):
        for text in ['abcd', 'a b ', '    ', '1234']:
            result = self.run_program(f'0 0 0 0\n-1 -1 -1 -1\nT {text}\n0\n')
            self.assertEqual(result.returncode, 0)
            self.assertEqual(result.stdout, text+'\n')
        result = self.run_program('0 0 0 0\n-1 -1 -1 -1\nN 0 255 128 1\n0\n')
        self.assertEqual(result.stdout, '0 255 128 1\n')

    def test_invalid_configuration_and_zero_mod_divisors(self):
        cases = ['256 0 0 0\n', '0 0 0 0\n4 -1 -1 -1\n',
                 '-4294967295 2 3 4\n-1 -1 -1 -1\nN 0 0 0 0\n0\n',
                 '1 1 1 1\n-1 -1 -1 -1\nN 0 0 0 0\n1\nE 1 -4294967295\n',
                 '1 1 1 1\n-1 -1 -1 -1\nN 0 0 0 0\n-1\n',
                 '1 1 1 1\n-1 -1 -1 -1\nN 0 0 0 0\n-18446744073709551615\n',
                 '0 0 1 1\n-1 -1 -1 -1\nN 0 0 0 0\n1\nE 1 3\n',
                 '1 0 1 1\n-1 -1 -1 -1\nN 0 0 0 0\n1\nE 1 3\n',
                 '1 1 1 1\n-1 -1 -1 -1\nN 0 0 0 0\n1\nE 1 4\n',
                 '1 1 1 1\n-1 -1 -1 -1\nN 0 0 0 0\n1\nE 3 0\n',
                 '1 1 1 1\n-1 -1 -1 -1\nN 0 0 0 0\n1\nQ 1 0\n',
                 '1 1 1 1\n-1 -1 -1 -1\nN 0 0 0 256\n']
        for data in cases:
            result = self.run_program(data)
            self.assertNotEqual(result.returncode, 0)
            self.assertEqual(result.stdout, 'error\n')


if __name__ == '__main__':
    result = unittest.main(argv=[__file__]+REMAINING, verbosity=2, exit=False).result
    print(f'2024 Lab 7.4 reference: {FeistelTests.executions} executions; 65536 scramble vectors checked.')
    raise SystemExit(not result.wasSuccessful())
