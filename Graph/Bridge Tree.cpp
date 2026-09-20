#include <bits/stdc++.h>
using namespace std;

class BridgeTree
{
public:
  int n, m;

  vector<vector<pair<int, int>>> g;
  vector<pair<int, int>> edges;

  vector<int> tin, low, isBridge;
  int timer;

  vector<int> par, sz;

  vector<vector<int>> tree;
  vector<int> comp;

  BridgeTree(int n, int m)
  {
    this->n = n;
    this->m = m;

    g.assign(n, {});
    edges.resize(m);

    tin.assign(n, -1);
    low.assign(n, 0);
    isBridge.assign(m, 0);
    par.resize(n);
    sz.assign(n, 1);
    timer = 0;
    for (int i=0; i<n; i++) par[i] = i;
  }

  void addEdge(int id, int u, int v)
  {
    edges[id] = {u, v};
    g[u].push_back({v, id});
    g[v].push_back({u, id});
  }

  void dfsBridge(int u, int pe)
  {
    tin[u] = low[u] = timer++;
    for (auto [v, id] : g[u])
    {
      if (id == pe) continue;
      if (tin[v] != -1) low[u] = min(low[u], tin[v]);
      else
      {
        dfsBridge(v, id);
        low[u] = min(low[u], low[v]);
        if (low[v] > tin[u]) isBridge[id] = 1;
      }
    }
  }

  void findBridges()
  {
    for (int i=0; i<n; i++)
    {
      if (tin[i]==-1) dfsBridge(i, -1);
    }
  }

  int find(int x)
  {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
  }

  void unite(int a, int b)
  {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
  }

  void build()
  {
    for (int i=0; i<m; i++)
    {
      if (!isBridge[i])
      {
        auto [u, v] = edges[i];
        unite(u, v);
      }
    }

    comp.assign(n, -1);
    vector<int> rootToComp(n, -1);
    int k = 0;

    for (int i=0; i<n; i++)
    {
      int root = find(i);
      if (rootToComp[root] == -1) rootToComp[root] = k++;
      comp[i] = rootToComp[root];
    }

    tree.assign(k, {});
    for (int i=0; i<m; i++)
    {
      if (isBridge[i])
      {
        auto [u, v] = edges[i];
        int a = comp[u], b = comp[v];
        tree[a].push_back(b);
        tree[b].push_back(a);
      }
    }
  }

  void construct()
  {
    findBridges();
    build();
  }
};

/*
  Graph nodes are assumed to be 0-indexed for this template
*/ 

int main() 
{
  int n, m; cin >> n >> m;

  BridgeTree bt(n, m);

  for (int i = 0; i < m; i++) 
  {
    int u, v; cin >> u >> v;
    bt.addEdge(i, u, v);
  }

  // construct the bridge tree
  bt.construct();

  // which bridge tree node does original graph node u (~0) belong to
  cout << bt.comp[0] << '\n';

  int nodes_in_bridge_tree = bt.tree.size();
  for (int i=0; i<nodes_in_bridge_tree; i++) 
  {
      for (int v:bt.tree[i]) cout << i << " -> " << v << '\n';
  }
}