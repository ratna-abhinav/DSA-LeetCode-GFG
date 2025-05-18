/*

Topcoder - SRM383 - FloorBoards
https://archive.topcoder.com/ProblemStatement/pm/8397

You are building a house and are laying the floorboards in one of the rooms. Each floorboard is a rectangle 1 unit wide and can be of 
any positive integer length. Floorboards must be laid with their sides parallel to one of the sides of the room and cannot overlap. 
In addition, the room may contain features such as pillars, which lead to areas of the floor where no floorboards can be laid. 
The room is rectangular and the features all lie on a unit-square grid within it. You want to know the minimum number of floorboards 
that you need to completely cover the floor.

Input:
4
4 4
####
####
####
####
6 6
#...#.
.##...
......
......
....##
##....
10 10
#.#.#.#...
.##.......
..#....#..
.##.......
....#.#...
.........#
.#.#.#..#.
..##..#..#
...#.#..#.
.......#..
10 10
.#.#...#.#
..#...#...
.....#...#
#.#.#.#.#.
.#...#....
#...#.#.#.
...#...#.#
#...#.#...
.#.#.#.#.#
..#...#...

Output:
0
8
24
33

*/




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

int set(int num, int bit) { return (num | (1ll << bit)); }
int unset(int num, int bit) { return (num & ~(1ll << bit)); }
int toggle(int num, int bit) { return (num ^ (1ll << bit)); }
bool is_set(int num, int bit) { return ((num >> bit) & 1ll); }

int n,m;
char board[11][11];
int dp[2][11][11][1<<10];

int rec(int i, int j, int f, int mask)
{
	if (j==m) return rec(i+1,0,0,mask);
	if (i==n) return 0;

	if (dp[f][i][j][mask] != -1) return dp[f][i][j][mask];

	int ans = 1e8, new_mask = unset(mask, j);
	if (board[i][j]=='#') ans = rec(i, j+1, 0, new_mask);
	else
	{
		// extend horizontal board
		if (f) ans = min(ans, rec(i, j+1, 1, new_mask));

		// extend vertical board
		if (is_set(mask,j)) ans = min(ans, rec(i, j+1, 0, mask));

		// start a new horizontal board
		ans = min(ans, 1+rec(i, j+1, 1, new_mask));

		// start a new vertical board
		ans = min(ans, 1+rec(i, j+1, 0, mask|(1<<j)));
	}
	return dp[f][i][j][mask] = ans;
}

void solve()
{
	cin >> n >> m;
	rep(i,0,n) rep(j,0,m) cin >> board[i][j];
	memset(dp, -1, sizeof dp);
	int ans = rec(0,0,0,0);
	cout << ans << nl;
}

signed main()
{
	int t; cin >> t; while (t--)
	solve();
}