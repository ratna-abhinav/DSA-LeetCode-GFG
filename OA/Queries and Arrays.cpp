#include <bits/stdc++.h>
#define int long long
using namespace std;

/*

  We have 3 arrays of size N, A[], B[], C[]. Its given that for each i, A[i] >= B[i]
  Following operation can be performed any number of times.
  In one operation, we can pick two indices i,j and do A[i] += 1 and A[j] -= 1
  but we can do it iff A[j] >= B[j] is satisfied after doing the operation and the
  cost of doing this operation is C[j]

  Find the maximum value of minimum element of final A[] and also find the minimum
  cost required to make that happen.

  Constraints:
  1 <= N <= 1e5
  1 <= A[i], B[i], C[i] <= 1e9
  B[i] <= A[i]

  I/P:
  2
  10
  59 95 8 14 35 13 63 70 15 17
  48 47 7 7 5 9 62 43 12 9
  61 66 68 89 3 57 71 4 27 9
  10
  56 82 40 77 80 32 85 80 41 3
  48 25 27 6 38 21 43 42 39 2
  7 36 25 15 24 85 44 85 53 100 

  O/P:
  [31, 3827]
  [57, 4429]

  I/P:
  1
  4
  1 99 2 99
  1 97 2 98
  1 5 2 2

  O/P:
  [3, 12]

*/

const int MOD = 1e9 + 7;

bool canAchieve(vector<int> &A, vector<int> &B, vector<int> &C, int mid, int &cost)
{
  int N = A.size();
  int curCost = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<int> curA = A;

  for (int i = 0; i < N; ++i)
  {
    if (curA[i] > mid) pq.push({C[i], i});
  }

  for (int i = 0; i < N; ++i)
  {
    while (curA[i] < mid)
    {
      if (pq.empty()) return false;
      auto [costIdx, idx] = pq.top();
      pq.pop();
      if (curA[idx] <= mid || curA[idx] <= B[idx]) continue;

      // move = max we can increase curA[i]
      int move = min(mid - curA[i], curA[idx] - max(B[idx], mid));

      curA[i] += move; curA[idx] -= move;
      curCost = (curCost + move * costIdx) % MOD;
      if (curA[idx] > mid) pq.push({C[idx], idx});
    }
  }
  cost = curCost;
  return true;
}

pair<int, int> findMaxMin(vector<int> &A, vector<int> &B, vector<int> &C)
{
  int lo = *min_element(B.begin(), B.end());
  int hi = *max_element(A.begin(), A.end());
  int ans = lo, minCost = LLONG_MAX;

  while (lo <= hi)
  {
    int mid = lo + (hi - lo) / 2;
    int cost = 0;

    if (canAchieve(A, B, C, mid, cost))
    {
      ans = mid;
      minCost = cost;
      lo = mid + 1;
    }
    else hi = mid - 1;
  }
  return {ans, minCost};
}
 
int32_t main()
{
  int T;
  cin >> T;

  while (T--)
  {
    int N;
    cin >> N;

    vector<int> A(N), B(N), C(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];
    for (int i = 0; i < N; ++i) cin >> C[i];

    pair<int, int> result = findMaxMin(A, B, C);
    cout << "[" << result.first << ", " << result.second << "]" << endl;
  }
}