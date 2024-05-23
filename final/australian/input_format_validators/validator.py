#!/usr/bin/python
from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"
flo='-?\d+(?:\.\d+)?'   #Full format: -?(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?
line = stdin.readline()
assert re.match(integer + "\n" , line)
N=int(line.split()[0])
assert 1<=N<=10
n=2**N
line = stdin.readline()
assert re.match((n-1)*(flo + " ") + flo + "\n" , line)
f=[float(x) for x in line.split()]
for k in f:
   assert 0<k<10
line = stdin.readline()
assert line==""
sys.exit(42)

