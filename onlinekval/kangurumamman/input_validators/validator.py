#!/usr/bin/python3
from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"
line = stdin.readline()
assert re.match(integer + "\n", line)
N=int(line)
assert (N>0 and N<=1000)
line = stdin.readline()
assert len(line)==0
# Nothing to report
sys.exit(42)

