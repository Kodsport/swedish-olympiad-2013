from sys import stdin
import re
import sys
import math

char_re = re.compile("([0-5]|X)*\n")

line = stdin.readline()

N = len(line.strip())
assert 1 <= N <= 50000
assert char_re.match(line)

assert len(stdin.readline()) == 0
sys.exit(42)
