#!/usr/bin/env -S python3 -B
import math
from datatools import use_solution, generator, samples, secret, io, random, subtask, graphs

use_solution("js.cpp")

def case(L, T):
    io.line(len(L), T)
    io.line(*L)

@generator
def manual(L, T):
    case(L, T)

@generator
def rand(N, T):
    case([2 * x for x in random.sample(range(1, min(20000, T // 2)+1), N)], T)

@generator
def rand_small(N, T):
    case([2 * x for x in random.sample(range(1, min(100, T // 2)+1), N)], T)

@generator
def close_many(N, T):
    L = T // N
    p = [N - 2 * p for p in random.sample(range(1, 500), 40)]
    s = (L - 40) * N + sum(p)
    case([N] + p + list(range(2, 100, 2)), s)

task1 = subtask(score=20, maxn=10, maxt=1000, onlywhole=0).include(samples())
task2 = subtask(score=30, maxn=1000, maxt=100000, onlywhole=1)
task3 = subtask(score=50, maxn=1000, maxt=100000, onlywhole=0).include(task1, task2)

with samples(maxn=1000, maxt=100000, onlywhole=0):
    manual([10, 8, 14], 23)
    manual([8, 12, 14], 23)
    manual([2], 3)
    manual([4], 7)

with task1:
    rand(3, 1000)
    rand(3, 1000)
    rand(3, 1000)
    rand(10, 1000)
    rand(10, 1000)
    rand(10, 1000)
    manual([2], 1000)
    manual([2, 4, 8, 10], 1000)
    manual([10, 18], 991)
    manual([10, 18], 990)
    manual([10, 18], 989)

with task2:
    manual([10000, 20000, 40000], 100000)
    manual([40000], 40000)
    manual([40000], 39999)
    manual([2, 4, 6, 8, 10, 30, 34, 36, 38], 98800)
    close_many(1000, 100000)
    close_many(10000, 100000)

with task3:
    manual([40000], 40001)
    manual([40000], 60000)
    manual([40000], 60001)
    manual([40000], 59999)
    rand(30, 100000)
    rand(30, 100000)
    rand(30, 100000)
    rand(30, 100000)
    rand_small(30, 100000)
    rand_small(30, 100000)
    rand(1000, 100000)
    rand(1000, 100000)
    rand(1000, 100000)
