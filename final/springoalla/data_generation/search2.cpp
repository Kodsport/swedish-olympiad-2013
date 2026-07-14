#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int HMAX, XMAX;
vector<vector<int>> dp, nxt;
void build(const vector<int>& u, int tmax) {
    int umax = *max_element(u.begin(), u.end());
    XMAX = tmax + 3*umax + 5;
    dp.assign(HMAX+1, vector<int>(XMAX, INF));
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
    nxt.assign(HMAX+1, vector<int>(XMAX+1, XMAX));
    for (int h = 0; h <= HMAX; h++)
        for (int x = XMAX-1; x >= 0; x--) nxt[h][x] = (dp[h][x] < INF) ? x : nxt[h][x+1];
}
int main(int argc, char** argv) {
    int maxt = atoi(argv[1]); HMAX = atoi(argv[2]);
    int gb = -1; string gd;
    for (int q = 16; q <= 44; q += 1)
      for (int n = q/2; n <= 55; n += 1) {
        long long umax = 1 + (long long)(n-1)*q;
        if (2*umax > 40000) break;
        vector<int> u; for (int j = 0; j < n; j++) u.push_back(1 + j*q);
        build(u, maxt);
        int bh = -1, bt = 0, bts = 0, brs = 0;
        for (int t = 1; t <= maxt; t++) {
            int ts = nxt[HMAX][t]; if (ts >= XMAX) continue;
            int rs = dp[HMAX][ts];
            for (int h = 0; h <= HMAX; h++)
                if (nxt[h][t] == ts && dp[h][ts] == rs) { if (h > bh) { bh=h; bt=t; bts=ts; brs=rs; } break; }
        }
        if (bh > gb) {
            gb = bh;
            char buf[256];
            snprintf(buf,sizeof buf,"q=%d n=%d umax=%lld  t=%d -> t_s=%d n_s=%d  REQUIRED HALVES=%d",q,n,umax,bt,bts,brs,bh);
            gd = buf; printf("%s\n", buf); fflush(stdout);
        }
      }
    printf("\nBEST: %s\n", gd.c_str());
}
