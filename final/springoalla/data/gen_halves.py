#!/usr/bin/python3

# Force every optimal solution to run MANY half trails.
#
# Write u_i = l_i / 2. Trail i can contribute k_i * u_i minutes (k_i = 0, or
# k_i >= 2) and that costs ceil(k_i / 2) runs, so a half trail is used exactly
# when k_i is odd. Take the trail lengths to be l_i = 2 * 4^i, i.e. u_i = 4^i,
# and set
#
#     t = 4^m - 1 = 3 * (4^0 + 4^1 + ... + 4^(m-1)).
#
# Running every trail once whole and once half (k_i = 3 for all i) hits exactly
# t minutes in 2m runs and uses all m half trails. Dropping a half means paying
# for the missing u_i with whole trails instead, and because each trail of the
# chain is worth four of the one below it, the cheapest whole-only replacement
# is a base-4 digit sum, which costs up to 3m runs -- strictly worse than 2m.
# So all m halves are forced.
#
# Base 4 is the smallest ratio that works (with ratio 3, three trails of one
# size exactly rebuild the next one up, which keeps whole-only representations
# cheap) and the largest ratio that still fits 8 trails under l <= 40000.
#
# Padding trails repeat lengths already in the chain. A duplicate length is not
# a new value, so it cannot give a solver any option it did not already have,
# but it lets the case use the full n.

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

m = int(cmdlinearg('m'))
n = int(cmdlinearg('n', m))
assert n >= m, "n must leave room for the whole chain"

chain = [2 * 4**i for i in range(m)]
t = 4**m - 1

lengths = chain + [chain[i % m] for i in range(n - m)]
random.shuffle(lengths)

print(n, t)
print(*lengths)
