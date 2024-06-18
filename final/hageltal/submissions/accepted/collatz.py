#/usr/bin/env python3
import sys


def seq(n):
    if n == 1:
        return [1]
    elif n % 2 == 0:
        return [n] + seq(n / 2)
    else:
        return [n] + seq(n * 3 + 1)


tokens = sys.stdin.readline().split()
s1 = seq(int(tokens[0]))
s2 = seq(int(tokens[1]))

for a in s1:
    if a in s2:
        print(s1.index(a) + s2.index(a))
        break
