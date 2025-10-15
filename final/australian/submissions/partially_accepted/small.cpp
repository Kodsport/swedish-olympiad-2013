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

int main()
{
    int n;
    cin >> n;
    double a,b;
    cin >> a >> b;

    auto winp = [](double a, double b)
    {
        return 1.0/(1+exp(b-a));
    };
    double awin = winp(a,b);
    double bwin = winp(b,a);
    if (awin > bwin)
    {
        cout << fixed << setprecision(15) << 1 << " " << awin << endl;
    }
    else
    {
        cout << fixed << setprecision(15) << 2 << " " << bwin << endl;
    }

    return 0;
}
