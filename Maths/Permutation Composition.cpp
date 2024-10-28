											/*    JAI SHRI RAM    */
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,a,b) for(int i=a; i<b; i++)
#define vi vector<int>
#define vvi vector<vi>
#define pi pair<int,int>
#define len(v) (int)(v.size())
#define all(v) v.begin(), v.end()
#define nl '\n'

int add(int x, int y, int mod) { int res = 0ll + x + y; return (res >= mod ? res - mod : res); }
int mul(int x, int y, int mod) { x %= mod, y %= mod; int res = 1ll * x * y; return (res >= mod ? res % mod : res); }
int mod_pow(int x, int y, int mod) { if (y <= 0) return 1; int ans = 1; x %= mod; while (y) { if (y & 1) ans = mul(ans, x, mod); x = mul(x, x, mod); y >>= 1; } return ans; }


/*
  Atcoder 377 - E

  You are given a permutation P. The following operation will be performed K times:
      -> For i=1,2,…,N, simultaneously update P[i] to P[P[i]]
  Print P after all operations

  N <= 2e5, K <= 1e18
*/

void solve()
{
	int n, k; cin >> n >> k; int arr[n+1];
	rep(i,1,n+1) cin >> arr[i];

	vvi all_cycles;
	vi vis(n+1, 0);
	rep(i,1,n+1)
	{
		if (vis[i]) continue;
		int v = i;
		vi cur_cycle;
		while (!vis[v])
		{
			cur_cycle.push_back(v);
			vis[v] = 1;
			v = arr[v];
		}
		all_cycles.push_back(cur_cycle);
	}

	vi ans(n+1, 0);
	for (auto v:all_cycles)
	{
		int sz = len(v);
		for (int i=0; i<sz; i++)
		{
			int val = mod_pow(2,k,sz);
			ans[v[i]] = v[(i+val)%sz];
		}
	}
	rep(i,1,n+1) cout << ans[i] << ' ';
}

signed main()
{
	solve();
}
