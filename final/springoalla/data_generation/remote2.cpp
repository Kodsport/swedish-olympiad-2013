// Focused: can a 9- or 10-coin chain with ratio just above 3 force 9/10 halves?
// (ratio 4 -> only 8 coins fit under u<=20000; ratio must stay >3 or the
//  base-3 digit sum gets cheap enough that whole-only wins.)
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
const int INF = 1e9;
int MAXT = 100000, UCAP = 20000;

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
int main(int argc, char** argv) {
    int m = atoi(argv[1]), iters = atoi(argv[2]), threads = atoi(argv[3]);
    omp_set_num_threads(threads);
    int gBest = -1; vector<int> gU; int gT = 0;
    #pragma omp parallel for schedule(dynamic)
    for (int it = 0; it < iters; it++) {
        mt19937_64 rng(it * 7919ULL + 4242);
        vector<int> u{1};
        bool ok = true;
        for (int i = 1; i < m && ok; i++) {
            double lo = 3.0 * u.back() + 1;
            double hi = 3.9 * u.back();
            double room = UCAP / pow(3.0, m - 1 - i);   // must leave room for >3x steps
            hi = min(hi, room);
            if (hi < lo) { ok = false; break; }
            u.push_back((int)(lo + rng() % (uint64_t)max(1.0, hi - lo + 1)));
        }
        if (!ok || (int)u.size() != m || u.back() > UCAP) continue;
        auto s = score(u);
        for (int step = 0; step < 120; step++) {          // multiplicative hill climb
            vector<int> v = u;
            int i = 1 + rng() % (v.size() - 1);
            int mag = max(1, v[i] / 20);
            long long nv = (long long)v[i] + ((int)(rng() % (2*mag+1)) - mag);
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
            printf("m=%d HALVES=%d t=%d lengths:", m, gBest, gT);
            for (int c : gU) printf(" %d", 2*c);
            printf("\n"); fflush(stdout);
        }
    }
    printf("\nBEST m=%d HALVES=%d t=%d\nlengths:", m, gBest, gT);
    for (int c : gU) printf(" %d", 2*c);
    printf("\n");
}
