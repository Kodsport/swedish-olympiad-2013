#include "validator.h"

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(it,x) for(auto& it : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
template<typename A, typename B> auto smin(A& a, const B& b) { if (b < a) a = b;}

void run() {
    int N = Int(1, Arg("maxn")); Endl();
    int L = Int(1, Arg("maxl")); Endl();
    SpacedInts(N, 1, min(L, 10));
    Eof();
}
