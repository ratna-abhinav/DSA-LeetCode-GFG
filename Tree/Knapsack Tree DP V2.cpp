#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll NEG = -(1LL << 60);

int N, K;
vector<vector<int>> tree;
vector<int> profit;
vector<int> subtree_sz;

/* 
  Time Complexity : O(N*N)
  but this trick got applied here because we could do
  for (int i=subtree_sz[cur]; i>=0; i--)
  {
    .......
    subtree_sz[cur] += subtree_sz[nxt];
  }
*/

/*
    dp[u][k][0]
        = maximum profit from subtree of u
        if we select exactly k nodes
        and u is NOT selected

    dp[u][k][1]
        = maximum profit from subtree of u
        if we select exactly k nodes
        and u IS selected
*/

vector<vector<array<ll, 2>>> dp;

void dfs(int cur, int par)
{
  subtree_sz[cur] = 1;
  for (int k = 0; k <= K; k++)
  {
    dp[cur][k][0] = NEG;
    dp[cur][k][1] = NEG;
  }
  dp[cur][0][0] = 0;
  dp[cur][1][1] = profit[cur];

  for (int nxt : tree[cur])
  {
    if (nxt == par)
      continue;
    dfs(nxt, cur);

    for (int i = subtree_sz[cur]; i >= 0; i--)
    {
      for (int j = subtree_sz[nxt]; j >= 0; j--)
      {
        // case 1: cur is not selected
        dp[cur][i + j][0] = max(dp[cur][i + j][0], dp[cur][i][0] + max(dp[nxt][j][0], dp[nxt][j][1]));

        // case 2: cur is selected
        dp[cur][i + j][1] = max(dp[cur][i + j][1], dp[cur][i][1] + dp[nxt][j][0]);
      }
    }
    subtree_sz[cur] += subtree_sz[nxt];
  }
}

int main()
{
  cin >> N >> K;
  tree.resize(N + 1);
  profit.resize(N + 1);
  subtree_sz.resize(N + 1);

  dp.resize(N + 1, vector<array<ll, 2>>(N + 1));

  for (int i = 1; i <= N; i++)
    cin >> profit[i];

  for (int i = 0; i < N - 1; i++)
  {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  if (K == 0)
  {
    cout << 0 << '\n';
    return 0;
  }

  dfs(1, 0);

  ll ans = max(dp[1][K][0], dp[1][K][1]);
  cout << ans << '\n';
}