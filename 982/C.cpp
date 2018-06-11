/*input
12
1 2
1 3
3 4
3 5
5 6
6 7
7 8
7 9
9 10
7 11
3 12
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

vector<int> adj[100005];
int n;

int treesz[100005];

int dfs1(int u, int p){
	treesz[u]=1;
	for (int v : adj[u]) {
		if (v!=p) treesz[u]+=dfs1(v,u);
	}
	return treesz[u];
}

int dfs(int u, int p){
	int ans=0;
	for (int v : adj[u]){
		if (v!=p){
			if (treesz[v]%2==0){
				ans += 1+dfs(v,u);
			} else {
				ans += dfs(v,u);
			}
		}
	}
	return ans;
}



int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n;
	if (n%2==1) return !printf("-1\n");
	for (int i=1; i<n; ++i){
		int u,v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs1(1, 0);
	int ans=dfs(1, 0);
	cout << ans << endl;
}
