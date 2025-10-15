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

map<int, pair<double, double>> winningProb(vector<pair<int,double>>& strengths)
{
    if (strengths.size() == 1)
    {
        return { {strengths[0].first, {1, strengths[0].second}}};
    }

    std::size_t const half_size = strengths.size() / 2;
    vector<pair<int, double>> split_lo(strengths.begin(), strengths.begin() + half_size);
    vector<pair<int, double>> split_hi(strengths.begin() + half_size, strengths.end());

    map<int, pair<double, double>> bottom = winningProb(split_lo);
    map<int, pair<double, double>> top = winningProb(split_hi);

    map<int, pair<double, double>> ret;
    repe(i, bottom)
    {
        repe(j, top)
        {
            if (!ret.count(i.first))
            {
                ret[i.first] = { 0, i.second.second };
            }
            if (!ret.count(j.first))
            {
                ret[j.first] = { 0, j.second.second };
            }
            ret[i.first].first += 1 / (1 + exp(j.second.second - i.second.second)) * i.second.first*j.second.first;
            ret[j.first].first += 1 / (1 + exp(i.second.second - j.second.second)) * j.second.first*i.second.first;
        }
    }

    return ret;
}

int main()
{
    int n;
    cin >> n;
    vector<pair<int, double>> strengths(pow(2,n));
    rep(i, pow(2, n))
    {
        double strength;
        cin >> strength;
        strengths[i] = { i,strength };
    }

    map<int, pair<double, double>> winner = winningProb(strengths);
    
    int bestPlayer = -1;
    double bestProb = -1;
    repe(player, winner)
    {
        if (player.second.first > bestProb)
        {
            bestProb = player.second.first;
            bestPlayer = player.first + 1;
        }
    }

    cout << bestPlayer << " " << fixed << setprecision(20) << bestProb << endl;

    return 0;
}
