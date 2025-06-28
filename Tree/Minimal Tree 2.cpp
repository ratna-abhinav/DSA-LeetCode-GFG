/*

  Given a unrooted tree of n nodes. You are also given a list of special nodes. Find the minimum time
  required to start and end at any node while visiting all the special nodes in any order.

*/


#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<bool> isSpec, inSteiner;
vector<int> parent;

// 1) DFS to mark which nodes/edges are in the minimal Steiner subtree
//    returns true if u’s subtree contains any special node
bool dfs_mark(int u, int p)
{
  bool has = isSpec[u];
  for (int v : adj[u])
    if (v != p)
    {
      if (dfs_mark(v, u))
      {
        has = true;
        // mark edge u-v as part of minimal steiner tree
        inSteiner[u] = inSteiner[v] = true;
      }
    }
  return has;
}

// 2) BFS to find farthest special node & distances (only walking steiner edges)
pair<int, int> bfs_far(int src)
{
  queue<int> q;
  vector<int> dist(n + 1, -1);
  dist[src] = 0;
  q.push(src);
  int best_node = src, best_d = 0;
  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    for (int v : adj[u])
    {
      if (dist[v] == -1 && inSteiner[v])
      {
        dist[v] = dist[u] + 1;
        q.push(v);
        if (isSpec[v] && dist[v] > best_d)
        {
          best_d = dist[v];
          best_node = v;
        }
      }
    }
  }
  return {best_node, best_d};
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  adj.assign(n + 1, {});
  isSpec.assign(n + 1, false);
  inSteiner.assign(n + 1, false);

  for (int i = 0, u, v; i < n - 1; i++)
  {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 0, x; i < m; i++)
  {
    cin >> x;
    isSpec[x] = true;
  }

  // pick any special node as “root” for pruning
  int anySpec = find(isSpec.begin() + 1, isSpec.end(), true) - isSpec.begin();
  dfs_mark(anySpec, 0);

  // count pruned‐subtree edges: each marked node except the start
  // contributes one used edge when it was discovered
  int E = 0;
  for (int u = 1; u <= n; u++)
  {
    for (int v : adj[u])
    {
      if (u < v && inSteiner[u] && inSteiner[v]) E++;
    }
  }

  // compute diameter among special nodes
  auto [u, _d1] = bfs_far(anySpec);
  auto [v, D] = bfs_far(u);

  // minimal tour = 2*E - D
  cout << (2 * E - D) << "\n";
  return 0;
}
