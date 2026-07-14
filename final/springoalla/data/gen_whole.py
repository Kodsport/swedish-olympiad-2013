#!/usr/bin/python3

# Emit a case where running only whole trails is optimal (subtask 2).
#
# maxl must divide t. The longest trail then has length maxl, so every run --
# whole or half -- covers at most maxl minutes, meaning any solution needs at
# least t/maxl runs and t_s >= t. Running the longest trail t/maxl times whole
# attains (t, t/maxl), so that is the optimum and it uses no half trails.

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
maxl = int(cmdlinearg('maxl'))

assert 2 <= maxl <= 40000 and maxl % 2 == 0
assert t % maxl == 0

# Lengths may repeat; only the longest one is pinned down.
lengths = [maxl] + [2 * random.randint(1, maxl // 2) for _ in range(n - 1)]
random.shuffle(lengths)

print(n, t)
print(*lengths)
