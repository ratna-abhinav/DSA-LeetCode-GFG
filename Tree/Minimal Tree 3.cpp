/*

  Given a unrooted tree of n nodes. You are also given a list of special nodes. Find the minimum time
  required to start and end at same node while visiting all the special nodes in any order.

*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<bool> isSpecial;
long long edgeCount = 0;

// returns true if subtree of u (w.r.t. parent p) contains any special node
bool dfs(int u, int p)
{
  bool has = isSpecial[u];
  for (int v : adj[u])
    if (v != p)
    {
      if (dfs(v, u))
      {
        has = true;
        edgeCount++; // we need edge u–v in the Steiner subtree
      }
    }
  return has;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  adj.assign(n + 1, {});
  isSpecial.assign(n + 1, false);

  for (int i = 0, u, v; i < n - 1; i++)
  {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 0, x; i < m; i++)
  {
    cin >> x;
    isSpecial[x] = true;
  }

  // if there are no specials, you need not move at all:
  if (m == 0)
  {
    cout << 0 << "\n";
    return 0;
  }

  // start DFS from any special node:
  int anySpec = find(isSpecial.begin() + 1, isSpecial.end(), true) - isSpecial.begin();
  dfs(anySpec, 0);

  // each needed edge must be walked twice in a closed tour
  cout << (2 * edgeCount) << "\n";
  return 0;
}