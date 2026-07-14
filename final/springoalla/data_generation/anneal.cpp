// Simulated annealing over coin sets (u_i = l_i/2), objective = max over t<=100000
// of "half-trails required in every optimal solution".
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int MAXT = 100000, UCAP = 20000;

// returns best (required halves, t) for a coin set
pair<int,int> score(const vector<int>& u) {
    int H = (int)u.size();
    int X = MAXT + 40001;
    vector<vector<int>> dp(H+1, vector<int>(X, INF));
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
    vector<vector<int>> nx(H+1, vector<int>(X+1, X));
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
    mt19937 rng(atoi(argv[1]));
    vector<int> cur;                      // start: powers of 4
    for (long long p = 1; p <= UCAP; p *= 4) cur.push_back((int)p);
    auto cs = score(cur);
    auto best = cur; auto bs = cs;
    printf("start pow4: halves=%d t=%d\n", cs.first, cs.second); fflush(stdout);
    for (int it = 0; it < 260; it++) {
        vector<int> nxt = cur;
        int op = rng() % 3;
        if (op == 0 && nxt.size() > 2) nxt.erase(nxt.begin() + rng() % nxt.size());
        else if (op == 1 && nxt.size() < 14) {
            int v = 1 + rng() % UCAP;
            if (find(nxt.begin(), nxt.end(), v) == nxt.end()) nxt.push_back(v);
        } else {
            int i = rng() % nxt.size();
            int delta = (int)(rng() % 41) - 20;
            long long v = (long long)nxt[i] + delta;
            if (v < 1 || v > UCAP) continue;
            if (find(nxt.begin(), nxt.end(), (int)v) != nxt.end()) continue;
            nxt[i] = (int)v;
        }
        sort(nxt.begin(), nxt.end());
        auto ns = score(nxt);
        if (ns.first >= cs.first) { cur = nxt; cs = ns; }
        if (ns.first > bs.first) {
            bs = ns; best = nxt;
            printf("it=%3d  HALVES=%d  t=%d  n=%d  lengths:", it, bs.first, bs.second, (int)best.size());
            for (int c : best) printf(" %d", 2*c);
            printf("\n"); fflush(stdout);
        }
    }
    printf("\nBEST halves=%d t=%d\nlengths:", bs.first, bs.second);
    for (int c : best) printf(" %d", 2*c);
    printf("\n");
}
