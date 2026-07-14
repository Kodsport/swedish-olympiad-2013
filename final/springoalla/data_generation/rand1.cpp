// Random search over coin sets for the subtask-1 box: n<=10, t<=1000.
#include <bits/stdc++.h>
using namespace std;
const int INF=1e9;
int HMAX=12, XMAX;
vector<vector<int>> dp,nxt;
void build(const vector<int>& u,int tmax){
    int umax=*max_element(u.begin(),u.end());
    XMAX=tmax+3*umax+5;
    dp.assign(HMAX+1,vector<int>(XMAX,INF));
    for(int h=0;h<=HMAX;h++) dp[h][0]=0;
    for(int x=1;x<XMAX;x++) for(int h=0;h<=HMAX;h++){
        int b=INF;
        for(int c:u){ if(x>=2*c) b=min(b,dp[h][x-2*c]+1); if(h>0&&x>=3*c) b=min(b,dp[h-1][x-3*c]+2); }
        dp[h][x]=b;
    }
    nxt.assign(HMAX+1,vector<int>(XMAX+1,XMAX));
    for(int h=0;h<=HMAX;h++) for(int x=XMAX-1;x>=0;x--) nxt[h][x]=(dp[h][x]<INF)?x:nxt[h][x+1];
}
int main(){
    mt19937 rng(12345);
    int best=-1;
    for(int iter=0;iter<4000;iter++){
        int n=2+rng()%9;                 // 2..10 trails
        int umax=8+rng()%60;             // u_max up to ~67
        set<int> S; S.insert(umax);
        while((int)S.size()<(size_t)n) S.insert(1+rng()%umax);
        vector<int> u(S.begin(),S.end());
        build(u,1000);
        for(int t=1;t<=1000;t++){
            int ts=nxt[HMAX][t]; if(ts>=XMAX) continue;
            int rs=dp[HMAX][ts];
            for(int h=0;h<=HMAX;h++) if(nxt[h][t]==ts&&dp[h][ts]==rs){
                if(h>best){ best=h;
                    printf("REQUIRED HALVES=%d  n=%d t=%d -> t_s=%d n_s=%d  lengths:",h,(int)u.size(),t,ts,rs);
                    for(int c:u) printf(" %d",2*c);
                    printf("\n"); fflush(stdout);
                }
                break;
            }
        }
    }
}
