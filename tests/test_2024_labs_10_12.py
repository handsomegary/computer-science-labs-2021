"""Compile and exercise the 2024 Lab 10-12 implementations independently.

Run from any directory: python tests/test_2024_labs_10_12.py --cxx /path/to/g++
The input/output contracts are documented in 2024/lab*/README.md because the
provided review slides omit parts of the original online-judge statements.
"""
import argparse
from collections import Counter, deque
import datetime
import os
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser()
parser.add_argument('--cxx', default=os.environ.get('CXX','g++'))
parser.add_argument('--bin-dir', type=Path)
ARGS, remaining = parser.parse_known_args()
ENV = os.environ.copy()
if Path(ARGS.cxx).parent != Path('.'):
    ENV['PATH'] = str(Path(ARGS.cxx).resolve().parent) + os.pathsep + ENV.get('PATH','')
EXECUTIONS = 0


class Labs2024(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.scratch = tempfile.TemporaryDirectory(prefix='cslab2024-build-')
        cls.bin = ARGS.bin_dir.resolve() if ARGS.bin_dir else Path(cls.scratch.name)
        if not ARGS.bin_dir:
            for lab in (10,11,12):
                for task in range(1,5):
                    name=f'lab{lab}_{task}'
                    result=subprocess.run([ARGS.cxx,'-std=c++11','-O2','-Wall','-Wextra','-Wpedantic',
                                           str(ROOT/'2024'/f'lab{lab}'/(name+'.cpp')),
                                           '-o',str(cls.executable(name))],text=True,capture_output=True,env=ENV)
                    if result.returncode or result.stderr:
                        raise RuntimeError(f'{name}: compiler failed or warned:\n{result.stderr}')

    @classmethod
    def tearDownClass(cls): cls.scratch.cleanup()

    @classmethod
    def executable(cls,name): return cls.bin/(name+('.exe' if os.name=='nt' else ''))

    def run_lab(self,name,input_text,timeout=5):
        global EXECUTIONS
        with tempfile.TemporaryDirectory(prefix='cslab2024-run-') as cwd:
            result=subprocess.run([str(self.executable(name))],input=input_text,text=True,capture_output=True,
                                  cwd=cwd,env=ENV,timeout=timeout)
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertEqual(result.stderr,'')
        EXECUTIONS += 1
        return result.stdout

    def test_modifying_score_clamp_and_one_based_boundary(self):
        for k in range(1,5):
            scores=[0,90,91,100]
            scores[k-1]=min(100,scores[k-1]+10)
            output=self.run_lab('lab10_1',f'4\n0 90 91 100\n{k}\n')
            self.assertEqual(output,' '.join(map(str,scores))+'\n')
        for k in (-1,0,5):
            self.assertEqual(self.run_lab('lab10_1',f'4\n0 90 91 100\n{k}\n'),'invalid student number.\n')
        rng=random.Random(2024101)
        for _ in range(10):
            scores=[rng.randrange(101) for _ in range(rng.randrange(1,20))]
            k=rng.randrange(1,len(scores)+1)
            text=f'{len(scores)}\n'+' '.join(map(str,scores))+f'\n{k}\n'
            scores[k-1]=min(100,scores[k-1]+10)
            self.assertEqual(self.run_lab('lab10_1',text),' '.join(map(str,scores))+'\n')

    def test_transpose_rectangular_single_and_maximum_dimensions(self):
        rng=random.Random(2024102)
        for rows,columns in [(1,1),(2,3),(1,100),(100,1),(100,100)]+[(rng.randrange(1,8),rng.randrange(1,8)) for _ in range(5)]:
            matrix=[[rng.randrange(-1000,1001) for _ in range(columns)] for _ in range(rows)]
            text=f'{rows} {columns}\n'+'\n'.join(' '.join(map(str,row)) for row in matrix)+'\n'
            expected='\n'.join(' '.join(map(str,row)) for row in zip(*matrix))+'\n'
            self.assertEqual(self.run_lab('lab10_2',text),expected)

    def test_book_titles_case_insensitive_stable_prefixes_and_spaces(self):
        cases=[['Zoo','apple','Apple','a','A Tale','apple pie','!Book',''],[],['same','SAME','Same']]
        rng=random.Random(2024103)
        cases.append([''.join(rng.choice('aABbzZ !') for _ in range(rng.randrange(1,100))) for _ in range(100)])
        cases.append(['z'*200,'a'*200,'b'*200])
        for titles in cases:
            text=str(len(titles))+'\n'+'\n'.join(titles)+('\n' if titles else '')
            expected=''.join(title+'\n' for title in sorted(titles,key=str.lower))
            self.assertEqual(self.run_lab('lab10_3',text),expected)

    def test_caesar_all_keys_wrap_case_punctuation_and_no_match(self):
        def shift(text,key):
            result=''
            for ch in text:
                if 'a'<=ch<='z': result+=chr((ord(ch)-97+key)%26+97)
                elif 'A'<=ch<='Z': result+=chr((ord(ch)-65+key)%26+65)
                else: result+=ch
            return result
        message='Attack At Dawn. Meet at the Park! 2024'
        for key in range(1,27):
            encrypted=shift(message,key)
            self.assertEqual(self.run_lab('lab10_4',encrypted+'\nAttack\n'),f'{key}\n{message}\n')
        self.assertEqual(self.run_lab('lab10_4','ab\nlonger keyword\n'),'not found\n')
        self.assertEqual(self.run_lab('lab10_4','ab cd\n\n'),'not found\n')
        # The unchanged key is represented by 26, and cannot be mistaken for 0.
        self.assertEqual(self.run_lab('lab10_4','Hello, World!\nHello, World!\n'),'26\nHello, World!\n')

    def test_discount_pointer_two_decimal_output(self):
        for price,discount in [('100','0.85'),('199.99','0.85'),('0','0.3'),('100','1'),('80','0'),('1200','0.875')]:
            expected=f'{float(price)*float(discount):.2f}'
            output=self.run_lab('lab11_1',price+'\n'+discount+'\n')
            self.assertEqual(output,'Please enter the price: Please enter the discount: After discount, the price is '+expected+'\n')

    def test_calendar_against_datetime_with_century_leap_years(self):
        dates=['20240807','20240229','20230229','19000229','20000229','21000229','24000229',
               '20240431','20241231','20240001','20241301','20240100','00000101','00010101',
               '99991231','2024087','202408071','2024aa07']
        rng=random.Random(2024112)
        dates += [f'{rng.randrange(1,10000):04d}{rng.randrange(0,14):02d}{rng.randrange(0,33):02d}' for _ in range(12)]
        for value in dates:
            legal=False
            if len(value)==8 and value.isascii() and value.isdigit():
                try:
                    datetime.date(int(value[:4]),int(value[4:6]),int(value[6:]))
                    legal=True
                except ValueError: pass
            self.assertEqual(self.run_lab('lab11_2',value+'\n'),'This is legal.\n' if legal else 'This is not legal.\n')

    def test_apple_banana_hints_leading_zero_repeated_guesses_and_retry(self):
        cases=[('0123',['3210','0011','0123']),('12345678',['87654321','12345678']),('1230',['0000','1230'])]
        for secret,guesses in cases:
            expected=[]
            for guess in guesses:
                apples=sum(a==b for a,b in zip(secret,guess))
                bananas=sum((Counter(secret)&Counter(guess)).values())-apples
                expected.append(f'{apples}A{bananas}B')
            expected.append('You win!')
            text=str(len(secret))+'\n'+secret+'\n'+'\n'.join(guesses)+'\n'
            self.assertEqual(self.run_lab('lab11_4',text),'\n'.join(expected)+'\n')
        output=self.run_lab('lab11_4','3\n012\n12\nabc\n012\n')
        self.assertEqual(output,'Invalid guess, please enter again.\n'*2+'3A0B\nYou win!\n')
        self.assertEqual(self.run_lab('lab11_4','4\n1123\n'),'Invalid secret number.\n')

    def test_apple_banana_exact_attempt_limits_first_and_last_win(self):
        for length,limit in [(3,4),(4,7),(5,11),(6,16),(7,22),(8,29)]:
            secret='01234567'[:length]; wrong=secret[::-1]
            apple=sum(a==b for a,b in zip(secret,wrong))
            hint=f'{apple}A{length-apple}B\n'
            prefix=str(length)+'\n'+secret+'\n'
            self.assertEqual(self.run_lab('lab11_4',prefix+secret+'\n'),f'{length}A0B\nYou win!\n')
            self.assertEqual(self.run_lab('lab11_4',prefix+(wrong+'\n')*(limit-1)+secret+'\n'),hint*(limit-1)+f'{length}A0B\nYou win!\n')
            self.assertEqual(self.run_lab('lab11_4',prefix+(wrong+'\n')*limit+secret+'\n'),hint*limit+'You lose!\n')

    def test_reverse_five_elements_pointer_access(self):
        for numbers in [[1,2,3,4,5],[-2**31,0,2**31-1,4,-5],[9,9,9,9,9]]:
            self.assertEqual(self.run_lab('lab12_1',' '.join(map(str,numbers))+'\n'),' '.join(map(str,numbers[::-1]))+'\n')

    def test_digital_root_zero_multi_stage_and_int_boundaries(self):
        for number in [0,1,9,10,99,999999,2147483647,-2147483648,1234567890]:
            expected=0 if not number else 1+(abs(number)-1)%9
            self.assertEqual(self.run_lab('lab12_2',str(number)+'\n'),f'digital root: {expected}\n')
        source=(ROOT/'2024/lab12/lab12_2.cpp').read_text('utf-8')
        self.assertRegex(source,r'void\s+digitalRoot\(int num, int \*dRoot\)')

    def maze_case(self,board):
        rows,columns=len(board),len(board[0])
        text=f'{rows} {columns}\n'+'\n'.join(''.join(map(str,row)) for row in board)+'\n'
        # Independent BFS establishes reachability; output path must be a simple
        # walk through open orthogonal cells and terminate at the lower-right exit.
        reached=set()
        queue=deque([(0,0)]) if board[0][0]==0 else deque()
        while queue:
            r,c=queue.popleft()
            if (r,c) in reached: continue
            reached.add((r,c))
            for dr,dc in [(1,0),(0,1),(-1,0),(0,-1)]:
                nr,nc=r+dr,c+dc
                if 0<=nr<rows and 0<=nc<columns and board[nr][nc]==0 and (nr,nc) not in reached:
                    queue.append((nr,nc))
        output=self.run_lab('lab12_4',text)
        if (rows-1,columns-1) not in reached:
            self.assertEqual(output,"Can't reach the exit!\n")
            return
        points=[tuple(map(int,m)) for m in re.findall(r'\((\d+), (\d+)\)',output)]
        self.assertTrue(points)
        self.assertEqual(points[0],(0,0));self.assertEqual(points[-1],(rows-1,columns-1))
        self.assertEqual(len(points),len(set(points)))
        for r,c in points:
            self.assertTrue(0<=r<rows and 0<=c<columns)
            self.assertEqual(board[r][c],0)
        for first,second in zip(points,points[1:]):
            self.assertEqual(abs(first[0]-second[0])+abs(first[1]-second[1]),1)

    def test_maze_reachability_dead_ends_single_cells_and_large_stack(self):
        boards=[[[0]],[[1]],[[0,0,0,0]],[[0],[0],[0]],[[0,1],[1,0]],
                [[0,0,0,1],[0,1,0,1],[0,1,1,1],[0,0,0,0]],[[0,0],[0,1]]]
        rng=random.Random(2024124)
        for _ in range(25):
            r,c=rng.randrange(1,9),rng.randrange(1,9)
            board=[[int(rng.random()<.3) for _ in range(c)] for _ in range(r)]
            board[0][0]=board[-1][-1]=0
            boards.append(board)
        # A unique 100x100 snake requires thousands of stack entries.
        board=[[1]*100 for _ in range(100)]
        for r in range(0,100,2):
            board[r]=[0]*100
            if r+1<100: board[r+1][99 if (r//2)%2==0 else 0]=0
        board[-1]=[0]*100
        boards.append(board)
        for board in boards: self.maze_case(board)
        self.assertEqual(self.run_lab('lab12_4','2 3\n000\n000\n'),'(0, 0) (0, 1) (0, 2) (1, 2)\n')

    def test_hotel_search_catalogue_exact_occupancy_and_alignment(self):
        expected={1:[('2-1','Single',760)],2:[('1-1','Double',1650),('2-2','Double',1380),('2-3','Twin',1420),('3-1','Double',2540)],
                  3:[('3-2','Triple',3670)],4:[('1-2','Quad',3200),('3-3','Quad',4300)]}
        for lab in (11,12):
            for people,rows in expected.items():
                output=self.run_lab(f'lab{lab}_3',f'1\n9/6\n{people}\nexit()\n')
                found=[(number,room,int(price)) for number,room,price in re.findall(r'^([123]-[123])\s+(\w+)\s+NTD\s+(\d+)$',output,re.M)]
                self.assertEqual(found,rows)
                for line in output.splitlines():
                    if re.match(r'^[123]-[123]',line): self.assertEqual(line.index('NTD'),39)
                    elif line.startswith('No.'): self.assertEqual(line.index('Price'),39)

    def test_hotel_payment_user_isolation_multiple_dates_and_unlimited_lab11(self):
        for lab in (11,12):
            text='2\nAlice Example\n9/6\n3-1\n2\nAlice Example\n2/10\n2-3\n2\nBob\n9/6\n2-1\n3\nAlice Example\n3\nMissing\nexit()\n'
            output=self.run_lab(f'lab{lab}_3',text)
            self.assertEqual(output.count('Reserved successfully!'),3)
            self.assertIn("*** This is Alice Example's order ***",output)
            self.assertRegex(output,r'Total\s+NTD\s+3960')
            self.assertNotIn('Garden Hotel Single Room',output)
            self.assertIn('You have not reserved any rooms.',output)
        text='2\nA\n9/6\n1-1\n2\nB\n9/6\n1-1\n3\nB\nexit()\n'
        output=self.run_lab('lab11_3',text)
        self.assertEqual(output.count('Reserved successfully!'),2)
        self.assertNotIn('not available',output)
        self.assertRegex(output,r'Total\s+NTD\s+1650')

    def test_hotel_lab12_date_room_capacity_search_filter_and_canonical_dates(self):
        text='2\nA\n9/6\n1-1\n2\nB\n09/06\n1-1\n2-2\n1\n9/6\n2\n1\n9/7\n2\nexit()\n'
        output=self.run_lab('lab12_3',text)
        self.assertEqual(output.count('Reserved successfully!'),2)
        self.assertEqual(output.count('The selected room is not available, please enter again!'),1)
        searches=output.split('How many people? ')[1:]
        first=[number for number in re.findall(r'^([123]-[123])\s',searches[0],re.M)]
        second=[number for number in re.findall(r'^([123]-[123])\s',searches[1],re.M)]
        self.assertEqual(first,['2-3','3-1'])
        self.assertNotIn('Cloud Hotel',searches[0])
        self.assertEqual(second,['1-1','2-2','2-3','3-1'])
        text=''.join(f'2\nGuest{i}\n9/6\n{room}\n' for i,room in enumerate(['1-1','2-2','2-3','3-1']))
        text+='1\n9/6\n2\nexit()\n'
        output=self.run_lab('lab12_3',text)
        self.assertIn('No available rooms.',output)
        self.assertNotIn('*** Cloud Hotel',output)
        self.assertNotIn('*** Garden Hotel',output)
        self.assertNotIn('*** City Big Hotel',output)

    def test_hotel_invalid_commands_rooms_dates_people_and_more_than_five_bookings(self):
        for lab in (11,12):
            text='unknown\n2\nAlice\n2/30\n9/6\nxyz\n4-1\n1-1\n1\n9/6\n0\n5\nabc\n2\nexit()\n'
            output=self.run_lab(f'lab{lab}_3',text)
            self.assertIn('Unknown command',output)
            self.assertIn('Wrong date, please enter again!',output)
            self.assertEqual(output.count('Wrong number, please enter again!'),2)
            self.assertEqual(output.count('Invalid number of people, please enter again!'),3)
            text=''.join(f'2\nAlice\n1/{day}\n1-1\n' for day in range(1,11))+'3\nAlice\nexit()\n'
            output=self.run_lab(f'lab{lab}_3',text)
            self.assertEqual(output.count('Reserved successfully!'),10)
            self.assertRegex(output,r'Total\s+NTD\s+16500')
            self.run_lab(f'lab{lab}_3','2\nAlice\n')


if __name__=='__main__':
    result=unittest.main(argv=[sys.argv[0]]+remaining,verbosity=2,exit=False).result
    print(f'2024 Labs 10-12: {EXECUTIONS} completed program executions.')
    sys.exit(0 if result.wasSuccessful() else 1)
