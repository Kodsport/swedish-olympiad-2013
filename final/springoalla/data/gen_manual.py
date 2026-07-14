#!/usr/bin/python3

# Emit a hand-picked case: l is a comma-separated list of trail lengths and t
# is the target time. (The trailing seed argument is ignored.)

import sys


def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=", 1)[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default


lengths = [int(x) for x in cmdlinearg('l').split(',')]
t = int(cmdlinearg('t'))

print(len(lengths), t)
print(*lengths)
