#include <bits/stdc++.h>
using namespace std;

int opt[100], K, N;
double cost[100][100], dp[100][100];
const double INF = 1e12;

/*
    You need to transmit message from port 0 to port N. You can only transmit the message from i-th port to (i+1)th port, 
    and the transmission can fail with p[i] probability. Then you need to again retransmit the message from the previous port which has a memory. Port 0 and port N already have memory. 
    Find the minimum number of expected transmissions required to send the message from port zero to port n if we are allowed to select k additional ports to have memory.

    Solution:

    Dp(i,k) = min no of expected transmissions to transmit the message till ith port given that we are left with k operations

    Transition:
    Dp(i,k) = min (dp(j,k-1) + cost(j...i)) for all j in [0, i-1]

    So basically we iterate over where to place the last memory, say we place it at jth port, then dp(j,k-1) will get the min no of expected 
    transmissions to transmit the message to jth port if we are left with k-1 ops

    opt(i) = j for which dp[i][k] is minimized
    opt(i+1) = j for which dp[i+1][k] is minimized
*/

void compute_dc(int s, int L, int R, int optL, int optR) 
{
    if (L > R) return;
    int mid = (L + R)/2;

    int hi = min(optR, mid - 1), lo = optL;
    // we'll try to calculate the value of dp[s][mid]
    // hi is uptill min(optR, mid - 1) because the last memory will be used in port [0..mid-1]

    double bestVal = INF;
    int optM = -1;
    
    // we are placing the last memory at jth port
    for (int j=lo; j<=hi; j++) 
    {
        double cand = dp[s-1][j] + cost[j][mid];
        if (cand < bestVal) 
        {
            bestVal = cand;
            optM = j;
        }
    }
    dp[s][mid] = bestVal;

    if (L == R) return;
    if (optM == -1) 
    {
        compute_dc(s, L, mid - 1, optL, optR);
        compute_dc(s, mid + 1, R, optL, optR);
    } 
    else 
    {
        compute_dc(s, L, mid - 1, optL, optM);
        compute_dc(s, mid + 1, R, optM, optR);
    }
}

int main() 
{
    cin >> N >> K;
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++) cin >> cost[i][j];
    }

    for (int s = 1; s <= K; ++s)
    {
        dp[s][0] = 0.0;
        compute_dc(s, 0, N, 0, N - 1);
    }
    double ans = dp[K][N];
    cout << ans;
}
