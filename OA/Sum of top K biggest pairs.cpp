#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
using ll = long long;

/*

  We are given an array arr of size N and an integer K. Find the total sum of k biggest distinct index pairs.
  Index pairs (i,j), (j,i), (i,i) all are considered as different index pairs

  N <= 1e5, K <= min(1e9, n*n)

  I/P: arr = {5,1,4,2}, K = 5
  O/P: (5+5) + (5+4) + (4+5) + (4+4) + (5+2) = 43

*/

ll max_total_transfer_rate(vector<int>& arr, ll K) 
{
  int n = arr.size();
  sort(arr.begin(), arr.end());

  vector<ll> prefixSum(n + 1, 0);
  for (int i=0; i<n; ++i) prefixSum[i + 1] = prefixSum[i] + arr[i];

  ll lo = 2LL*arr[0], hi = 2LL*arr[n-1], S = 0;
  while (lo <= hi) 
  {
    ll mid = (lo+hi) / 2, total_pairs = 0;
    int j = n - 1;

    // Count total index pairs with sum >= mid
    for (int i=0; i<n; ++i) 
    {
      while (j>=0 && arr[i]+arr[j] >= mid) j--;
      total_pairs += n-j-1;
    }
    if (total_pairs >= K) 
    {
      S = mid;
      lo = mid + 1;
    } 
    else hi = mid - 1;
  }

  // Now compute the total sum of the K biggest sum index pairs
  ll total_pairs = 0, total_sum = 0; vector<int> idx(n, n);
  int j = n - 1;

  for (int i=0; i<n; ++i) 
  {
    while (j>=0 && arr[i]+arr[j] >= S) j--;
    idx[i] = j+1;
    ll count = n - idx[i];
    total_pairs += count;
    total_sum += 1LL*arr[i]*count + (prefixSum[n] - prefixSum[idx[i]]);
  }

  // Adjust for extra pairs if total_pairs > K
  if (total_pairs > K) 
  {
    ll extra_pairs = total_pairs - K;
    total_sum -= extra_pairs * S;
  }

  return total_sum;
}

int main() 
{
  int n; cin >> n; vector<int> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  ll K; cin >> K;
  cout << max_total_transfer_rate(arr, K) << endl;
}