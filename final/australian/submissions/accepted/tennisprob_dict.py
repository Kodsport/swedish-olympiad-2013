#!/usr/bin/env python3
import sys
import math


def s(xa, xb):
    y = 1.0 / (1.0 + math.exp(xb - xa))
    return y


def match(a, b):
    global ss
    keys = list(a.keys()) + list(b.keys())
    res = dict(list(zip(keys, [0.0] * len(keys))))
    for i, pa in a.items():
        for j, pb in b.items():
            paw = ss[i][j]
            res[i] += pa * pb * paw
            res[j] += pa * pb * (1 - paw)
    return res


def play(plist):
    N = len(plist)
    if N == 1:
        return plist[0]
    return match(play(plist[0 : N // 2]), play(plist[N // 2 : N]))


lines = sys.stdin.readlines()
n = 2 ** int(lines[0])
skill = [float(x) for x in lines[1].split()]
if len(skill) != n:
    print("Error in input")
    exit(0)

ss = [[s(skill[i], skill[j]) for j in range(n)] for i in range(n)]
winner = play([{i: 1.0} for i in range(n)])
(best, prob) = max(list(winner.items()), key=lambda x: x[1])
print(best + 1, "%.8f" % prob)
