                                  /*    JAI SHRI RAM    */
#include <bits/stdc++.h>
using namespace std;

#define int long long
int _t;
void solve();

void IO()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}

void testcase(int _t)
{
  cin >> _t;
  while (_t--) solve();
}

typedef long long ll;
typedef long double lld;

#define ff first
#define ss second
#define pi pair<int, int>
#define vi vector<int>
#define vs vector<string>
#define vc vector<char>
#define pv pair<vi, vi>
#define vpi vector<pi>
#define vvi vector<vi>
#define vvc vector<vc>
#define vvvi vector<vvi>
#define vvpi vector<vpi>
#define vvvpi vector<vvpi>
#define vvvvi vector<vvvi>
#define vvvvpi vector<vvvpi>
#define pb push_back
#define var(k) vector<array<int, k>>
#define all(v) v.begin(), v.end()
#define unq(v) v.erase(unique(all(v)), v.end());
#define len(v) (int)v.size()
#define rep(i,a,b) for(int i=a; i<b; i++)
#define pll pair<ll, ll>
#define vll vector<ll>
#define vpll vector<pll>
#define vvll vector<vll>
#define setbits(x) __builtin_popcountll(x)
#define nl '\n'


/*  ------------------------    BASIC INPUT -------------------------------  */

void read() {}
void read(int &a) {cin >> a;}
void read(string &s) {cin >> s;}
void read(double &a) {cin >> a;}
void read(lld &a) {cin >> a;}
template<typename x, typename y> void read(pair<x, y> &a) {read(a.first), read(a.second);}
template<typename x>void read(x &a) {for (auto  &i : a) read(i);}
template<typename x, typename... y> void read(x& a, y&... b) {read(a); read(b...);}
template<class T> void cmin(T&a, T b) {a = min(a, b);}
template<class T> void cmax(T&a, T b) {a = max(a, b);}

/*    ------------------------------------------------------------------   */


/*
  1. GRAPH ????
  2. If Math, then WLOG ????
  3. EDGE CASES -> like n = 1 etc.
  4. MULTIPLE EDGES, then maybe replace it by min()
  5. Take care of OVERFLOW, sometimes INF = 1e18, may cause
      overflow if it was added n times where n ~ 1e5
  6. If u are using __int128, then {cin, cout} doesn't work
      so typecast to LL before doing cout
  #. For Bug - Free Code, do Proper Simplification & Formulation
*/

int n, pairCost, k;
const int inf = 1e18, MOD = 1e9+7;

/*

  Given an array cost of size N. We need to find minimum cost required to remove all the elements
  from the array. We can remove elements by following the below strategy:

  - remove the leftmost element of the current array by paying cost[leftmost_index]
  - remove the rightmost element of the current array by paying cost[rightmost_index]
  - remove both leftmost and rightmost element of current array by paying "pairCost", but
    you can do this operation atmax K times

  Constraints: N <= 1e5, 0 <= K <= N

*/


int arr[100];

void solve()
{
  cin >> n >> pairCost >> k;
  int tot = 0;
  rep(i,0,n) 
  {
    cin >> arr[i];
    tot += arr[i];
  }
  sort(arr, arr+n);
  vi big;
  for(int i=n-1; i>=max(0ll,n-2*k); i--) big.push_back(arr[i]);
  rep(i,1,len(big)) big[i] += big[i-1];

  int ans = inf;
  rep(i,0,k+1)
  {
    int left = n-2*i;
    if (left<0) break;
    int cur = tot;
    if (i) 
    {
      cur -= big[2*i-1];
      cur += i*pairCost;
    }
    ans = min(ans, cur);
  }
  cout << ans;
}

signed main()
{
  IO();

  // testcase(_t);
  solve();
}