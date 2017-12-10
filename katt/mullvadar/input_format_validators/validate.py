from sys import stdin
import re
import sys
import math

char_re = re.compile("(A|\\.)+\n")
int_re = re.compile("[1-9]\d*\n")

line = stdin.readline()
N = len(line.strip())
assert 1 <= N <= 100
assert char_re.match(line)

line = stdin.readline()
assert int_re.match(line)
t = int(line)
assert 0 <= t <= 10**18

assert len(stdin.readline()) == 0
sys.exit(42)
