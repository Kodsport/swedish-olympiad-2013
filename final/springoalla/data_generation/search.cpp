// Search for coin sets (u_i = l_i/2) + target t maximizing the number of
// half-trails REQUIRED in every optimal solution.
//
// dp[h][x] = min runs to run exactly x minutes using at most h half-trails.
// items per trail: whole (2u, 1 run, 0 halves), whole+half (3u, 2 runs, 1 half).
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int HMAX, XMAX;
vector<vector<int>> dp, nxt;

void build(const vector<int>& u, int tmax) {
    XMAX = tmax + 40001;
    dp.assign(HMAX + 1, vector<int>(XMAX, INF));
    for (int h = 0; h <= HMAX; h++) dp[h][0] = 0;
    for (int x = 1; x < XMAX; x++)
        for (int h = 0; h <= HMAX; h++) {
            int b = INF;
            for (int c : u) {
                if (x >= 2*c && dp[h][x-2*c] + 1 < b) b = dp[h][x-2*c] + 1;
                if (h > 0 && x >= 3*c && dp[h-1][x-3*c] + 2 < b) b = dp[h-1][x-3*c] + 2;
            }
            dp[h][x] = b;
        }
    nxt.assign(HMAX + 1, vector<int>(XMAX + 1, XMAX));
    for (int h = 0; h <= HMAX; h++) {
        nxt[h][XMAX] = XMAX;
        for (int x = XMAX - 1; x >= 0; x--)
            nxt[h][x] = (dp[h][x] < INF) ? x : nxt[h][x+1];
    }
}
// returns required halves for target t, and fills ts/rs
int required(int t, int& ts, int& rs) {
    ts = nxt[HMAX][t];
    if (ts >= XMAX) return -1;
    rs = dp[HMAX][ts];
    for (int h = 0; h <= HMAX; h++)
        if (nxt[h][t] == ts && dp[h][ts] == rs) return h;
    return -1;
}
int main(int argc, char** argv) {
    int maxn = atoi(argv[1]), maxt = atoi(argv[2]);
    HMAX = atoi(argv[3]);
    int bestH = -1; string bestDesc; 
    auto eval = [&](vector<int> u, string tag) {
        if ((int)u.size() > maxn) return;
        build(u, maxt);
        for (int t = 1; t <= maxt; t++) {
            int ts, rs, h = required(t, ts, rs);
            if (h > bestH) {
                bestH = h;
                char buf[512];
                snprintf(buf, sizeof buf, "%-22s n=%d t=%d -> t_s=%d n_s=%d  REQUIRED HALVES=%d",
                         tag.c_str(), (int)u.size(), t, ts, rs, h);
                bestDesc = buf;
                printf("%s\n  lengths: ", buf);
                for (int c : u) printf("%d ", 2*c);
                printf("\n"); fflush(stdout);
            }
        }
    };
    // family A: powers of 4
    { vector<int> u; for (long long p = 1; 2*p <= 40000; p *= 4) u.push_back((int)p); eval(u, "pow4"); }
    // family B: u_j = 1 + j*q  (all u = 1 mod q)
    for (int q = 2; q <= 200; q++)
        for (int n = 2; n <= min(maxn, 60); n++) {
            long long top = 1 + (long long)(n-1)*q;
            if (2*top > 40000) break;
            vector<int> u; for (int j = 0; j < n; j++) u.push_back(1 + j*q);
            eval(u, "ap1modq q=" + to_string(q));
        }
    printf("\nBEST: %s\n", bestDesc.c_str());
}
