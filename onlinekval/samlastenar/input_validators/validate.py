#!/usr/bin/python3
from sys import stdin
import re
import sys
import math

line = stdin.readline()
number_pat = "[1-9]\d*"
int_re = re.compile(number_pat)

# First line, three integers.    
assert int_re.match(line)
N = int(line.strip())
assert 1 <= N <= 100000

for i in range(N):
    line = stdin.readline()
    assert len(line.strip().split()) == 2
    x,y = list(map(float,line.strip().split()))
    assert math.sqrt(x*x+y*y) <= 100.0

assert len(stdin.readline()) == 0
sys.exit(42)
