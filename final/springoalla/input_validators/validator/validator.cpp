#include "validator.h"

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(it,x) for(auto& it : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
template<typename A, typename B> auto smin(A& a, const B& b) { if (b < a) a = b;}

int N, T;
vi is;

pii solve(bool onlywhole) {
    vector<pii> I;
    rep(i,0,N) {
        int l = is[i];
        I.emplace_back(l, 1);
        if (onlywhole) I.emplace_back(l, 1);
        else I.emplace_back(l + l / 2, 2);
    }
    vi least(T + 40'000, 1e9);
    least[0] = 0;
    rep(i,1,sz(least)) {
        trav(it, I) {
            if (i - it.first >= 0)
                smin(least[i], least[i - it.first] + it.second);
        }
    }
    rep(t,T,sz(least)) {
        if (least[t] < 1e6) {
            return pii(t, least[t]);
        }
    }
    assert(false);
}

void run() {
    N = Int(1, Arg("maxn")); Space();
    T = Int(1, Arg("maxt")); Endl();
    is = SpacedInts(N, 1, 40'000);
    Eof();

    bool onlywhole = Arg("onlywhole");
    if (onlywhole) {
        assert(solve(true) == solve(false));
    }
}
