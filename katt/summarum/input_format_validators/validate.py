from sys import stdin
import re
import sys
import math

number_pat = "[1-9]\d*\n"
int_re = re.compile(number_pat)

line = stdin.readline()

# first line, one integer.    
assert int_re.match(line)

N = int(line)
assert 1 <= N <= 100000 

# check two lines with N numbers
for i in xrange(2):
    line = stdin.readline()
    assert len(line.strip().split()) == N
    for x in line.strip().split():
        assert -100000 <= int(x) <= 100000

assert len(stdin.readline()) == 0
sys.exit(42)
