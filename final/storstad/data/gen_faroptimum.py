#!/usr/bin/python3

# The cost of a house is  cost(x, y) = F(x) + G(y), where F and G are convex
# and minimised at the MEDIAN of the friends' x resp. y coordinates. Heuristics
# that rank the candidate houses by distance to some centre of the friends and
# then brute force the best-looking ones (in particular, distance to the MEAN)
# are fooled here:
#
#   x: half the friends far left, half far right   ->  F has slope 2     (flat)
#   y: 90% of the friends far down, 10% far up     ->  G has slope 80000 (steep)
#
# so the mean sits near (0, -8000) while the median sits near (-10000, -10000),
# and the cost is dominated by y. Exactly one house gets the optimal y, and it
# is pushed out to x = +10000 -- the flat F makes that almost free, but it puts
# the house as far as possible from the median. Every other house is a decoy
# packed tightly around the mean.
#
# The unique optimum is therefore the house farthest from the mean, from the
# median AND from the origin, so any "look at the houses nearest some centre"
# order visits it dead last. The friends and the houses are also almost all
# distinct points, so collapsing duplicates does not shrink the brute force.

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

N = int(cmdlinearg('n'))
M = int(cmdlinearg('m'))
MAXC = 10000

# Width of the friend clusters. Wide enough that the friends are mostly
# distinct points, narrow enough that F and G keep their intended slopes.
W = 400

n_left = N // 2 + 1              # a hair more than half -> F slopes gently up
n_right = N - n_left
n_down = (N * 9) // 10           # 90% low  -> G slopes steeply up
n_up = N - n_down

xs = ([random.randint(-MAXC, -MAXC + W) for _ in range(n_left)] +
      [random.randint(MAXC - W, MAXC) for _ in range(n_right)])
ys = ([random.randint(-MAXC, -MAXC + W) for _ in range(n_down)] +
      [random.randint(MAXC - W, MAXC) for _ in range(n_up)])

random.shuffle(xs)
random.shuffle(ys)
friends = list(zip(xs, ys))

# The L1 cost is minimised at the median, so this is the best y available.
best_y = sorted(ys)[len(ys) // 2]
good = (MAXC, best_y)

# Decoys: distinct lattice points packed around the mean of the friends.
cx = round(sum(xs) / N)
cy = round(sum(ys) / N)
# radius chosen so the blob holds at least M - 1 distinct points
R = 1
while (2 * R + 1) ** 2 < M - 1:
    R += 1
if not (-MAXC <= cx - R and cx + R <= MAXC and -MAXC <= cy - R and cy + R <= MAXC):
    print("decoy blob falls outside the coordinate range", file=sys.stderr)
    sys.exit(1)

cells = [(x, y)
         for x in range(cx - R, cx + R + 1)
         for y in range(cy - R, cy + R + 1)]
if good in cells:
    print("the good house is inside the decoy blob", file=sys.stderr)
    sys.exit(1)

houses = random.sample(cells, M - 1) + [good]
random.shuffle(houses)

out = ["%d %d" % (N, M)]
out += ["%d %d" % p for p in friends]
out += ["%d %d" % p for p in houses]
print("\n".join(out))
