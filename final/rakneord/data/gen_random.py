#!/usr/bin/env python3

import sys
import random as rnd

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

rnd.seed(int(cmdlinearg('seed', sys.argv[-1])))

def getLength(N: int):
    s1 = [
        "",
        "ett",
        "tva",
        "tre",
        "fyra",
        "fem",
        "sex",
        "sju",
        "atta",
        "nio",
        "tio",
        "elva",
        "tolv",
        "tretton",
        "fjorton",
        "femton",
        "sexton",
        "sjutton",
        "arton",
        "nitton",
    ]
    s2 = ["tjugo", "trettio", "fyrtio", "femtio", "sextio", "sjuttio", "attio", "nittio"]


    def r1(n, efter):
        if n == 1 and efter:
            return "en"
        return s1[n]


    def r2(n, efter):
        if n < 20:
            return r1(n, efter)
        return s2[n // 10 - 2] + r1(n % 10, efter)


    def r3(n):
        if n == 0:
            return ""
        else:
            return s1[n] + "hundra"


    def r6(n):
        if n == 0:
            return ""
        elif n == 1:
            return "ettusen"
        else:
            return r3((n % 1000) // 100) + r2(n % 100, True) + "tusen"


    def r9(n):
        if n == 0:
            return ""
        elif n == 1:
            return "enmiljon"
        else:
            return r3((n % 1000) // 100) + r2(n % 100, True) + "miljoner"


    def r12(n):
        if n == 0:
            return ""
        elif n == 1:
            return "enmiljard"
        else:
            return r3((n % 1000) // 100) + r2(n % 100, True) + "miljarder"


    def rakneord(n):
        return (
            r12((n % 1000000000000) // 1000000000)
            + r9((n % 1000000000) // 1000000)
            + r6((n % 1000000) // 1000)
            + r3((n % 1000) // 100)
            + r2(n % 100, False)
        )


    tal = [rakneord(i) for i in range(1, N + 1)]
    tal.sort()
    s = "".join(tal)
    return len(s)

LENGTHS = {
    3: 16260,
    4: 235600,
    5: 2908000,
    6: 37425000,
    7: 472250000,
    8: 5319500000,
    9: 61585000000,
    10: 722850000000,
    11: 7834500000000,
    12: 86744000000000
}

max_n = int(cmdlinearg("n", 10**12-1))

n = rnd.randint(1, max_n)


if n < 10**6:
    k = rnd.randint(1, getLength(n)-2)
else:
    k = rnd.randint(1, len(str(n)))

print(n, k)