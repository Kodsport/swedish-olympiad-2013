#!/usr/bin/python
from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"
line = stdin.readline()
assert re.match(integer + " " + integer + "\n" , line)
N=int(line.split()[0])
P=int(line.split()[1])
assert (N>=3 and N<=20)
assert (P>=1 and P<=100)

line = stdin.readline()
assert re.match((N-2)*(integer + " ") + integer + "\n" , line)
km=[int(x) for x in line.split()]
for k in km:
   assert 2<=k<=1000
for p in range(P):
   line = stdin.readline()
   assert re.match(integer + " " + integer + " " + integer + "\n" , line)
   A=int(line.split()[0])
   B=int(line.split()[1])
   T=int(line.split()[2])
   assert 1<=A<B<=N
   assert 2<=T<=1000
   
line = stdin.readline()
assert line==""
sys.exit(42)

