/*    JAI SHRI RAM    */
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,a,b) for(int i=a; i<b; i++)
#define vi vector<int>
#define vvi vector<vi>
#define pi pair<int,int>
#define len(v) (int)(v.size())
#define all(v) v.begin(), v.end()
#define nl '\n'


// SPOJ - DQUERY

int n, cnt_distinct = 0;
int arr[30005], freq[1000005];

void insert(int x)
{
  freq[x]++;
  if (freq[x]==1) cnt_distinct++;
}
void remove(int x)
{
  freq[x]--;
  if (freq[x]==0) cnt_distinct--;
}

void solve()
{
	cin >> n;
  rep(i,0,n) cin >> arr[i];
  int q; cin >> q;
  vvi queries;
  rep(i,0,q)
  {
    int l,r; cin >> l >> r;
    queries.push_back({l-1, r-1, i});
  }
  int block_sz = sqrt(n)+1;
  sort(all(queries), [&](vi &a, vi &b){
    if (a[0]/block_sz != b[0]/block_sz) return a[0]/block_sz < b[0]/block_sz;
    return a[1] < b[1];
  });
  vi ans(q);
  int st=0, en=-1;
  rep(i,0,q)
  {
    int l = queries[i][0], r = queries[i][1];
    while (st>l) st--, insert(arr[st]);
    while (en<r) en++, insert(arr[en]);
    while (st<l) remove(arr[st]), st++;
    while (en>r) remove(arr[en]), en--;
    ans[queries[i][2]] = cnt_distinct;
  }
  rep(i,0,q) cout << ans[i] << nl;
}

signed main()
{
  // int t; cin >> t; while (t--)
  solve();
}
