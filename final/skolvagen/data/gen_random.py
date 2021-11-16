#!/usr/bin/env python3

import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

seed = int(cmdlinearg('seed', sys.argv[-1]))
random.seed(seed)
L = int(cmdlinearg('len'))

print(''.join(random.choice(['S', 'N', 'B']) for _ in range(L)))
