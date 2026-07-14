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
    auto start = std::chrono::high_resolution_clock::now();

    int n, m;
    cin >> n >> m;

    pair<double,double> avg = { 0,0 };
    vector<p2> friends(n);
    for (auto& [x,y] : friends) {
        cin >> x >> y;
        avg.first += x;
        avg.second += y;
    }
    avg.first /= n;
    avg.second /= n;

    vector<pair<double, p2>> houses;
    rep(i, m) {
        double x, y;
        cin >> x >> y;

        houses.push_back({ sqrt(pow(x - avg.first,2) + pow(y - avg.second,2)), {x,y} });
    }
    sort(all(houses));

    ll ans = 1e12;
    rep(i, m) {
        p2 ansHouse = { houses[i].second.first, houses[i].second.second };

        ll s = 0;
        repe(house, friends) {
            s += abs(ansHouse.first - house.first) + abs(ansHouse.second - house.second);
        }
        ans = min(ans, s);

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        if (elapsed >= 850.0) break;
    }
    
    cout << ans << '\n';

    return 0;
}
