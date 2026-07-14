// Unconstrained annealing over coin sets: is 8 (powers of 4) really the max
// number of half-trails forcible under l<=40000, t<=100000?
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
const int INF = 1e9;
const int MAXT = 100000, UCAP = 20000, X = MAXT + 40001;

pair<int,int> score(const vector<int>& u) {
    int H = (int)u.size();
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
    int restarts = atoi(argv[1]), steps = atoi(argv[2]), threads = atoi(argv[3]);
    omp_set_num_threads(threads);
    int gBest = -1; vector<int> gU; int gT = 0;
    #pragma omp parallel for schedule(dynamic)
    for (int r = 0; r < restarts; r++) {
        mt19937_64 rng(r * 1000003ULL + 777);
        vector<int> u;
        if (r % 4 == 0) { for (long long p = 1; p <= UCAP; p *= 4) u.push_back((int)p); }  // seed from pow4
        else {
            int m = 4 + rng() % 14;
            set<int> S;
            while ((int)S.size() < m) S.insert(1 + rng() % UCAP);
            u.assign(S.begin(), S.end());
        }
        auto s = score(u);
        for (int step = 0; step < steps; step++) {
            vector<int> v = u;
            int op = rng() % 4;
            if (op == 0 && v.size() > 3) v.erase(v.begin() + rng() % v.size());
            else if (op == 1 && v.size() < 20) v.push_back(1 + rng() % UCAP);
            else {
                int i = rng() % v.size();
                int mag = max(2, v[i] / 8);                       // multiplicative move
                long long nv = (long long)v[i] + ((int)(rng() % (2*mag+1)) - mag);
                if (nv < 1 || nv > UCAP) continue;
                v[i] = (int)nv;
            }
            sort(v.begin(), v.end());
            if (adjacent_find(v.begin(), v.end()) != v.end()) continue;
            auto s2 = score(v);
            if (s2.first >= s.first) { u = v; s = s2; }
        }
        #pragma omp critical
        if (s.first > gBest) {
            gBest = s.first; gU = u; gT = s.second;
            printf("HALVES=%d n=%d t=%d lengths:", gBest, (int)gU.size(), gT);
            for (int c : gU) printf(" %d", 2*c);
            printf("\n"); fflush(stdout);
        }
    }
    printf("\nGLOBAL BEST HALVES=%d n=%d t=%d\nlengths:", gBest, (int)gU.size(), gT);
    for (int c : gU) printf(" %d", 2*c);
    printf("\n");
}
