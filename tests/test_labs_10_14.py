"""Independent oracles and transcript regressions for 2021 Labs 10-13 and 14.3.

python tests/test_labs_10_14.py [--cxx /path/to/g++] [--bin-dir existing/build]
Builds into a temporary directory when --bin-dir is omitted; no binaries in repo.
"""
import argparse
import itertools
import math
import os
from pathlib import Path
import random
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
PARSER = argparse.ArgumentParser()
PARSER.add_argument('--cxx', default=os.environ.get('CXX', 'g++'))
PARSER.add_argument('--bin-dir', type=Path)
ARGS, UNITTEST_ARGS = PARSER.parse_known_args()
ENV = os.environ.copy()
if Path(ARGS.cxx).parent != Path('.'):
    ENV['PATH'] = str(Path(ARGS.cxx).resolve().parent) + os.pathsep + ENV.get('PATH', '')
PROGRAMS = [f'lab{lab}_{task}' for lab in range(10, 14) for task in range(1, 5)] + ['lab14_3']


class Labs(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.build_temp = tempfile.TemporaryDirectory(prefix='cslab-build-')
        cls.bin_dir = ARGS.bin_dir.resolve() if ARGS.bin_dir else Path(cls.build_temp.name)
        if not ARGS.bin_dir:
            for name in PROGRAMS:
                source = ROOT / name.split('_')[0] / (name + '.cpp')
                command = [ARGS.cxx, '-std=c++11', '-O2', '-Wall', '-Wextra', '-Wpedantic',
                           str(source), '-o', str(cls.executable(name))]
                result = subprocess.run(command, text=True, capture_output=True, env=ENV)
                if result.returncode or result.stderr:
                    raise RuntimeError(f'{name} compilation failed or warned:\n{result.stderr}')

    @classmethod
    def tearDownClass(cls):
        cls.build_temp.cleanup()

    @classmethod
    def executable(cls, name):
        return cls.bin_dir / (name + ('.exe' if os.name == 'nt' else ''))

    def run_lab(self, name, input_text, files=None, timeout=5):
        with tempfile.TemporaryDirectory(prefix='cslab-input-') as folder:
            cwd = Path(folder)
            for filename, content in (files or {}).items():
                (cwd / filename).write_text(content, encoding='utf-8')
            result = subprocess.run([str(self.executable(name))], input=input_text, text=True,
                                    capture_output=True, cwd=cwd, env=ENV, timeout=timeout)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual(result.stderr, '')
            outputs = {p.name: p.read_text('utf-8') for p in cwd.glob('*out.txt')}
            return result.stdout, outputs

    def test_reverse_extremes_and_fifty_elements(self):
        for values in [[-2**63, 0, 2**63-1], [1], list(range(50))]:
            output, _ = self.run_lab('lab10_1', '  '.join(map(str, values)) + '  \n')
            self.assertEqual(output, ' '.join(map(str, reversed(values))) + '\n')

    def test_mountains_independent_peak_oracle(self):
        rng = random.Random(102)
        cases = [[1,4,6,5,4,7,8,5], [10,11,13,12,5,10,12,13,12,11,50,100],
                 [1,2,3], [3,2,1], [1,3,3,1], [1,2,1,2,1], [-2**63,2**63-1,-2**63]]
        cases += [[rng.randrange(-3,4) for _ in range(50)] for _ in range(8)]
        for values in cases:
            mountains = []
            for peak in range(1,len(values)-1):
                if values[peak-1] < values[peak] > values[peak+1]:
                    left, right = peak, peak
                    while left > 0 and values[left-1] < values[left]: left -= 1
                    while right+1 < len(values) and values[right] > values[right+1]: right += 1
                    mountains.append(values[left:right+1])
            longest = max(mountains, key=len) if mountains else []
            output, _ = self.run_lab('lab10_2', ' '.join(map(str,values))+'\n')
            self.assertEqual(output, str(len(mountains))+'\n'+' '.join(map(str,longest))+'\n')

    def test_operator_insertion_bruteforce_and_zero_reset(self):
        rng = random.Random(104)
        cases = [([1,2,3],6), ([1,2,1],3), ([0],0), ([2**63-1,2**63-1,0],0),
                 ([0]*50,1), ([1]*50,100), ([2]*50,1)]
        cases += [([rng.randrange(5) for _ in range(rng.randrange(2,8))],rng.randrange(30)) for _ in range(20)]
        for values, target in cases:
            expected = []
            if len(values) < 10:
                for ops in itertools.product('+*', repeat=len(values)-1):
                    expression = str(values[0]) + ''.join(op+str(value) for op,value in zip(ops,values[1:]))
                    if eval(expression, {'__builtins__':{}}, {}) == target:
                        expected.append('[' + str(values[0]) + ''.join(' '+op+' '+str(value) for op,value in zip(ops,values[1:])) + ']')
            output, _ = self.run_lab('lab10_4',' '.join(map(str,values))+'\n'+str(target)+'\n')
            self.assertEqual(output, (', '.join(expected) or 'not found')+'\n')

    def test_wave_sort_function_pointer_order(self):
        for values in [[1,2,3,4,5],list(range(20)),[2,2,0,-4,-4],[2**31-1,-2**31]]:
            pool = sorted(values)
            expected = []
            while pool:
                expected.append(pool.pop())
                if pool: expected.append(pool.pop(0))
            output,_ = self.run_lab('lab11_1',' '.join(map(str,values))+'\n')
            self.assertEqual(output,' '.join(map(str,expected))+'\n')

    def matrix_case(self, first, second):
        rows, middle, columns = len(first),len(first[0]),len(second[0])
        text = f'{rows} {middle}\n{len(second)} {columns}\n'
        text += '\n'.join(' '.join(map(str,row)) for row in first+second)+'\n'
        expected = [[sum(first[r][k]*second[k][c] for k in range(middle)) for c in range(columns)] for r in range(rows)]
        output,_ = self.run_lab('lab11_2',text)
        self.assertEqual(output.split('Output Matrix:\n')[1], '\n'.join(' '.join(map(str,row)) for row in expected)+'\n')

    def test_matrix_dimension_and_exact_wide_arithmetic(self):
        output,_ = self.run_lab('lab11_2','3 2\n3 2\n')
        self.assertIn('Cannot multiply these two matrixes.\n',output)
        self.matrix_case([[1,1,1],[2,2,2]],[[1,1],[2,2],[3,3]])
        self.matrix_case([[-2**63]*10],[[-2**63] for _ in range(10)])
        self.matrix_case([[-2**63, -2**63, 2**63-1]],[[2**63-1],[-(2**63-1)],[1]])
        self.matrix_case([[0]*10 for _ in range(10)],[[0]*10 for _ in range(10)])
        rng=random.Random(112)
        for _ in range(6):
            self.matrix_case([[rng.randrange(-10**12,10**12) for _ in range(3)] for _ in range(2)],
                             [[rng.randrange(-10**12,10**12) for _ in range(4)] for _ in range(3)])
        self.assertNotIn('[', (ROOT/'lab11/lab11_2.cpp').read_text('utf-8'))

    def test_goldbach_against_trial_division(self):
        def prime(n): return n >=2 and all(n%d for d in range(2,math.isqrt(n)+1))
        for n in [4,10,30,100,1000,50000]:
            expected=sum(prime(p) and prime(n-p) for p in range(2,n//2+1))
            output,_=self.run_lab('lab11_4',str(n)+'\n')
            self.assertEqual(output,f'Input number: Number of combinations: {expected}\n')

    def test_score_file_no_phantom_eof_student(self):
        for text,expected in [('12\n50\n64\n84\n95\n82\n10\n0\n','8\n4\n'),('60','1\n0\n'),('','0\n0\n')]:
            output,_=self.run_lab('lab12_1','score.txt\n',{'score.txt':text})
            self.assertEqual(output,'Please enter the input file name:\n'+expected)
        output,_=self.run_lab('lab12_1','missing.txt\n')
        self.assertIn('File could not be opened.',output)

    def test_gift_file_retry_validation_and_saved_content(self):
        gifts='No. Present\n1 Iphone13\n2 PS4\n5 sneakers\n'
        output,files=self.run_lab('lab12_2','missing.txt\ngifts.txt\n0\n2x\n4\n5\n',{'gifts.txt':gifts})
        self.assertIn('File could not be opened.',output)
        self.assertEqual(output.count('Invalid input! Please enter again:'),3)
        self.assertIn('Okay! Your Christmas present has been saved to giftsout.txt',output)
        self.assertEqual(files,{'giftsout.txt':'Congratulations! Your Christmas present is sneakers'})

    def test_word_grid_examples_and_backtracking(self):
        board=(ROOT/'lab12/4_1.txt').read_text('utf-8')
        output,_=self.run_lab('lab12_4','HELLO\nCOMPUTER\nLLVOIRP\nZZZZZ\n-1\n',{'4_1.txt':board})
        self.assertEqual(output,'True\nTrue\nTrue\nFalse\n')
        # The right branch matches B but dies; the downward branch succeeds.
        board='A B Z Z Z Z Z Z Z\nB Z Z Z Z Z Z Z Z\nC Z Z Z Z Z Z Z Z\n'+'Z Z Z Z Z Z Z Z Z\n'*6
        output,_=self.run_lab('lab12_4','ABC\nABA\nAZ\n-1\n',{'4_1.txt':board})
        self.assertEqual(output,'True\nFalse\nFalse\n')

    def test_invoice_all_prize_tiers_leading_zeros_and_ten_invoices(self):
        invoices=['00000678','00005678','00045678','00345678','02345678','12345678','99999999','00000000','12345678','00000678']
        output,_=self.run_lab('lab13_1','The invoice lottery number is 12345678.\n'+' '.join(invoices)+'\n')
        self.assertIn('00000678 won 2 hundred dollars!',output)
        self.assertEqual(output.count(' dollars!\n'),8)
        self.assertIn('You totally won 455400 dollars !!!',output)
        output,_=self.run_lab('lab13_1','The invoice lottery number is 12345678.\n99999999\n')
        self.assertEqual(output,'\nWon nothing. But, less is more.\n')

    def test_blood_all_genotype_combinations(self):
        genes=['AA','Ai','iA','BB','Bi','iB','AB','BA','ii']
        for first,second in itertools.product(genes,repeat=2):
            counts=dict(A=0.,B=0.,O=0.,AB=0.)
            for a,b in itertools.product(first,second):
                phenotype='O' if a==b=='i' else 'AB' if set((a,b))==set('AB') else 'A' if 'A' in (a,b) else 'B'
                counts[phenotype]+=.25
            output,_=self.run_lab('lab13_2',first+'\n'+second+'\n')
            actual={line.split(': ')[0]:float(line.split(': ')[1]) for line in output.splitlines() if ': ' in line}
            self.assertEqual(actual,counts)

    def test_routes_against_exhaustive_assignment(self):
        rng=random.Random(134)
        text=''; answers=[]
        for n in range(1,7):
            a=[rng.randrange(1,20) for _ in range(n)];b=[rng.randrange(1,20) for _ in range(n)]
            d,r=15,3
            answers.append(min(sum(max(0,x+y-d)*r for x,y in zip(a,p)) for p in itertools.permutations(b)))
            text+=f'{n} {d} {r}\n'+' '.join(map(str,a))+'\n'+' '.join(map(str,b))+'\n'
        text+='100 10000 5\n'+' '.join(['10000']*100)+'\n'+' '.join(['10000']*100)+'\n0 0 0\n'
        answers.append(5000000)
        output,_=self.run_lab('lab13_4',text)
        self.assertEqual(list(map(int,output.split())),answers)

    def test_theater_versions_register_login_logout_and_cross_account_auth(self):
        for lab in range(10,15):
            signup=lambda u,p: '5\nn\ny\n'+u+'\n'+p+'\n'+('0900000000\n' if lab>=13 else '')
            logout=lab-3 if lab<12 else 5
            text=signup('First','first123')+signup('Second','second123')
            text+='5\ny\nFirst\nsecond123\n5\ny\nFirst\nfirst123\n'+str(logout)+'\n'+str(lab-4)+'\n'
            output,_=self.run_lab(f'lab{lab}_3',text)
            self.assertEqual(output.count('Welcome! You are now a member'),2)
            self.assertEqual(output.count("The username and the password don't match."),1)
            self.assertIn('***Welcome back First***',output)
            self.assertIn('Thank you for using our system',output)

    def test_theater_invalid_seats_cancellation_full_capacity_and_eof(self):
        for lab in range(10,15):
            text='abc\n99\n1\nx\ny\n0\n16\n1\n1\ny\n1\n-5\n2\n2\n0\n16\n2\n2\n2\n4\n'+str(lab-4)+'\n'
            output,_=self.run_lab(f'lab{lab}_3',text)
            self.assertGreaterEqual(output.count('Invalid input, please enter your selection again:'),8)
            self.assertIn('The seat has been reserved, please enter your selection again:',output)
            self.assertIn('The seat number 2 is available now...',output)
            self.assertIn('The seat is not reserved',output)
            self.assertIn('Seat 1            reserved',output)
            self.assertIn('Seat 2            available',output)
            output,_=self.run_lab(f'lab{lab}_3',('1\nn\n'*15)+'1\n'+str(lab-4)+'\n')
            self.assertEqual(output.count('is reserved for you...'),15)
            self.assertIn('All seats have been reserved.',output)
            self.run_lab(f'lab{lab}_3','1\ny\n')

    def test_theater_member_lists_capacity_and_declined_signup(self):
        for lab in range(11,15):
            text='6\n5\nn\nn\n'
            for i in range(15): text+=f'5\nn\ny\nUser{i}\npw{i}\n'+('0900000000\n' if lab>=13 else '')
            text+='5\nn\ny\n6\n'+str(lab-4)+'\n'
            output,_=self.run_lab(f'lab{lab}_3',text)
            self.assertIn('No Member',output)
            self.assertIn('Okay! Have a nice day.',output)
            self.assertIn('The member center is full.',output)
            self.assertIn('15.  User14',output)
            self.assertEqual(output.count('Welcome! You are now a member'),15)

    def test_theater_file_append_auth_password_phone_changes_and_search(self):
        for lab in range(12,15):
            rows='Name Password'+(' Phone' if lab>=13 else '')+'\nAlpha oldA'+(' 0900000001' if lab>=13 else '')+'\nBeta oldB'+(' 0900000002' if lab>=13 else '')+'\n'
            text='7\nmissing.txt\n7\nmembers.txt\n6\n5\ny\nAlpha\noldA\n5\n'
            if lab>=13:
                text+='8\n3\n1\nAlpha\noldB\n8\n1\nAlpha\noldA\nnewA\n8\n2\nAlpha\nnewA\n0912345678\n'
                text+='5\ny\nAlpha\noldA\n5\ny\nAlpha\nnewA\n5\n'
            if lab==14: text+='9\nAl\n9\nalpha\n9\nBeta\n'
            text+=str(lab-4)+'\n'
            output,_=self.run_lab(f'lab{lab}_3',text,{'members.txt':rows})
            self.assertIn('File could not be opened.',output)
            self.assertIn('The file members.txt has been loaded...',output)
            self.assertIn('1.  Alpha\n2.  Beta',output)
            self.assertIn('***Welcome back Alpha***',output)
            if lab>=13: self.assertEqual(output.count("The username and the password don't match."),2)
            if lab==14:
                self.assertIn(f'{"Alpha":<16} {"newA":<16} 0912345678',output)
                self.assertIn(f'{"Beta":<16} {"oldB":<16} 0900000002',output)
                self.assertIn('We cannot find the keyword',output)

    def test_theater_search_fifty_character_field_separators(self):
        username,password='A'*50,'P'*50
        rows=f'Name Password Phone\n{username} {password} 0900000000\n'
        output,_=self.run_lab('lab14_3','7\nmembers.txt\n9\nAAA\n10\n',{'members.txt':rows})
        self.assertIn(username+' '+password+' 0900000000',output)


if __name__ == '__main__':
    unittest.main(argv=[sys.argv[0]]+UNITTEST_ARGS, verbosity=2)
