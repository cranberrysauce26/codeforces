/*input
3 1 3
1 2
1 3

*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

int n, x, y, root, treesz[300005], h[300006], reachesy[300006];
vector<int> adj[300005];

ll totpaths = 0;

int dfs(int u, int par) {
	treesz[u] = 1;
	if (u==y) reachesy[u] = true;
	else reachesy[u] = false;
	
	for (int v : adj[u]) {
		if (v!=par) {
			h[v] = 1+h[u];
			treesz[u]+=dfs(v,u);
			reachesy[u] |= reachesy[v];
		}
	}
	
	return treesz[u];
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d%d", &n, &x, &y);
	if (n==2) {
		return !printf("1\n");
	}

	totpaths = 1LL*n*(n-1);
	ll badpaths = 0;
	for (int i = 1; i < n; ++i) {
		int a, b; scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	dfs(x, -1);

	badpaths=0;
	ll cnt1=1;
	for (int v : adj[x]) {
		if (!reachesy[v]) {
			cnt1 += treesz[v];
		}
	}

	ll cnt2 = treesz[y];

	badpaths = cnt1*cnt2;

	// dfs(root, -1);

	// if (hi[x] < lo[y] || hi[y] < lo[x]) {
	// 	badpaths = 1LL*treesz[x]*treesz[y];
	// } else if (lo[x] < lo[y]) {
	// 	printf("case 2\n");
	// 	// y is child of x
	// 	badpaths = 1LL*(n-treesz[x]+1)*treesz[y];
	// } else {
	// 	badpaths = 1LL*(treesz[x]*(n-treesz[y]+1));
	// }
	cout << totpaths - badpaths << endl;
}
