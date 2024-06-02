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
typedef vector < int > VI;
typedef vector < VI > VVI;
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

struct Collector {
  LL left;
  Collector(int left):left(left){};
};

// haha kunde inte motstå testa detta :)
template < class T > struct LRU {
  int cap;
  vector<T> xs;
  LRU(int cap):cap(cap){}
  void insert(T elem){
    if(cap > sz(xs)){
      xs.push_back(elem);
    } else {
      xs.front() = elem;
    }
  }
  void sayIUsed(int i){
    if(i < 10){
      T elem = xs[i];
      xs.erase(xs.begin()+i);
      xs.push_back(elem);
    }
  }
};

typedef pair < LL, int > II;

int main(){
  mr2(int, n, k);
  vector<LL> a(n); cin >> a;

  vector<Collector> cs;

  const int B = 100;
  LRU<II> bonuses(B);
  LL largest = -100;
  tr(a, it){
    LL v = *it;
    int i = 0;
    tr(bonuses.xs, bit){
      II b = *bit;
      int j = -1;
      if(v >= b.first && i < b.second) {
        i = b.second;
        j = bit - bonuses.xs.begin();
      }
      if(j>=0) bonuses.sayIUsed(j);
    }
    if(v > largest) i = sz(cs);
    /* cerr << i << " "; */
    while(true){
      if(i >= sz(cs)){
        cs.push_back(Collector(k));
      }
      else if (cs[i].left >= v) {
        cs[i].left -= v; cout << i << (it+1 != a.end() ? " " :"");
        largest = max(cs[i].left, largest);
        bonuses.insert(II(v, i));
        break;
      }
      else {
        i++;
      }
    }
  }

  cout << endl;
}

