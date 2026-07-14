#!/usr/bin/python3
"""Dev version of the 'far optimum' generator: prints the test to stdout and a
full analysis to stderr so we can check the attack actually works.

Idea
----
The Manhattan cost of a house is  cost(x,y) = F(x) + G(y)  where
F/G are convex piecewise-linear and minimised at the *median* of the friends'
x / y coordinates.  joshua_cheese1/2 order the candidate houses by distance to
the *mean* of the friends and brute force in that order with a time cutoff.

So we build friends whose mean is far from their median:

  x:  50001 friends far left,  49999 far right   ->  F(x) ~= 2*x + C      (slope 2, almost flat)
  y:  90000 friends far down,  10000 far up      ->  G(y) ~= 80000*y + C  (slope 80000, very steep)

  mean   ~= (0, -8000)
  median ~= (-9800, -9800)

cost is therefore dominated by y.  We give exactly one house the (near) optimal
y and push it to x = +10000, i.e. as far as possible from the median.  Every
other house is a decoy packed tightly around the *mean*.

Result: the unique optimum is the house that is *farthest* from the mean, from
the median and from the origin, so it is sorted dead last by any
"distance to some centre" ordering and the time cutoff never reaches it.
"""

import sys
import random

MAXC = 10000

random.seed(int(sys.argv[1]) if len(sys.argv) > 1 else 12345)

N = 100000
M = 100000

# how wide the friend clusters are; wide enough that friends are mostly
# distinct points, so grouping equal friends does not rescue a brute force
W = 400
# half-width of the decoy blob around the mean; (2*R+1)^2 must exceed M so the
# decoys can be pairwise distinct and de-duplicating houses does not help
R = 200

N_LEFT = N // 2 + 1        # 50001
N_RIGHT = N - N_LEFT       # 49999
N_DOWN = 90000
N_UP = N - N_DOWN          # 10000

xs = ([random.randint(-MAXC, -MAXC + W) for _ in range(N_LEFT)] +
      [random.randint(MAXC - W, MAXC) for _ in range(N_RIGHT)])
ys = ([random.randint(-MAXC, -MAXC + W) for _ in range(N_DOWN)] +
      [random.randint(MAXC - W, MAXC) for _ in range(N_UP)])

random.shuffle(xs)
random.shuffle(ys)
friends = list(zip(xs, ys))

# L1 cost is minimised at the median, so this y is the best possible y
med_y = sorted(ys)[len(ys) // 2]
med_x = sorted(xs)[len(xs) // 2]
mean_x = sum(xs) / N
mean_y = sum(ys) / N

# the one good house: optimal y, but as far from the median as x allows
good = (MAXC, med_y)

# decoys: distinct lattice points packed around the mean
cx = int(round(mean_x))
cy = int(round(mean_y))
cells = [(x, y)
         for x in range(cx - R, cx + R + 1)
         for y in range(cy - R, cy + R + 1)]
assert len(cells) >= M - 1, "decoy blob too small to hold distinct decoys"
decoys = random.sample(cells, M - 1)
assert good not in decoys, "decoy collided with the good house"

houses = decoys + [good]
random.shuffle(houses)

out = [f"{N} {M}"]
out += [f"{x} {y}" for x, y in friends]
out += [f"{x} {y}" for x, y in houses]
sys.stdout.write("\n".join(out) + "\n")


# ---------------------------------------------------------------- analysis ---
def cost(h):
    hx, hy = h
    # F(x) + G(y), computed exactly via the friend coordinate lists
    return (sum(abs(hx - fx) for fx in xs) + sum(abs(hy - fy) for fy in ys))


# exact cost of every house, the cheap way (prefix sums over sorted coords)
sxs, sys_ = sorted(xs), sorted(ys)
import bisect
pre_x = [0]
for v in sxs:
    pre_x.append(pre_x[-1] + v)
pre_y = [0]
for v in sys_:
    pre_y.append(pre_y[-1] + v)


def axis_cost(v, arr, pre):
    i = bisect.bisect_left(arr, v)
    left = v * i - pre[i]
    right = (pre[len(arr)] - pre[i]) - v * (len(arr) - i)
    return left + right


costs = [(axis_cost(hx, sxs, pre_x) + axis_cost(hy, sys_, pre_y), (hx, hy))
         for hx, hy in houses]
best_cost, best_house = min(costs)
good_cost = axis_cost(good[0], sxs, pre_x) + axis_cost(good[1], sys_, pre_y)
best_decoy = min(axis_cost(hx, sxs, pre_x) + axis_cost(hy, sys_, pre_y)
                 for hx, hy in decoys)

n_argmin = sum(1 for c, _ in costs if c == best_cost)


def euclid(a, b):
    return ((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2) ** 0.5


def manh(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


mean_pt = (mean_x, mean_y)
med_pt = (med_x, med_y)

# where does the good house land in each candidate ordering?
def rank(keyfn):
    keys = sorted(keyfn(h) for h in houses)
    return bisect.bisect_left(keys, keyfn(good))

r_eucl_mean = rank(lambda h: euclid(h, mean_pt))          # cheese1's ordering
r_manh_mean = rank(lambda h: manh(h, (int(mean_x), int(mean_y))))  # cheese2's
r_manh_med = rank(lambda h: manh(h, med_pt))              # the obvious "fix"
r_eucl_orig = rank(lambda h: euclid(h, (0, 0)))

e = sys.stderr.write
e(f"mean   = ({mean_x:.2f}, {mean_y:.2f})\n")
e(f"median = {med_pt}\n")
e(f"good house      = {good}\n")
e(f"answer (min)    = {best_cost}   attained by {best_house}\n")
e(f"  #houses attaining the min : {n_argmin}  (want 1)\n")
e(f"  good house cost           : {good_cost}\n")
e(f"  best decoy cost           : {best_decoy}\n")
e(f"  margin (decoy - good)     : {best_decoy - good_cost}\n")
e("\nrank of the good house in each ordering (0 = visited first, "
  f"{M-1} = visited last):\n")
e(f"  euclid-to-mean  (cheese1) : {r_eucl_mean}\n")
e(f"  manhattan-to-mean (cheese2): {r_manh_mean}\n")
e(f"  manhattan-to-median (patch): {r_manh_med}\n")
e(f"  euclid-to-origin  (patch) : {r_eucl_orig}\n")
e(f"\ndistinct friends = {len(set(friends))}  distinct houses = {len(set(houses))}\n")
