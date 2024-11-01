#include <bits/stdc++.h>
#define int long long
using namespace std;

#define accuracy chrono::steady_clock::now().time_since_epoch().count()
mt19937 rng(accuracy);
int rand(int l, int r)
{
	uniform_int_distribution<int> ludo(l, r);
	return ludo(rng);
}

const int MX = 1e6+2, MOD = 1e9+7;
vector<int> spf(MX+1);

int mod_pow(int x, int y)
{
	x %= MOD;
	if (y==0) return 1;
	if (y==1) return x;

	int ans = 1;
	while (y)
	{
		if (y&1) ans = (ans*x)%MOD;
		x = (x*x)%MOD;
		y >>= 1;
	}
	return ans;
}

// calculate LCM(arr) % MOD
int calc_lcm(vector<int> arr)
{
	int n = arr.size();
	map<int,int> allExps;
	for (int i=0; i<n; i++)
	{
		int e = arr[i];
		map<int,int> curExps;
		while (e>1)
		{
			curExps[spf[e]]++;
			e /= spf[e];
		}
		for (auto &it:curExps) allExps[it.first] = max(allExps[it.first], it.second);
	}
	int ans = 1;
	for (auto &it:allExps) ans = (ans * mod_pow(it.first, it.second)) % MOD;
	return ans;
}

void solve()
{
	for (int i=1; i<MX; i++) spf[i] = i;
	for (int i=2; i*i<MX; i++)
	{
		if (spf[i]==i)
		{
			for (int j=i*i; j<MX; j+=i)
			{
				if (spf[j]==j) spf[j] = i;
			}
		}
	}

	int n = rand(1,10);
	vector<int> arr(n);
	// for (int i=0; i<n; i++) cin >> arr[i];
	for (int i=0; i<n; i++) arr[i] = rand(1,15);
	int l = calc_lcm(arr);
	
	int ans = 1;
	for (int e:arr) ans = lcm(ans, e);
	assert(ans==l);
	for (auto e:arr) cout << e << ' '; cout << endl;
	cout << l;
}

int32_t main()
{
	solve();
}