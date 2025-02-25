/*    JAI SHRI RAM    */
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i, a, b) for (int i = a; i < b; i++)
#define vi vector<int>
#define vvi vector<vi>
#define pi pair<int, int>
#define len(v) (int)(v.size())
#define all(v) v.begin(), v.end()
#define nl '\n'


void solve()
{
	int n; cin >> n; vi arr(n);
	rep(i,0,n) cin >> arr[i];
	
	int ans = 0, i = 0, j = n-1;
	while (i<=j)
	{
		if (arr[i]==arr[j])
		{
			i++;
			j--;
		}
		else if (arr[i]<arr[j])
		{
			arr[i+1] += arr[i];
			i++;
			ans++;
		}
		else
		{
			arr[j-1] += arr[j];
			j--;
			ans++;
		}
	}
	cout << ans;
}

signed main()
{
	solve();
}