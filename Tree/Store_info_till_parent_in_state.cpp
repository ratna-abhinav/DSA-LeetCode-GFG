#include <bits/stdc++.h>
using namespace std;

/*
  Given a tree of N nodes. We can color each node of the tree with any of the M (~20) colors. Find the total no of
  colorings possible such that there is atleast one path from root (node 1) to any leaf with gcd != 1

  Answer = total_colorings - colorings_with_no_path_with_gcd_not_1
  Answer = m^n - colorings_with_all_paths_with_gcd_1
*/

#define rep(i,a,b) for(int i=a; i<b; i++)

using ll = long long;

int n, m;
vector<vector<int>> tree, dp;

const int mod = 1e9+7;
int add(int x, int y) { ll res = 0ll + x + y; return (res >= mod ? res - mod : res); }
int sub(int x, int y) { int res = x - y; return (res < 0 ? res + mod : res); }
int mul(int x, int y) { x %= mod, y %= mod; ll res = 1ll * x * y; return (res >= mod ? res % mod : res); }
int mod_pow(int x, int y) { if (y <= 0) return 1; int ans = 1; x %= mod; while (y) { if (y & 1) ans = mul(ans, x); x = mul(x, x); y >>= 1; } return ans; }

int dfs(int cur, int par, int g) 
{
  if (dp[cur][g] != -1) return dp[cur][g];

  if (tree[cur].size() == 1 && cur != 1) 
  {
    int ans = 0;
    for (int i = 1; i <= m; i++) 
    {
      int ng = __gcd(g, i);
      if (ng == 1) ans++;
    }
    return dp[cur][g] = ans;
  }

  int ans = 0;
  for (int i = 1; i <= m; i++) 
  {
    int val = 1;
    int ng = __gcd(g, i);
    for (auto nb : tree[cur]) 
    {
      if (nb == par) continue;
      val = mul(val, dfs(nb, cur, ng));
    }
    ans = add(ans, val);
  }
  
  return dp[cur][g] = ans;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m;
  tree.resize(n + 1);
  rep(i, 1, n) 
  {
    int u, v; cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  dp.assign(n + 1, vector<int>(m + 1, -1));
  
  int bad_colorings = dfs(1, 0, 0);
  int ans = sub(mod_pow(m, n), bad_colorings);
  cout << ans << "\n";    
}