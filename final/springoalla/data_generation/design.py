# Coins u_j = 1 + j*q  (all == 1 mod q), so O == 2r - T (mod q) for ANY solution.
# maxT(r,O) = max minutes with r runs and O half-trails
#           = 2*(r-2O)*U + 3*S_O   (S_O = sum of the O largest coins, U = largest)
# Choose T = maxT(r,O): then r runs with O halves is exactly tight, and every
# r' < r is infeasible iff T > maxT(r', (2r'-T) % q).
def coins(q, n): return [1 + j*q for j in range(n)]

best = None
for q in range(3, 80):
    for n in range(2, 200):
        u = coins(q, n)
        U = u[-1]
        if 2*U > 40000: break
        pre = [0]
        for c in reversed(u): pre.append(pre[-1] + c)      # pre[O] = sum of O largest
        def maxT(r, O):
            if O > n or 2*O > r: return -1
            return 2*(r - 2*O)*U + 3*pre[O]
        for O in range(1, min(n, q-1) + 1):
            for r in range(2*O, 4000):
                T = maxT(r, O)
                if T > 100000: break
                if T < 1: continue
                if all(T > maxT(rp, (2*rp - T) % q) for rp in range(2*O, r)):
                    cand = (O, -n, q, n, r, T, U)
                    if best is None or (O, -n) > (best[0], best[1]): best = cand
print("best: halves=%d  q=%d n=%d runs=%d t=%d u_max=%d" % (best[0], best[2], best[3], best[4], best[5], best[6]))
q, n, r, T = best[2], best[3], best[4], best[5]
print("lengths (l_i = 2*u_i):", [2*c for c in coins(q, n)])
