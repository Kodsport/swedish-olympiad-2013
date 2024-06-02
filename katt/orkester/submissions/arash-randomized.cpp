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
#define MAX(l, r) l = max((l),(r))
#define MIN(l, r) l = min((l),(r))

template <class T> string toString(T n){ostringstream oss;oss<<n;oss.flush();return oss.str();}
template <class T> string vectorToString(vector < T > v, string seperator = " "){
  ostringstream oss;
  tr(v, e) {
    oss << *e << seperator;
  }
  oss.flush();
  return oss.str();
}
template <class T1, class T2> std::ostream& operator << ( std::ostream& out,
                        const std::pair< T1, T2 >& rhs )
{
    out << "(" << rhs.first << ", " << rhs.second << ")";
    return out;
}

template <class T> std::ostream& operator << ( std::ostream& out,
                        const vector< T >& rhs )
{
    tr(rhs, it){
      out << *it << " ";
    }
    return out;
}

template <class T> std::istream& operator >> ( std::istream& in,
                        vector< T >& rhs )
{
    
    if(false /* sz(rhs) == 0 */){
      // Do getline and assume that's our elements
      string s;
      getline(in, s);
      if(s == "\n" || s == "") getline(in, s);
      stringstream sin(s);
      T temp;
      while(sin >> temp) rhs.push_back(temp); 
    } else {
      // read fixed number of elements
      tr(rhs, it) in >> *it;
    }
    return in;
}

template <class InIt> string rangeToString(InIt begin, InIt end, string seperator = " "){
  ostringstream oss;
  for(InIt it = begin; it != end; it++)
    oss << *it << seperator;
  oss.flush();
  return oss.str();
}

int main(){
  srand(0); // Make program deterministic

  // First, read input and organize data into arrays
  mr2(int, n, m);
  VVI player_gives_tracks(n); // list of track for each player
  VVI track_gives_players(m); // list of players for each track
  foru(i, n) {
    mr(int, t);
    foru(__unused, t){
      mr(int, j); j--;
      player_gives_tracks[i].push_back(j);
      track_gives_players[j].push_back(i);
    }
  }

  // Additional preprocessing
  VVVI common_tracks(n, VVI(n));
  VII has_commons_pairs;
  foru(i1, n){
    tr(player_gives_tracks[i1], it){
      int j = *it;
      tr(track_gives_players[j], it2){
        int i2 = *it2;
        common_tracks[i1][i2].push_back(j);
        has_commons_pairs.push_back(II(i1,i2));
      }
    }
  }

  // Initially, set a starting player for each track randomly
#define randomV(v) (v)[(rand()%sz(v))]
#define set_track(i, j) ({if(assigned[j]>=0){count_tracks[assigned[j]]--;}; assigned[j]=i;count_tracks[i]++;})
  VI count_tracks(n);
  VI assigned(m, -1); // who's assigned the track currently (-1 == none)
  foru(j, m){
    if(sz(track_gives_players[j]) == 0) continue;
    int i = randomV(track_gives_players[j]);
    set_track(i, j);
  }
  
  // Iteratively refine the solution
  LL iterations=1000000;
  while(iterations-->0){
    II ii = randomV(has_commons_pairs); // We put weight on "heavy traffic" pairs of musicians
    int i1 = ii.first, i2 = ii.second;
    if(count_tracks[i1] > count_tracks[i2]) swap(i1, i2);
    VI &ct = common_tracks[i1][i2];
    random_shuffle(all(ct));
    tr(ct, it){
      if(count_tracks[i1] >= count_tracks[i2]) break;
      int j = *it;
      if(assigned[j] == i2){
        set_track(i1, j);
      }
    }
  }

  double ans=0.0;
  tr(count_tracks, it){
    foru(i, *it) {
      ans+=1.0/(i+1.0);
    }
  }

  cout << setprecision(16) << ans << endl;
}

