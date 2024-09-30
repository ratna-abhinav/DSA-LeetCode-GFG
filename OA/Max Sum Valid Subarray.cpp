#include <bits/stdc++.h>
using namespace std;

/*

  Find max sum subarray such that the first and last element of the subarray is not same.
  -1e9 <= A[i] <= 1e9

*/

void solve()
{
	int n; cin >> n;
	int arr[n];
	for (int i = 0; i < n; i++) cin >> arr[i];
	vector<int> pf(n+1, 0);
	for (int i = 1; i <= n; i++) pf[i] = pf[i - 1] + arr[i-1];

	map<int,int> m; multiset<pair<int,int>> ms;
	ms.insert({0, arr[0]});
	m[arr[0]] = arr[0];

	int ans = -1e8;
	for (int i=1; i<n; i++)
	{
		int cur = -1e8;
		if (ms.begin()->second != arr[i]) cur = pf[i+1] - ms.begin()->first;
		else if (ms.size() >= 2)
		{
			auto it = ms.begin();
			it++;
			cur = max(cur, pf[i+1] - it->first);
		}
		if (m.count(arr[i]))
		{
			int val = min(m[arr[i]], pf[i]);
			if (m[arr[i]] != val) 
			{
				ms.erase({m[arr[i]], arr[i]});
				m[arr[i]] = val;
				ms.insert({pf[i], arr[i]});
			}
		}
		else ms.insert({pf[i], arr[i]});
		ans = max(ans, cur);
	}
	cout << ans;
}

int32_t main()
{
	solve();
}