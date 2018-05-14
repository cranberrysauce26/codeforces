#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int INF = 1e9;
vector<unordered_set<int>> g;
int n, m;
vector<int> dist, order, p, leafh;
stack<int> steps;

void bfs() {
	queue<int> q;
	dist.resize(n+1, INF);
	p.resize(n+1, 0);
	leafh.resize(n+1, 0);
	order.reserve(n+1);
	q.push(1);
	dist[1] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		order.push_back(u);
		for (int v : g[u]) {
			if (dist[v] == INF) {
				dist[v] = 1+dist[u];
				p[v] = u;
				q.push(v);
			}
		}
	}
	for (int i = sz(order)-1; i >= 0; --i) {
		leafh[p[order[i]]] = max(leafh[p[order[i]]], leafh[order[i]]+1);
	}

	if (dist[n]!=INF) {
		steps.push(n);
		while (steps.top() != 1) {
			steps.push(p[steps.top()]);
		}
	}
}

void find_loop() {
	/*
		What are you looking for?
		u1 = 1 -> u2 -> ... -> v -> ch1 -> ch2 -> v -> n

		You need to find a v that is reachable from u such that v has grandchild ch2 such that ch2 is not directly connected to v
		
		for each v
			for each ch1 in g[u]
				for each ch2 in g[ch1]
					if v is not connected to ch2
						go.
	*/
	int bestu = -1;
	for (int u = 1; u <= n; ++u) {
		if (leafh[u] >= 2) {
			if (dist[u]+4 < dist[n]) {
				dist[n] = dist[u]+4;
				bestu = u;
			}
		}
	}
	if (bestu != -1) {
		steps = stack<int>();
		// push the loop
		// n <- u <- ch2[u] <- ch[u] <- u <- p[u] <- p[p[u]] <- ... <- 1
		int ch1 = -1;
		for (int ch : g[bestu]) {
			if (leafh[ch]+1 == leafh[bestu]) {
				ch1 = ch;
				break;
			}
		}
		assert(ch1!=-1);
		int ch2 = -1;
		for (int ch : g[ch1]) {
			if (leafh[ch]+1 == leafh[ch1]) {
				ch2 = ch;
				break;
			}
		}
		steps.push(n);
		steps.push(bestu);
		steps.push(ch2);
		steps.push(ch1);
		steps.push(bestu);
		while (steps.top() != 1) {
			steps.push(p[steps.top()]);
		}
	}
}

void find_triangles() {
	int uu = -1, vv1 = -1, vv2 = -1;
	for (int u : order) {
		for (int v1 : g[u]) {
			if (v1 == p[u]) continue;
			for (int v2 : g[v1]) {
				if (v2 != u && g[u].find(v2) == g[u].end()) {
					uu = u, vv1 = v1, vv2 = v2;
					goto done;
				}
			}
		}
	}
done:
	if (uu!=-1 && dist[uu]+4 < dist[n]) {
		dist[n] = dist[uu]+4;
		steps = stack<int>();
		steps.push(n);
		steps.push(uu);
		steps.push(vv2);
		steps.push(vv1);
		steps.push(uu);
		while (steps.top() != 1) {
			steps.push(p[steps.top()]);
		}
	}
}

int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n >> m;
	g.resize(n+1);
	for (int i = 0, a, b; i < m; ++i) {
		cin >> a >> b;
		g[a].insert(b);
		g[b].insert(a);
	}
	bfs();
	find_triangles();
	if (dist[n]==INF) cout << "-1\n";
	else {
		cout << dist[n] << "\n";
		for (;!steps.empty();steps.pop()) cout << steps.top() << " ";
		cout << "\n";
	}
}