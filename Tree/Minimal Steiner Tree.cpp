/*

  Given a unrooted tree of n nodes. You are also given a list of special nodes. Find the minimum time
  required to start and end at any node while visiting all the special nodes in any order.

*/

// Below is another way to prune nodes and find the minimal steiner subtree. After pruning, the leftover edges will
// definitely be traversed atleast once in order to visit all the special nodes


vector<set<int>> tree(n);
for (auto &e : edges)
{
  int u = e[0], v = e[1];
  tree[u].insert(v);
  tree[v].insert(u);
}

queue<int> qu;
for (int i = 0; i < n; i++)
{
  if (tree[i].size() == 1 && !special[i]) qu.push(i);
}

// 3) do pruning
while (!qu.empty())
{
  int cur = qu.front();
  qu.pop();
  if (tree[cur].empty()) continue; // already pruned

  int par = *tree[cur].begin();
  // remove the edge cur–par
  tree[par].erase(cur);
  tree[cur].erase(par);

  // if par became a non‑special leaf, prune it next
  if (tree[par].size() == 1 && !special[par])
    qu.push(par);
}

// 4) now ‘tree’ contains only the Steiner subtree
