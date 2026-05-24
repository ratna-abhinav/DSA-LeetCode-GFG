#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll NEG = -(1LL << 60);

int N, K;
vector<vector<int>> tree;
vector<int> profit;
vector<int> subtree_sz;

/*
    dp[u][k][0]
        = maximum profit from subtree of u
        if we select exactly k nodes
        and u is NOT selected

    dp[u][k][1]
        = maximum profit from subtree of u
        if we select exactly k nodes
        and u IS selected
*/

vector<vector<array<ll, 2>>> dp;

void dfs(int cur, int par)
{
    vector<int> ch;
    subtree_sz[cur] = 1;

    for (int nxt : tree[cur])
    {
        if (nxt == par) continue;

        dfs(nxt, cur);

        subtree_sz[cur] += subtree_sz[nxt];
        ch.push_back(nxt);
    }

    for (int k=0; k<=K; k++)
    {
        dp[cur][k][0] = NEG;
        dp[cur][k][1] = NEG;
    }

    // --------------------------
    // CASE 1 : cur NOT selected
    // --------------------------

    int m = ch.size();

    /*
        f0[i][j] = 
            max profit if we have considered first i children only
            and selecting exactly j nodes
    */

    vector<vector<ll>> f0(m + 1, vector<ll>(K + 1, NEG));

    f0[0][0] = 0;   // if we have not selected any child, profit = 0

    for (int i=0; i<m; i++)
    {
        int v = ch[i];

        for (int used=0; used<=K; used++)
        {
            if (f0[i][used] == NEG) continue;

            for (int take=0; take<=subtree_sz[v] && used+take<=K; take++)
            {
                ll best_child = max(dp[v][take][0], dp[v][take][1]);

                if (best_child == NEG) continue;

                f0[i+1][used+take] = max(f0[i+1][used+take], f0[i][used] + best_child);
            }
        }
    }

    for (int k=0; k<=K; k++)
    {
        dp[cur][k][0] = f0[m][k];
    }

    // --------------------------
    // CASE 2 : cur selected
    // --------------------------

    /*
        f1[i][j] =
                max profit if we have considered first i children only
                and selecting exactly j nodes from children
                while cur itself is already selected
    */

    vector<vector<ll>> f1(m+1, vector<ll>(K+1, NEG));

    f1[0][0] = profit[cur];

    for (int i=0; i<m; i++)
    {
        int v = ch[i];

        for (int used=0; used<=K; used++)
        {
            if (f1[i][used]==NEG) continue;

            for (int take=0; take<=subtree_sz[v] && used+take<=K; take++)
            {
                if (dp[v][take][0] == NEG) continue;

                f1[i+1][used+take] = max(f1[i+1][used+take], f1[i][used] + dp[v][take][0]);
            }
        }
    }

    /*
        cur itself is selected,
        so total selected nodes = nodes from children + 1
    */

    for (int child_taken=0; child_taken+1<=K; child_taken++)
    {
        dp[cur][child_taken+1][1] = f1[m][child_taken];
    }
}

int main()
{
    cin >> N >> K;
    tree.resize(N + 1);
    profit.resize(N + 1);
    subtree_sz.resize(N + 1);

    dp.resize(N + 1, vector<array<ll, 2>>(K + 1));

    for (int i = 1; i <= N; i++) cin >> profit[i];

    for (int i = 0; i < N - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1, 0);

    ll ans = max(dp[1][K][0], dp[1][K][1]);
    cout << ans << '\n';

}