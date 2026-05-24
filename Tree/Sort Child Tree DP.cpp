#include <bits/stdc++.h>
using namespace std;

/*
  There is a tree of N nodes and there are infinite type of tickets but every type of ticket
  has only 2 copies. You need to put exactly k tickets at every node. Any edge (u -- v) is considered to be covered if there is atleast common ticket among the tickets alloted to 
  node u and node v. Each edge has profit assigned to it. Maximize the total profit from covered edges.

  Constraints: N <= 1e5, k <= 1e5
*/

using ll = long long;

int n, k;
vector<vector<pair<int, ll>>> adj;
vector<array<ll, 2>> dp;

void dfs(int u, int p)
{
  ll base = 0;
  vector<ll> gain;

  for (auto [v, w] : adj[u])
  {
    if (v == p)
      continue;

    dfs(v, u);

    base += dp[v][0];
    ll g = w + dp[v][1] - dp[v][0];
    if (g > 0)
      gain.push_back(g);
  }

  sort(gain.rbegin(), gain.rend());

  dp[u][0] = base;
  dp[u][1] = base;

  int take0 = min(k, (int)gain.size());
  int take1 = min(k - 1, (int)gain.size());

  for (int i = 0; i < take0; i++)
    dp[u][0] += gain[i];
  for (int i = 0; i < take1; i++)
    dp[u][1] += gain[i];
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  adj.assign(n + 1, {});
  dp.assign(n + 1, {0, 0});

  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  dfs(1, 0);
  cout << dp[1][0] << '\n';
  return 0;
}