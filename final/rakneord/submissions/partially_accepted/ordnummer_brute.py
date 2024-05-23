#!/usr/bin/env python3/
import sys

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


line = sys.stdin.readline().split()
N = int(line[0])
K = int(line[1])

tal = [rakneord(i) for i in range(1, N + 1)]
tal.sort()
s = "".join(tal)
print(s[(K - 1) : (K + 2)])
