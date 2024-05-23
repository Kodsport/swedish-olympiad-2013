#!/usr/bin/python
from sys import stdin
import sys
import re

integer = "(?:0|-?[1-9]\d*)"
line = stdin.readline()
assert re.match(integer + " " + integer + "\n" , line)
N=int(line.split()[0])
K=int(line.split()[1])
assert (1<=N<=100)
assert (1<=K<=10000)

for i in range(N):
   line = stdin.readline()
   assert re.match((N-1)*(integer + " ") + integer + "\n" , line)
   rad=[int(x) for x in line.split()]
   for r in rad: assert 1<=r<=1000
line = stdin.readline()
assert re.match((K-1)*(integer + " ") + integer + "\n" , line)
rad=[int(x) for x in line.split()]
for r in rad: assert 1<=r<=1000
line = stdin.readline()
assert line==""
sys.exit(42)

