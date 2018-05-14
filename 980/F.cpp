/*input
9 10
7 2
9 2
1 6
3 1
4 3
4 7
7 6
9 8
5 8
5 9
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

const int MAXN = 1e6+6, INF = 1e9;
int n, m, ng=0, dfst=0, p[MAXN], disc[MAXN], lowlink[MAXN], g[MAXN], idx[MAXN], gsz[MAXN]; 
vector<int> adj[MAXN];
vector<ii> gadj[MAXN];

stack<int> dfs_stack;
void dfs(int u) {
	disc[u] = lowlink[u] = ++dfst;
	dfs_stack.push(u);
	for (int v : adj[u]) {
		if (!disc[v]) {
			p[v] = u;
			dfs(v);
			lowlink[u] = min(lowlink[u], lowlink[v]);
		} else if (v!=p[u] && disc[v] < lowlink[u]) {
			lowlink[u] = disc[v];
		}
	}
	if (disc[u]==lowlink[u]) {
		++ng;
		gsz[ng] = 0;
		int i = 0;
		while (true){
			int v = dfs_stack.top();
			dfs_stack.pop();
			g[v] = ng;
			++gsz[ng];
			idx[v] = i++;
			if (v==u) break;
		}
	}
}

int visit[MAXN];
void buildg(int u) {
	visit[u] = true;
	for (int v : adj[u]) {
		if (!visit[v]) {
			if (g[v]!=g[u]) {
				gadj[g[u]].push_back({v, idx[u]});
				gadj[g[v]].push_back({u, idx[v]});
			}
			buildg(v);
		}
	}
}

int mem[MAXN];

// inline int dist()

int solve(int u) {
	if (mem[u]!=-1) return mem[u];

	/**
	 * How do you do this part?
	 * ok. You want to minimize the maximum.
	 * 
	 * Each adjacent GROUP has a minimum maximum. Compute these.
	 * 
	 * Base case: there are no adjacent groups. returns 0
	 * 
	 * Otherwise, you have gsize choices: where to cut the edge.
	 * For each of these choices, determine the adjacent group that gives you the maximum.
	 * 
	 * Say between indices c and c+1 (mod gsize)
	 * 
	 * That is, determine group G where G is in gadg[g[u]] such that
	 * solve(G)+1+dist(i, G.idx, c, gsz)
	 * dist(i1, i2, cut, sz) = if i2 < i i2+=sz. same for cut. if i1 <= cut < i2 go other way. 
	 */

	int gsize = gsz[g[u]];
	if (gsize==1) {
		
	} else {
		
	}

	mem[u] = INF;
	int gsize = gsz[g[u]];
	// for (int i = 0; i < gsize; ++i) {
	// 	// try removing i->(i+1)
	// 	// so pick one of the endpoints of i
	// 	mem[u] = min(mem[u], min(      ));
	// }
	for (ii e : gadj[g[u]]) {
		mem[u] = min(mem[u], min((idx[u]-e.second+gsize)%gsize, (e.second-idx[u]+gsize)%gsize)+1+solve(e.first));
	}
	return mem[u];
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0, a, b; i < m; ++i) {
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1);
	for (int i = 1; i <= n; ++i) {
		printf("u = %d, g = %d, idx = %d\n", i, g[i], idx[i]);
	}
	buildg(1);
	memset(mem, -1, sizeof mem);
	for (int u = 1; u <= n; ++u) printf("%d\n", solve(u));
}