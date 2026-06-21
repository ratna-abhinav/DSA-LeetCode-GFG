#include <bits/stdc++.h>
using namespace std;

/*

Given a tree with n nodes rooted at node 1. You have to perform q operations of the following types:
1 v c: Insert color c into the subtree of node v.
2 v: Find the number of distinct colors in the subtree of node v.


This is the exact approach you described:
- Euler tour converts subtree(v) into [tin[v], tout[v]]
- For each color, maintain a segment tree on Euler positions
- Update: range add +1 on [tin[v], tout[v]] for that color
- Query: for every color, check whether max on [tin[v], tout[v]] > 0

This is correct for the "insert color into subtree" operation.
Time:
- update: O(log n)
- query: O(K log n), where K = number of distinct colors

*/

struct DynSegTree
{
  struct Node
  {
    int mx = 0, lazy = 0;
    int l = -1, r = -1;
  };

  vector<Node> st;
  int n;

  DynSegTree(int n = 0) : n(n)
  {
    st.reserve(1);
    st.push_back(Node());
  }

  int newNode()
  {
    st.push_back(Node());
    return (int)st.size() - 1;
  }

  void push(int p)
  {
    if (st[p].lazy == 0)
      return;
    int val = st[p].lazy;

    if (st[p].l == -1)
      st[p].l = newNode();
    if (st[p].r == -1)
      st[p].r = newNode();

    st[st[p].l].mx += val;
    st[st[p].l].lazy += val;

    st[st[p].r].mx += val;
    st[st[p].r].lazy += val;

    st[p].lazy = 0;
  }

  void add(int &p, int l, int r, int ql, int qr, int val)
  {
    if (ql > r || qr < l)
      return;
    if (p == -1)
      p = newNode();

    if (ql <= l && r <= qr)
    {
      st[p].mx += val;
      st[p].lazy += val;
      return;
    }

    push(p);
    int mid = (l + r) >> 1;
    if (ql <= mid)
    {
      if (st[p].l == -1)
        st[p].l = newNode();
      add(st[p].l, l, mid, ql, qr, val);
    }
    if (qr > mid)
    {
      if (st[p].r == -1)
        st[p].r = newNode();
      add(st[p].r, mid + 1, r, ql, qr, val);
    }

    int leftMx = (st[p].l == -1 ? 0 : st[st[p].l].mx);
    int rightMx = (st[p].r == -1 ? 0 : st[st[p].r].mx);
    st[p].mx = max(leftMx, rightMx);
  }

  int queryMax(int p, int l, int r, int ql, int qr)
  {
    if (p == -1 || ql > r || qr < l)
      return 0;
    if (ql <= l && r <= qr)
      return st[p].mx;

    int mid = (l + r) >> 1;
    int res = 0;
    if (st[p].lazy != 0)
    {
      // Since this is implicit tree, push before going down
      // but query can also work if we push here
    }
    if (st[p].lazy != 0)
      push(p);

    if (ql <= mid)
      res = max(res, queryMax(st[p].l, l, mid, ql, qr));
    if (qr > mid)
      res = max(res, queryMax(st[p].r, mid + 1, r, ql, qr));
    return res;
  }
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<vector<int>> g(n + 1);
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  struct Op
  {
    int type, v, c;
  };
  vector<Op> ops(q);
  vector<int> allColors;

  for (int i = 0; i < q; i++)
  {
    cin >> ops[i].type >> ops[i].v;
    if (ops[i].type == 1)
    {
      cin >> ops[i].c;
      allColors.push_back(ops[i].c);
    }
  }

  sort(allColors.begin(), allColors.end());
  allColors.erase(unique(allColors.begin(), allColors.end()), allColors.end());

  unordered_map<int, int> colorId;
  colorId.reserve(allColors.size() * 2 + 1);
  for (int i = 0; i < (int)allColors.size(); i++)
  {
    colorId[allColors[i]] = i;
  }

  vector<int> tin(n + 1), tout(n + 1), euler(n + 1), parent(n + 1, -1);
  int timer = 0;

  function<void(int, int)> dfs = [&](int u, int p)
  {
    parent[u] = p;
    tin[u] = ++timer;
    euler[timer] = u;
    for (int v : g[u])
    {
      if (v == p)
        continue;
      dfs(v, u);
    }
    tout[u] = timer;
  };

  dfs(1, 0);

  int K = (int)allColors.size();
  vector<int> root(K, -1);
  vector<DynSegTree> trees;
  trees.reserve(K);
  for (int i = 0; i < K; i++)
    trees.emplace_back(n);

  for (auto &op : ops)
  {
    int l = tin[op.v], r = tout[op.v];

    if (op.type == 1)
    {
      int id = colorId[op.c];
      trees[id].add(root[id], 1, n, l, r, 1);
    }
    else
    {
      int ans = 0;
      for (int id = 0; id < K; id++)
      {
        if (root[id] == -1)
          continue;
        if (trees[id].queryMax(root[id], 1, n, l, r) > 0)
        {
          ans++;
        }
      }
      cout << ans << '\n';
    }
  }
}