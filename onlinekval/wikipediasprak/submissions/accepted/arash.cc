//Arash Rouhani
//#define _GLIBCXX_DEBUG
#define NDEBUG
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <math.h>
#include <fstream>
#include <numeric>
#include <set>
#include <queue>
#include <stack>
#include <map>
#include <bitset>
#include <assert.h>

using namespace std;

typedef long long LL;
typedef pair < int, int > II;
typedef pair < int, II > I_II;
typedef vector < int > VI;
typedef vector < II > VII;
typedef vector < VI > VVI;
typedef vector < VII > VVII;
typedef vector < VVI > VVVI;
typedef vector < string > VS;
typedef vector < VS > VVS;
typedef vector < char > VC;
typedef vector < VC > VVC;
typedef stringstream SS;
typedef set < int > SI;
typedef set < SI > SSI;
typedef vector < SI > VSI;

#define sz(c) (int((c).size()))
#define all(c) (c).begin(), (c).end()
#define tr(c, it) for(typeof((c).begin()) it = (c).begin(); it!=(c).end(); it++)
#define sfor(type, e, start, stop) for(type e=start; e<stop; e++)
#define foru(var, stop) sfor(int, var, 0, stop)
#define sford(type, e, start, stop) for(type e=start; e>=stop; e--)
#define ford(var, start) sford(int, var, start, 0)
#define mp make_pair
#define error(msg) {cout << msg << endl; throw;}
#define mr(type, v1) \
  type v1; \
  cin >> v1;
#define mr2(type, v1, v2) \
  type v1, v2; \
  cin >> v1 >> v2;
#define mr3(type, v1, v2, v3) \
  type v1, v2, v3; \
  cin >> v1 >> v2 >> v3;
#define mr4(type, v1, v2, v3, v4) \
  type v1, v2, v3, v4; \
  cin >> v1 >> v2 >> v3 >> v4;
#define mr5(type, v1, v2, v3, v4, v5) \
  type v1, v2, v3, v4, v5; \
  cin >> v1 >> v2 >> v3 >> v4 >> v5;

template <class T> string toString(T n){ostringstream oss;oss<<n;oss.flush();return oss.str();}
template <class T> string vectorToString(vector < T > v, string seperator = " "){
  ostringstream oss;
  tr(v, e)
  oss << *e << seperator;
  oss.flush();
  return oss.str();
}
template <class T1, class T2> std::ostream& operator << ( std::ostream& out,
                        const std::pair< T1, T2 >& rhs )
{
    out << "(" << rhs.first << ", " << rhs.second << ")";
    return out;
}

template <class InIt> string rangeToString(InIt begin, InIt end, string seperator = " "){
  ostringstream oss;
  for(InIt it = begin; it != end; it++)
    oss << *it << seperator;
  oss.flush();
  return oss.str();
}

// End of template

VVI graph;
VI dp;

int go(int i){
  int &v = dp[i];
  if(v == -1) {
    v = 1;
    tr(graph[i], it) {
      v = max(v, 1+go(*it));
    }
  }
  return v;
}

VI ordlista;

void solve(int i){
  ordlista.push_back(i);
  int curr_val = go(i);
  if(curr_val == 1) {
    // base case
  }
  else{
    // we definetly have reverse children
    VI cands;
    tr(graph[i], it) {
      if(go(*it) == curr_val-1) {
        cands.push_back(*it);
      }
    }
    if(sz(cands) != 1){
      error("ej unik losning ");
    }
    solve(cands.front());
  }
}

int main(){
  mr2(int, n, l);
  graph.resize(n);
  dp.resize(n, -1);
  foru(i, l){
    mr2(int, t, old);
    foru(j, t-1) { mr(int, neww); graph[old].push_back(neww); old = neww; }
  }

  foru(i, n) {go(i);} // fyll dp
  int best = max_element(dp.begin(), dp.end())-dp.begin();
  int best_rev = -(max_element(dp.rbegin(), dp.rend())-dp.rend())-1 ;
  if(best != best_rev) {
    error("Losning ej unik " + toString(best) + " " + toString(best_rev) );
  }

  solve(best);
  cout << ordlista.size() << endl << vectorToString(ordlista) << endl;
}

