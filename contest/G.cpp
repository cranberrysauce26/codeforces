/*input

*/
#include <bits/stdc++.h>
using namespace std;
#define szof(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

const int MAXN = 2e5+5;

int n, a[MAXN], sz[MAXN];
vector<int> adj[MAXN];

struct gcdtracker {
	void add(int x) {

	}
	void clear() {

	}
};

int treesz(int u, int p) {
	sz[u] = 1;
	for (int v : adj[u]) {
		sz[u] += treesz(v,u);
	}
	return sz[u];
}

void dfs(int u, int p, gcdtracker& tracker) {
	int mxsz = -1, heavy = -1;
	for (int v : adj[u]) {
		if (v!=p && sz[v] > mxsz) {
			heavy = v;
			mxsz = sz[v];
		}
	}
	if (heavy!=-1) {
		dfs(heavy, u, tracker);
	}
	gcdtracker tmp;
	for (int v : adj[u]) {
		if (v != p && v != heavy) {
			tmp.clear();
			dfs(v,u,tmp);
			// merge
		}
	}
	tracker.add(a[u]);
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n-1; ++i) {
		int u,v; scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	gcdtracker tracker;
	dfs(1, 0, tracker);
}
