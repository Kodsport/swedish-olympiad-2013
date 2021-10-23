#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(it,x) for(auto& it : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream& os, const vector<T> &v) { rep(i,0,sz(v)) { if (i) os << " " << v[i]; else os << v[i]; } os << endl; return os; }
template<typename T> istream& operator>>(istream& is, vector<T> &v) { trav(it, v) is >> it; return is; }
template<typename T> using v = vector<T>; template<typename T> using vv = v<v<T>>; template<typename T> using vvv = v<v<v<T>>>;
template<typename T> std::vector<T> make(T init, std::size_t size) { return std::vector<T>(size, init); }
template<typename T, typename... Args> auto make(T init, std::size_t first, Args... sizes) { auto inner = make<T>(init, sizes...); return std::vector<decltype(inner)>(first, inner); }
template<typename A, typename B> auto smax(A& a, const B& b) { if (b > a) a = b; }
template<typename A, typename B> auto smin(A& a, const B& b) { if (b < a) a = b;}
bool within(int r, int c, int R, int C) { return 0 <= r && r < R && 0 <= c && c < C; }

void solve() {
    int N, OT;
    cin >> N >> OT;
    vector<int> I;
    rep(i,0,N) {
        int l;
        cin >> l;
        I.emplace_back(l);
    }
    pair<pii, vi> R(pii(1e9, 1e9), vi());
    rep(msk,0,1<<N) {
        int T = OT;
        vi res(N);
        rep(i,0,N) {
            if (msk & (1 << i)) {
                T -= 3 * I[i] / 2;
                res[i] += 3 * I[i] / 2;
            }
        }
        if (T < 0) continue;

        vi least(T + 1'000, 1e9);
        least[0] = 0;
        rep(i,1,sz(least)) {
            trav(it, I) {
                if (i - it >= 0)
                    smin(least[i], least[i - it] + 1);
            }
        }
        rep(t,T,sz(least)) {
            if (least[t] < 1e6) {
                int ts = t + OT - T;
                int ns = least[t] + 2 * __builtin_popcount(msk);
                while (t) {
                    rep(i,0,2*N) {
                        if (I[i] <= t && least[t] == least[t - I[i]] + 1) {
                            res[i] += I[i];
                            t -= I[i];
                            break;
                        }
                    }
                }
                smin(R, make_pair(pii(ts, ns), res));
                break;
            }
        }
    }
    cout << R.first.first << " " << R.first.second << endl;
    cout << R.second;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    
    int TC = 1;
    if (!TC) cin >> TC;
    rep(i,1,TC+1) {
        // cout << i << " ";
        solve();
    }
}
