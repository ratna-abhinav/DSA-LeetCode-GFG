                                          /*    JAI SHRI RAM    */
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,a,b) for(int i=a; i<b; i++)
#define vi vector<int>
#define vvi vector<vi>
#define pi pair<int,int>
#define len(v) (int)(v.size())
#define all(v) v.begin(), v.end()
#define nl '\n'

/*
  
  Given an array of size N. In one operation, you can merge adjacent elements. You need to make the final array
  a palindrome. Find the max length of final palindromic array.

*/

void solve()
{
  int n; cin >> n; vi arr(n), vis(n,0), ans;
  rep(i,0,n) cin >> arr[i];
  int i = 0, j = n-1;
  while (i<=j)
  {
    if (arr[i] == arr[j]) i++, j--;
    else if (arr[i] < arr[j])
    {
      // merge arr[i] with arr[i+1]
      arr[i+1] += arr[i];
      vis[i] = 1;
      i++;
    }
    else
    {
      arr[j-1] += arr[j];
      vis[j] = 1;
      j--;
    }
  }
  rep(i,0,n)
  {
    if (!vis[i]) ans.push_back(arr[i]);
  }
  for (auto e:ans) cout << e << ' ';
}

signed main()
{
  // int t; cin >> t; while (t--)
  solve();
}
