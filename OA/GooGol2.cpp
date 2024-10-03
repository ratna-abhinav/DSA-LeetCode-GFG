#include <bits/stdc++.h>
#define int long long
using namespace std;

/*

  Given array A of N integers A1, A2, A3 ..... AN. You are also given two integers S and M. 
  You can perform at most M operations and in each operation, you can pick a subset of indexes of size S, 
  and increment the value of each element by 1. Apply the operations in an optimal way such that the minimum 
  value in array A is the maximum. Print the maximum value of the minimum value in array A possible.

  I/P:

  3
  5 2 5
  1 2 3 4 5
  5 1 5
  1 2 3 4 5
  5 2 0
  2 4 5 3 1

  O/P:

  5
  3
  1
  
*/

int n, s, m;
int a[100001];

bool check(int minval)
{
  int ops_req = 0;
  for (int i = 0; i < n; i++)
  {
    ops_req += max(0ll, minval - a[i]);
    if (max(0ll, minval - a[i]) > m) return false;
  }
  return ops_req <= m * s;
}

void solve()
{
  cin >> n >> s >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  int lo = 0, hi = 1e18, ans = lo;

  while (lo <= hi)
  {
    int mid = (lo + hi) / 2;
    if (check(mid)) lo = mid+1;
    else hi = mid - 1;
  }
  cout << lo-1 << "\n";
}

signed main()
{
  int t; cin >> t;
  while (t--) solve();
}