"""Verify 2021 final G member formatting and the complete theater workflow."""
import argparse
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
PARSER = argparse.ArgumentParser()
PARSER.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
OPTIONS, UNITTEST_ARGS = PARSER.parse_known_args()


def menu(username=None):
    text = '*** Welcome to NCU theater reservation system ***\n'
    if username:
        text += f'***Welcome back {username}***\n'
    return text + ('Please type 1 to make a new reservation\n'
        'Please type 2 to cancel an existing reservation\n'
        'Please type 3 to show the all available seats\n'
        'Please type 4 to show the status of all current seats\n') + (
        'Please type 5 to log-out\n' if username else 'Please type 5 to member center\n') + (
        'Please type 6 to show member\nPlease type 7 to load member information\n'
        'Please type 8 to change member data\nPlease type 9 to find member data\n'
        'Please type 10 to exit the system\nEnter your selection Here: ')


class TheaterTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which(OPTIONS.cxx) or OPTIONS.cxx
        cls.environment = dict(os.environ)
        cls.environment['PATH'] = str(Path(compiler).resolve().parent) + os.pathsep + cls.environment.get('PATH', '')
        cls.build = tempfile.TemporaryDirectory(prefix='exam-theater-build-')
        cls.addClassCleanup(cls.build.cleanup)
        cls.program = Path(cls.build.name) / ('theater.exe' if os.name == 'nt' else 'theater')
        result = subprocess.run([compiler, '-std=c++11', '-Wall', '-Wextra', '-Wpedantic',
            str(ROOT / 'exams/2021/final/problem_g.cpp'), '-o', str(cls.program)],
            text=True, encoding='utf-8', capture_output=True, env=cls.environment, timeout=30)
        if result.returncode or result.stderr:
            raise AssertionError(f'Theater compilation failed or warned:\n{result.stderr}')

    def run_program(self, commands, files=None):
        with tempfile.TemporaryDirectory(prefix='exam-theater-input-') as folder:
            for name, content in (files or {}).items():
                (Path(folder) / name).write_text(content, encoding='utf-8', newline='\n')
            result = subprocess.run([str(self.program)], input=commands, text=True,
                encoding='utf-8', capture_output=True, cwd=folder, env=self.environment, timeout=5)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stderr, '')
        return result.stdout

    def test_complete_official_flow_with_anonymous_fixture(self):
        members = 'Name Password Phone\nGuestA demoA 0000000001\nGuestB demoB 0000000002\nGuestLong demoC 0000000003\n'
        output = self.run_program('7\nmember1.txt\n6\n10\n', {'member1.txt': members})
        expected = menu() + ('\n***Load member information***\nPlease enter the member file name: '
            'The file member1.txt has been loaded...\n\n') + menu() + (
            '\n***NCU Theater Membership***\nNo.  Username    Phone\n'
            '1.   GuestA      0000000001\n2.   GuestB      0000000002\n'
            '3.   GuestLong   0000000003\n\n') + menu() + (
            '\nThank you for using our system\nHave a nice day~~\n')
        self.assertEqual(output, expected)

    def test_fifteen_members_and_long_names_align(self):
        names = ['U' * 50] + [f'Guest{i}' for i in range(2, 16)]
        members = '\n'.join(f'{name} pw 000000{i:04d}' for i, name in enumerate(names, 1)) + '\n'
        output = self.run_program('7\nrows.txt\n6\n10\n', {'rows.txt': members})
        table = output.split('***NCU Theater Membership***\n')[1].split('\n\n')[0].splitlines()
        self.assertEqual(len(table), 16)
        name_column, phone_column = table[0].index('Username'), table[0].index('Phone')
        self.assertEqual(name_column, 5)
        for i, line in enumerate(table[1:], 1):
            self.assertEqual(line[:5].strip(), f'{i}.')
            self.assertTrue(line[name_column:].startswith(names[i - 1]))
            self.assertEqual(line[phone_column:], f'000000{i:04d}')
            self.assertTrue(line[phone_column - 2:phone_column].isspace())

    def test_membership_login_changes_search_and_logout(self):
        commands = ('5\nn\ny\nGuestNew\npw\n0000000050\n6\n5\ny\nGuestNew\npw\n'
            '8\n1\nGuestNew\npw\nnew\n8\n2\nGuestNew\nnew\n0000000051\n'
            '6\n9\nGuest\n5\n5\ny\nGuestNew\npw\n5\ny\nGuestNew\nnew\n5\n10\n')
        output = self.run_program(commands)
        self.assertIn('Welcome! You are now a member of NCU theater.\nPlease log in again.', output)
        self.assertIn('1.   GuestNew    0000000050', output)
        self.assertIn('1.   GuestNew    0000000051', output)
        self.assertIn(f'{"GuestNew":<16} {"new":<16} 0000000051', output)
        self.assertIn('***Welcome back GuestNew***', output)
        self.assertEqual(output.count("The username and the password don't match."), 1)
        self.assertTrue(output.endswith('Thank you for using our system\nHave a nice day~~\n'))

    def test_load_is_atomic_for_malformed_duplicate_and_full_files(self):
        files = {
            'ok.txt': 'GuestA pw 0000000001\n',
            'bad.txt': 'NewGuest pw 0000000002\nmissing_phone pw\n',
            'duplicate.txt': 'NewGuest pw 0000000002\nGuestA pw 0000000003\n',
            'full.txt': ''.join(f'Temp{i} pw 000000{i:04d}\n' for i in range(15)),
        }
        output = self.run_program('7\nok.txt\n7\nbad.txt\n7\nduplicate.txt\n7\nfull.txt\n'
                                  '7\nmissing.txt\n6\n10\n', files)
        self.assertEqual(output.count('Invalid member data.'), 3)
        self.assertIn('File could not be opened.', output)
        table = output.split('***NCU Theater Membership***\n')[1].split('\n\n')[0]
        self.assertEqual(table, 'No.  Username    Phone\n1.   GuestA      0000000001')

    def test_all_seats_reservations_cancel_and_retry(self):
        commands = '1\nn\n' * 15 + '1\n4\n2\n1\n2\n15\n3\n1\ny\n2\n16\n1\n3\n4\n10\n'
        output = self.run_program(commands)
        allocations = re.findall(r'The seat number (\d+) is reserved for you', output)
        self.assertEqual(list(map(int, allocations)), list(range(1, 16)) + [1])
        self.assertIn('All seats have been reserved.', output)
        available = output.split('***Show the all available seats***\n')
        self.assertTrue(available[1].startswith('seat 1\nseat 15\n\n'))
        self.assertTrue(available[2].startswith('seat 15\n\n'))
        status = re.findall(r'^Seat (\d+)\s+(reserved|available)$', output, re.M)
        self.assertEqual(len(status), 30)
        self.assertTrue(all(value == 'reserved' for _, value in status[:15]))
        self.assertEqual(dict(status[15:]), {str(i): ('available' if i == 15 else 'reserved') for i in range(1, 16)})

    def test_empty_members_and_invalid_menu(self):
        output = self.run_program('x\n11\n-1\n6\n10\n')
        self.assertEqual(output.count('Invalid input, please enter your selection again: '), 3)
        self.assertIn('***NCU Theater Membership***\nNo Member\n', output)

    def test_full_membership_does_not_consume_next_menu_choice(self):
        members = ''.join(f'Guest{i} pw 000000{i:04d}\n' for i in range(15))
        output = self.run_program('7\nfull.txt\n5\nn\ny\n10\n', {'full.txt': members})
        self.assertIn('The member center is full.', output)
        self.assertTrue(output.endswith('Thank you for using our system\nHave a nice day~~\n'))

    def test_eof_at_each_interaction_returns_without_partial_mutation(self):
        for commands in ('', '5\n', '5\nn\ny\nUser\npw\n', '1\ny\n', '7\n', '8\n1\nUser\n', '9\n'):
            with self.subTest(commands=commands):
                output = self.run_program(commands)
                self.assertNotIn('is reserved for you', output)
                self.assertNotIn('You are now a member', output)
                self.assertNotIn('Have a nice day~~', output)


if __name__ == '__main__':
    unittest.main(argv=[__file__] + UNITTEST_ARGS, verbosity=2)
