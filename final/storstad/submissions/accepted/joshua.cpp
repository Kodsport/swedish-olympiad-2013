#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vi xcoords(n), ycoords(n);

    rep(i, n) {
        cin >> xcoords[i];
        cin >> ycoords[i];
    }

    sort(all(xcoords));
    sort(all(ycoords));

    vector<p2> x(n), y(n);

    x[0].first = xcoords[0];
    x[n-1].second = xcoords[n-1];
    y[0].first = ycoords[0];
    y[n-1].second = ycoords[n-1];

    repp(i, 1, n) x[i].first += x[i - 1].first + xcoords[i];
    for (int i = n-2; i >= 0; i--) x[i].second += x[i + 1].second + xcoords[i];
    
    repp(i, 1, n) y[i].first += y[i - 1].first + ycoords[i];
    for (int i = n-2; i >= 0; i--) y[i].second += y[i + 1].second + ycoords[i];

    ll ans = inf;
    rep(i, m) {
        ll d = 0;

        ll mx, my;
        cin >> mx >> my;

        auto xit = lower_bound(all(xcoords), mx);

        ll idx = xit - xcoords.begin();
        if (mx>xcoords[0]) {
            d += mx * (idx) - x[idx-1].first;
        }
        if (mx<xcoords[n-1]) {
            d+= x[idx].second - mx * (xcoords.size() - idx);
        }

        auto yit = lower_bound(all(ycoords), my);

        ll idy = yit - ycoords.begin();
        if (my>ycoords[0]) {
            d += my * (idy) - y[idy-1].first;
        }
        if (my<ycoords[n-1]) {
            d+= y[idy].second - my * (ycoords.size() - idy);
        }

        ans = min(ans, d);
    }

    cout << ans << '\n';
    return 0;
}
