#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<b; i++)

using ll = long long;

int n,m;
vector<vector<int>> tree,dp;

const int mod = 1e9+7;
int add(int x, int y) { ll res = 0ll + x + y; return (res >= mod ? res - mod : res); }
int sub(int x, int y) { int res = x - y; return (res < 0 ? res + mod : res); }
int mul(int x, int y) { x %= mod, y %= mod; ll res = 1ll * x * y; return (res >= mod ? res % mod : res); }
int mod_pow(int x, int y) { if (y <= 0) return 1; int ans = 1; x %= mod; while (y) { if (y & 1) ans = mul(ans, x); x = mul(x, x); y >>= 1; } return ans; }
int mod_inverse(int x) {return mod_pow(x, mod - 2);}


/*

  This solution will TLE due to we calling dfs(nb) for current node m times. But its 100% correct

*/

void dfs(int cur, int par, int g)
{
  if (tree[cur].size()==1 && cur!=1)
  {
    int ans = 0;
    for (int i=1; i<=m; i++)
    {
      int ng = __gcd(g,i);
      if (ng==1) ans++;
    }
    dp[cur][g] = ans;
    return;
  }

  for (int i=1; i<=m; i++)
  {
    for (auto nb:tree[cur])
    {
      if (nb==par) continue;
      dfs(nb, cur, __gcd(g,i));
    }
  }

  int ans = 0;
  for (int i=1; i<=m; i++)
  {
    int val = 1;
    for (auto nb:tree[cur])
    {
      if (nb==par) continue;
      int ng = __gcd(g,i);
      val = mul(val, dp[nb][ng]);
    }
    ans = add(ans, val);
  }
  dp[cur][g] = ans;
}

signed main()
{
  cin >> n >> m;
  tree.resize(n+1);
  rep(i,1,n) 
  {
    int u,v; cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  dp.assign(n+1, vector<int>(m+1,0));
  dfs(1,0,0);
  int ans = sub(mod_pow(m,n), dp[1][0]);
  cout << ans;
}