/*input
10
1 2 3 4 5

*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

const int INF = 1e9;
int n, np, p[55], dp[55][105][2];

int solve(int i, int pos, int col) {
	if (i > np) return 0;
	if (pos > n) return INF;
	if (dp[i][pos][col]!=-1) return 0;
	int &ans = dp[i][pos][col];
	ans = INF;
	if (pos <= p[i]) {
		for (int pos2 = pos; pos2 <= p[i]; ++pos2) {
			if ( (pos2&1)==col) {
				ans = min(ans, p[i]-pos2 + solve(i+1, pos2+1, col));
			}
		}
		if (((p[i]+1)&1)==col) {
			ans = min(ans, 1+solve(i+1, p[i]+2, col));
		}
	} else {
		if ((pos&1)==col) {
			ans = min(ans, pos-p[i] + solve(i+1, pos+1, col));
		} else {
			ans = min(ans, pos+1-p[i]+solve(i+1, pos+2, col));
		}
	}
	return ans;
}

int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n;
	np = n/2;
	for (int i = 1; i <=np; ++i) cin >> p[i];
	memset(dp, -1, sizeof dp);
	// dp[i][pos]

	printf("%d\n", min(solve(1,1,1), solve(1,1,0)));
}
