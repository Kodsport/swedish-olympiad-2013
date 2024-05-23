#!/usr/bin/python
from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"
line = stdin.readline()
assert re.match(integer + " " + integer + "\n" , line)
N=int(line.split()[0])
P=int(line.split()[1])
assert 1<=N<=1000
assert 1<=P<=1000
line = stdin.readline()
assert line==""
sys.exit(42)

