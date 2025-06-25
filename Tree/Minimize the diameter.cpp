/*    JAI SHRI RAM    */
#include <bits/stdc++.h>
using namespace std;

#define int long long
int _t;
void solve();

void IO()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}

void testcase(int _t)
{
  cin >> _t;
  while (_t--) solve();
}

#define nl '\n'
#define rep(i,a,b) for(int i=a; i<b; i++)
#define vi vector<int>

int n, m, k;

/*

  You have an undirected and unrooted tree of n nodes. You are allowed to remove atmax
  k nodes. Minimize the diameter of the final tree.

  Time Complexity = O(n*n*n)


  we'll keep removing any one of the diametric ends
  if there are multiple diametric ends, then we will remove the end from which
  maximum no of diameter originate

  we can find distance between every pair of vertices, we can do this by doing dfs
  from every vertex

  then we can find which vertices are part of diameter

*/


vi tree[305], deleted(305,0);
int dist[305][305];

void dfs(int cur, int par, int src, int d)
{
  dist[src][cur] = d;
  for (auto nb:tree[cur])
  {
    if (nb==par || deleted[nb]) continue;
    dfs(nb,cur,src,d+1);
  }
}

int calc_diameter()
{
  int ans = 0;
  rep(i,1,n+1)
  {
    rep(j,1,n+1) 
    {
      if (deleted[i] || deleted[j]) continue;
      ans = max(ans, dist[i][j]);
    }
  }
  return ans;
}

int calc_remove_vertex()
{
  int vertex = 0, cnt[n+1] = {0}, cur_diameter = calc_diameter();
  rep(i,1,n+1)
  {
    rep(j,1,n+1)
    {
      if (deleted[i] || deleted[j]) continue;
      if (dist[i][j]==cur_diameter)
      {
        cnt[i]++;
        cnt[j]++;
      }
    }
  }
  int mx = 0;
  rep(i,1,n+1)
  {
    if (!deleted[i] && mx < cnt[i])
    {
      mx = cnt[i];
      vertex = i;
    }
  }
  return vertex;
}

void solve()
{
  cin >> n >> k;
  rep(i,1,n)
  {
    int u,v; cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  rep(i,1,n+1) dfs(i,0,i,0);
  int ans = calc_diameter();
  if (k==0)
  {
    cout << ans << nl;
    return;
  }

  rep(i,1,k+1)
  {
    int optimal_vertex = calc_remove_vertex();
    deleted[optimal_vertex] = 1;

    rep(j,1,n+1)
    {
      if (!deleted[j]) dfs(j,0,j,0);
    }

    ans = min(ans, calc_diameter());
  }
  cout << ans;
}

signed main()
{
  IO();

  // testcase(_t);
  solve();
}