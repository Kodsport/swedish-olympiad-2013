#include <bits/stdc++.h>
using namespace std;
const int INF=1e9; const int MAXT=100000, UCAP=20000;
pair<int,int> score(const vector<int>& u){
    int H=min((int)u.size(),40), X=MAXT+40001;
    vector<vector<int>> dp(H+1, vector<int>(X,INF));
    for(int h=0;h<=H;h++) dp[h][0]=0;
    for(int x=1;x<X;x++) for(int h=0;h<=H;h++){
        int b=INF;
        for(int c:u){ if(x>=2*c&&dp[h][x-2*c]+1<b) b=dp[h][x-2*c]+1;
                      if(h>0&&x>=3*c&&dp[h-1][x-3*c]+2<b) b=dp[h-1][x-3*c]+2; }
        dp[h][x]=b;
    }
    vector<vector<int>> nx(H+1, vector<int>(X+1,X));
    for(int h=0;h<=H;h++) for(int x=X-1;x>=0;x--) nx[h][x]=(dp[h][x]<INF)?x:nx[h][x+1];
    int best=-1,bt=0;
    for(int t=1;t<=MAXT;t++){
        int ts=nx[H][t]; if(ts>=X) continue;
        int rs=dp[H][ts];
        for(int h=0;h<=H;h++) if(nx[h][t]==ts&&dp[h][ts]==rs){ if(h>best){best=h;bt=t;} break; }
    }
    return {best,bt};
}
void run(vector<int> u, string tag){
    sort(u.begin(),u.end()); u.erase(unique(u.begin(),u.end()),u.end());
    if(u.empty()||u.back()>UCAP) return;
    auto s=score(u);
    printf("%-24s coins=%2d  HALVES=%d  t=%d\n  lengths:",tag.c_str(),(int)u.size(),s.first,s.second);
    for(int c:u) printf(" %d",2*c);
    printf("\n\n"); fflush(stdout);
}
int main(){
    for (int b : {3,4,5,6,7,8}) {
        vector<int> u; for(long long p=1;p<=UCAP;p*=b) u.push_back((int)p);
        run(u,"base "+to_string(b));
    }
    // 2-D smooth-number families: coins = a^i * b^j <= UCAP
    for (auto pr : vector<pair<int,int>>{{4,5},{4,3},{4,7},{5,6},{4,9},{5,7},{4,11},{3,5}}) {
        vector<int> u;
        for(long long p=1;p<=UCAP;p*=pr.first)
            for(long long v=p; v<=UCAP; v*=pr.second) u.push_back((int)v);
        run(u,"grid "+to_string(pr.first)+"^i*"+to_string(pr.second)+"^j");
    }
}
