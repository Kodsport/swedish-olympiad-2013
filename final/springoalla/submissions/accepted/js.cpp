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
    int N, T;
    cin >> N >> T;
    vector<pii> I;
    rep(i,0,N) {
        int l;
        cin >> l;
        I.emplace_back(l, 1);
        I.emplace_back(l + l / 2, 2);
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
            cout << t << " " << least[t] << endl;
            vi res(N);
            while (t) {
                rep(i,0,2*N) {
                    if (I[i].first <= t && least[t] == least[t - I[i].first] + I[i].second) {
                        res[i / 2] += I[i].first;
                        t -= I[i].first;
                        break;
                    }
                }
            }
            cout << res;
            break;
        }
    }
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
