#!/usr/bin/python
from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"
line = stdin.readline()
assert re.match(integer + " " + integer + "\n" , line)
N=int(line.split()[0])
K=int(line.split()[1])
assert (1<=N<=999999999999)
assert (K>=1)
line = stdin.readline()
assert line==""
sys.exit(42)

