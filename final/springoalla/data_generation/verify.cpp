// Ground-truth check: read an input file, report t_s, n_s, and the minimum
// number of half-trails over all optimal solutions.
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int main(int argc, char** argv) {
    int HMAX = atoi(argv[2]);
    ifstream in(argv[1]);
    int n, t; in >> n >> t;
    vector<int> u(n); for (auto& x : u) { in >> x; x /= 2; }
    int XMAX = t + 40001;
    vector<vector<int>> dp(HMAX+1, vector<int>(XMAX, INF));
    for (int h = 0; h <= HMAX; h++) dp[h][0] = 0;
    for (int x = 1; x < XMAX; x++)
        for (int h = 0; h <= HMAX; h++) {
            int b = INF;
            for (int c : u) {
                if (x >= 2*c) b = min(b, dp[h][x-2*c] + 1);
                if (h > 0 && x >= 3*c) b = min(b, dp[h-1][x-3*c] + 2);
            }
            dp[h][x] = b;
        }
    auto first = [&](int h) { for (int x = t; x < XMAX; x++) if (dp[h][x] < INF) return x; return -1; };
    int ts = first(HMAX), rs = dp[HMAX][ts];
    printf("n=%d t=%d  ->  t_s=%d  n_s=%d\n", n, t, ts, rs);
    int need = -1;
    for (int h = 0; h <= HMAX; h++) {
        int x = first(h);
        bool ok = (x == ts && dp[h][x] == rs);
        if (ok) { need = h; printf("   <=%2d halves: (%d, %d)  OPTIMAL\n", h, x, dp[h][x]); break; }
        printf("   <=%2d halves: (%d, %d)  worse\n", h, x, x < 0 ? -1 : dp[h][x]);
    }
    printf("\n==> MINIMUM HALF-TRAILS REQUIRED IN ANY OPTIMAL SOLUTION: %d\n", need);
}
