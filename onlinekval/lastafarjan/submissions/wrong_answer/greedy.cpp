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

int sol(int L, vi A) {
    vi left(4, L + 1);
    rep(i,0,sz(A)) {
        int w = A[i];
        ++w;
        sort(all(left), greater<int>());
        if (left[0] < w) {
            return i;
        }
        left[0] -= w;
    }
    return sz(A);
}

int sol2(int L, vi A) {
    vi left(4, L + 1);
    rep(i,0,sz(A)) {
        int w = A[i];
        ++w;
        sort(all(left));
        rep(j,0,4) {
            if (left[j] >= w) {
                left[j] -= w;
                goto skip;
            }
        }
        return i;
skip:;
    }
    return sz(A);
}

void solve() {
    /*
The first line contains the integer $N$ ($N \le 200$), the number of cars.
The second line contains the integer $L$ ($L \le 60$), the length of the lanes.
This is followed by $N$ integers on a line, where each integer is the length of a car in the same order that they're queuing in.
Each car is between $1$ and $10$ meters long, and does not exceed the length of the ferry.
*/
    int N, L;
    cin >> N >> L;
    vi A(N);
    cin >> A;
    cout << max(sol(L, A), sol2(L, A)) << endl;
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
