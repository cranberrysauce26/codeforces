/*input
6 3
2 1
2 6
4 2
5 6
2 3
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e6+6, LOG = 21;
int n, must_take, p[MAXN][LOG], h[MAXN];
bool kept[MAXN];
vector<int> adj[MAXN];

void dfs(int u) {
	for (int v : adj[u]) {
		if (v!=p[u][0]) {
			p[v][0]=u;
			h[v]=h[u]+1;
			dfs(v);
		}
	}
}

void lca_init() {
	for (int k = 1; k < LOG; ++k) {
		for (int u = 1; u <= n; ++u) {
			p[u][k] = p[p[u][k-1]][k-1];
		}
	}
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d",&n, &must_take);
	for (int i=1; i<=n; ++i) {
		int a, b; scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}	
	dfs(n);
	lca_init();

	kept[n] = true;
	int ntake = n-1;
	for (int keep = n; keep; --keep) {
		if (!kept[keep]) {
			int x = keep, dist = 0;
			for (int k = LOG-1; k >= 0; --k) {
				if (p[x][k]!=0 && !kept[p[x][k]]) {
					x = p[x][k];
					dist += 1<<k;
				}
			}
			x = p[x][0];
			++dist;
			assert(kept[x]);
			if (ntake-dist >= must_take) {
				int y = keep;
				while (y!=x) {
					kept[y] = true;
				 	--ntake;
				 	y = p[y][0];
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) if (!kept[i]) printf("%d\n", i);
}
