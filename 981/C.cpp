/*input
6
1 2
3 2
2 4
4 5
4 6
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;
const int MAXN = 1e5+5;
int n, deg[MAXN];

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		deg[u]++;
		deg[v]++;
	}

	int cnt = 0;
	for (int u = 1; u <= n; ++u) {
		if (deg[u] > 2) ++cnt;
	}

	if (cnt > 1) {
		printf("No\n");
		return 0;
	}

	printf("Yes\n");

	int root = 1;

	if (cnt == 1) {
		for (int u = 1; u <= n; ++u) {
			if (deg[u] > 2) root = u;
		}
	}

	vector<int> leaves;

	for (int u = 1; u <= n; ++u) {
		if (deg[u]==1 && u != root) {
			// printf("%d %d\n", root, u);
			leaves.push_back(u);
		}
	}

	printf("%d\n", sz(leaves));
	for (int u : leaves) {
		printf("%d %d\n", root, u);
	}
}
