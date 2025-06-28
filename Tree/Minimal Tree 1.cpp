/*

  Given a rooted tree (at node 1) of n nodes. You are also given a list of special nodes. Find the minimum time
  required to start and end at node 1 while visiting all the special nodes in any order.

*/



#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
vector<vector<int>> adj;
vector<bool> isSpecial;
ll edgeCount = 0;


bool dfs(int u, int p)
{
  bool has = isSpecial[u];
  for (int v : adj[u])
    if (v != p)
    {
      if (dfs(v, u))
      {
        has = true;
        edgeCount++;
      }
    }
  return has;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int m;
  cin >> n >> m;
  adj.assign(n + 1, {});
  isSpecial.assign(n + 1, false);

  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for (int i = 0; i < m; i++)
  {
    int x;
    cin >> x;
    isSpecial[x] = true;
  }

  dfs(1, 0);

  cout << 2 * edgeCount << "\n";
  return 0;
}
