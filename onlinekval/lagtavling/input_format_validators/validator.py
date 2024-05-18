#!/usr/bin/python
from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"
line = stdin.readline()
assert re.match(integer + " " + integer + "\n" , line)
N=int(line.split()[0])
K=int(line.split()[1])
assert (N>0 and N<=1000)
assert (K>0 and K<=N)
line = stdin.readline()
line=line[:(len(line)-1)]
for c in line:
   assert c>='A' and c<='Z'
assert len(line)==N
# Nothing to report
sys.exit(42)

