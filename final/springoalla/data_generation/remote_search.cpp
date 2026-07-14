// Maximize the number of half-trails REQUIRED in every optimal solution.
//
// u_i = l_i/2. Theory: for a geometric chain of ratio b, "use every trail once
// whole + once half" costs 2m runs, while any whole-only alternative costs a
// base-b digit sum (up to (b-1)m). So halves win iff b > 3, and the coin count
// is maxed by pushing b as close to 3 as possible: 20000^(1/8) ~ 3.32 would fit
// NINE coins instead of the eight that ratio 4 allows. Search that gap.
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
const int INF = 1e9;
int MAXT, UCAP, MAXN;

pair<int,int> score(const vector<int>& u) {
    int H = (int)u.size(), X = MAXT + 40001;
    static thread_local vector<vector<int>> dp, nx;
    dp.assign(H+1, vector<int>(X, INF));
    for (int h = 0; h <= H; h++) dp[h][0] = 0;
    for (int x = 1; x < X; x++)
        for (int h = 0; h <= H; h++) {
            int b = INF;
            for (int c : u) {
                if (x >= 2*c && dp[h][x-2*c] + 1 < b) b = dp[h][x-2*c] + 1;
                if (h > 0 && x >= 3*c && dp[h-1][x-3*c] + 2 < b) b = dp[h-1][x-3*c] + 2;
            }
            dp[h][x] = b;
        }
    nx.assign(H+1, vector<int>(X+1, X));
    for (int h = 0; h <= H; h++)
        for (int x = X-1; x >= 0; x--) nx[h][x] = (dp[h][x] < INF) ? x : nx[h][x+1];
    int best = -1, bt = 0;
    for (int t = 1; t <= MAXT; t++) {
        int ts = nx[H][t]; if (ts >= X) continue;
        int rs = dp[H][ts];
        for (int h = 0; h <= H; h++)
            if (nx[h][t] == ts && dp[h][ts] == rs) { if (h > best) { best = h; bt = t; } break; }
    }
    return {best, bt};
}
// random chain with ratio in (lo,hi), all coins distinct, last <= UCAP
vector<int> chain(mt19937_64& rng, int m, double lo, double hi) {
    vector<int> u{1};
    for (int i = 1; i < m; i++) {
        double a = lo * u.back(), b = hi * u.back();
        // keep room: remaining (m-1-i) steps each multiply by >= lo
        double room = UCAP / pow(lo, m - 1 - i);
        b = min(b, room);
        if (b < a + 1) return {};
        int v = (int)(a + 1 + rng() % (uint64_t)max(1.0, b - a));
        if (v <= u.back() || v > UCAP) return {};
        u.push_back(v);
    }
    return u;
}
int main(int argc, char** argv) {
    MAXT = atoi(argv[1]); UCAP = atoi(argv[2]); MAXN = atoi(argv[3]);
    int iters = atoi(argv[4]), threads = atoi(argv[5]);
    omp_set_num_threads(threads);
    int gBest = -1; vector<int> gU; int gT = 0;
    #pragma omp parallel for schedule(dynamic)
    for (int it = 0; it < iters; it++) {
        mt19937_64 rng(it * 1000003ULL + 12345);
        int m = 4 + rng() % (MAXN - 3);
        double lo = 3.0 + (rng() % 100) / 200.0;      // ratio lower bound 3.00..3.50
        double hi = lo + 0.1 + (rng() % 100) / 100.0;
        vector<int> u = chain(rng, m, lo, hi);
        if (u.empty()) continue;
        auto s = score(u);
        // hill climb
        for (int step = 0; step < 60; step++) {
            vector<int> v = u;
            int i = 1 + rng() % (v.size() - 1);
            int d = (int)(rng() % 21) - 10;
            long long nv = (long long)v[i] + d;
            if (nv < 2 || nv > UCAP) continue;
            v[i] = (int)nv;
            sort(v.begin(), v.end());
            if (adjacent_find(v.begin(), v.end()) != v.end()) continue;
            auto s2 = score(v);
            if (s2.first >= s.first) { u = v; s = s2; }
        }
        #pragma omp critical
        if (s.first > gBest) {
            gBest = s.first; gU = u; gT = s.second;
            printf("HALVES=%d  n=%d  t=%d  lengths:", gBest, (int)gU.size(), gT);
            for (int c : gU) printf(" %d", 2*c);
            printf("\n"); fflush(stdout);
        }
    }
    printf("\nBEST HALVES=%d  n=%d  t=%d\nlengths:", gBest, (int)gU.size(), gT);
    for (int c : gU) printf(" %d", 2*c);
    printf("\n");
}
