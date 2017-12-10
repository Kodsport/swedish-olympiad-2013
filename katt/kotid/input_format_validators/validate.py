from sys import stdin
import re
import sys
import math

number_pat = "[1-9]\d*"
twonumbers_pat = number_pat + " " + number_pat + "\n"
int2_re = re.compile(twonumbers_pat)

line = stdin.readline()

# first line, one integer.    
assert int2_re.match(line)

n,k = map(int,line.strip().split())
assert 1 <= n <= 10**6 
assert 1 <= k <= 10**8

# check two lines with N numbers
line = stdin.readline()
assert len(line.strip().split()) == n
for x in line.strip().split():
    assert 1 <= int(x) <= k

assert len(stdin.readline()) == 0
sys.exit(42)
