#!/usr/bin/python3
from sys import stdin
import re
import sys
import math

line = stdin.readline()
int_pat = "[1-9]\d*"
int_re = re.compile(int_pat)
topline_pat = int_pat + " " + int_pat
topline_re = re.compile(topline_pat)

assert topline_re.match(line)
N,P = list(map(int, line.strip().split()))

assert 1 <= N <= 130000
assert 1 <= P <= 100000

for i in range(P):
    line = stdin.readline()
    numbers = line.strip().split()
    assert 3 <= len(numbers) <= 26
    assert 2 <= int(numbers[0]) <= 25
    assert int(numbers[0]) == len(numbers)-1
    for num in numbers[1:]:
        assert 0 <= int(num) <= N-1

assert len(stdin.readline()) == 0
sys.exit(42)
