#!/usr/bin/python3

import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

N = int(cmdlinearg('n'))
M = int(cmdlinearg('m'))
A = int(cmdlinearg('a'))

print(N, M)
for i in range(N+M):
	x = random.randint(-A, A)
	y = random.randint(-A, A)
	print(x, y)