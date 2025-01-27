#include <bits/stdc++.h>
using namespace std;

/*

  Given a tree of N (N <= 1e5) nodes. Count no of distinct pair of nodes such that distance
  between them is exactly equal to k

  I/P:

  16 3
  1 2
  1 3
  1 4
  2 5
  2 6
  3 9
  4 10
  4 11
  6 7
  6 8
  10 12
  11 13
  13 14
  13 15
  14 16

  O/P: 22

*/

int n,k;
int in[1010][110],out[1010][110];
vector<int> tree[1010];

void dfs1(int cur, int par)
{
  in[cur][0] = 1;
  for (auto nb:tree[cur])
  {
    if (nb==par) continue;
    dfs1(nb, cur);
    for (int i=1; i<=k; i++) in[cur][i] += in[nb][i-1];
  }
}

void dfs2(int cur, int par)
{
  vector<int> tots(k+1,0);
  for (auto nb:tree[cur])
  {
    if (nb==par) continue;
    for (int i=0; i<=k; i++) tots[i] += in[nb][i];
  }

  for (auto nb:tree[cur])
  {
    if (nb==par) continue;
    out[nb][0] = out[nb][1] = 1;
    for (int i=2; i<=k; i++) out[nb][i] += out[cur][i-1] + tots[i-2] - in[nb][i-2];
    dfs2(nb, cur);
  }
}

void solve()
{
  cin >> n >> k;
  for (int i=0; i<n-1; i++)
  {
    int u,v; cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  out[1][0] = 1;
  dfs1(1,0); dfs2(1,0);
  int ans = 0;
  for (int i=1; i<=n; i++) ans += in[i][k] + out[i][k];
  cout << ans/2;
}

int main()
{
  solve();
}