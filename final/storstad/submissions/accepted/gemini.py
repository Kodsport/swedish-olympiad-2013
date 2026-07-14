n, m = map(int, input().split())
o = 10000
k = 20000
cx = [0] * (k + 1)
cy = [0] * (k + 1)
for _ in range(n):
    x, y = input().split()
    cx[int(x) + o] += 1
    cy[int(y) + o] += 1

sx = [0] * (k + 1)
sy = [0] * (k + 1)

sx[0] = sum(cx[i] * i for i in range(k + 1))
lc = 0
for i in range(1, k + 1):
    lc += cx[i - 1]
    sx[i] = sx[i - 1] + lc - (n - lc)

sy[0] = sum(cy[i] * i for i in range(k + 1))
lc = 0
for i in range(1, k + 1):
    lc += cy[i - 1]
    sy[i] = sy[i - 1] + lc - (n - lc)

ans = 10**18
for _ in range(m):
    x, y = input().split()
    val = sx[int(x) + o] + sy[int(y) + o]
    if val < ans:
        ans = val

print(ans)
