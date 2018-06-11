/*input

*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

int n, a, b;
int adj[1005][1005];

int main() {
	freopen("data.txt", "r", stdin);
	cin >> n >> a >> b;
	if (a!=1 && b!=1) {
		// while (1) {}
		cout << "NO\n";
		return 0;
	}
	if (n==1) {
		cout << "YES\n0\n";
		return 0;
	}
	if (a==1 && b==1) {
		if (n<=3) {
			cout << "NO\n";
			return 0;
		}
	}

	cout << "YES\n";
	// compute
	int target = max(a,b);

	for (int u = target; u < n; ++u) {
		adj[u][u+1] = 1;
		adj[u+1][u] = 1;
	}
	if (b!=1) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				adj[i][j] ^= 1;
			}
		}
		for (int i = 1; i <= n; ++i) {
			adj[i][i] = 0;
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			printf("%d", adj[i][j]);
		}
		printf("\n");
	}
}
