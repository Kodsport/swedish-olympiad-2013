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

n = int(cmdlinearg('n'))
t = int(cmdlinearg('t'))
# Trail lengths are drawn as distinct even numbers 2..2*pool (capped so they
# never exceed 2*(t//2) = t, matching the original generator).
pool = int(cmdlinearg('pool', 20000))

cap = min(pool, t // 2)
lengths = [2 * x for x in random.sample(range(1, cap + 1), n)]

print(n, t)
print(*lengths)
