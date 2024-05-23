from sys import stdin
import re
import sys
import math

number_pat = "[1-9]\d*"
two_number_pat = number_pat + " " + number_pat;
int_re = re.compile(number_pat)
two_int_re = re.compile(two_number_pat)

line = stdin.readline()

# First line, three integers.    
assert two_int_re.match(line)
N,M = map(int,line.strip().split())
assert 1 <= N <= 100000 
assert 1 <= M <= 100000

for i in xrange(N+M):
    line = stdin.readline()
    assert len(line.strip().split()) == 2
    x,y = map(int,line.strip().split())
    assert -10000 <= x <= 10000 
    assert -10000 <= y <= 10000

assert len(stdin.readline()) == 0
sys.exit(42)
