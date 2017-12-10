from sys import stdin
import re
import sys
import math

number_pat = "[1-9]\d* [1-9]\d*\n"
int_re = re.compile(number_pat)

zint_pat = "\d*"
zint_re = re.compile(zint_pat)

line = stdin.readline()

# first line, two integers
assert int_re.match(line)

N,M = map(int,line.strip().split())
assert 1 <= N <= 1000 
assert 1 <= M <= 1000

T = 0
# check two lines with N numbers
for i in xrange(N):
    line = stdin.readline()
    for s in line.strip().split():
        assert zint_re.match(s)
    line_splitted = map(int,line.strip().split())
    assert line_splitted[0] == len(line_splitted)-1
    assert len(set(line_splitted[1:])) == len(line_splitted[1:])
    for x in line_splitted[1:]:
        assert 1 <= x <= M
        T += 1

assert T <= 20000

assert len(stdin.readline()) == 0
sys.exit(42)
