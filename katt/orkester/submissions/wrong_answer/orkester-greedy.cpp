#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, M;
vector<vector<int> > reach;
double solve() {
  double res = 0;
  vector<vector<int> > r;
  for (int i = 0; i < N; ++i) {
    random_shuffle(reach[i].begin(), reach[i].end());
    r.push_back(reach[i]);
  }
  random_shuffle(r.begin(), r.end());
  vector<int> used(N, 0);
  vector<bool> taken(M, false);
  bool some;
  do {
    some = false;
    for (int i = 0; i < N; ++i) {
      if (r[i].empty())
        continue;
      some = true;
      int wh = r[i].back();
      r[i].erase(r[i].end()-1);
      if (taken[wh])
        continue;
      taken[wh] = true;
      res += 1./++used[i];
    }
  }
  while(some);
  return res;
}

int main() {
  cin >> N >> M;
  reach.resize(N);
  for (int i = 0; i < N; ++i) {
    int t, a;
    cin >> t;
    for (int j = 0; j < t; ++j) {
      cin >> a;
      --a;
      reach[i].push_back(a);
    }
  }
  double best = 0;
  int iterations = 10000000 / N / M;
  for (int it = 0; it < iterations; ++it) {
    double s = solve();
    if (s > best) best = s;
  }
  cout << best << endl;
  return 0;
}
