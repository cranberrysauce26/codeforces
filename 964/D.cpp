/*input
4
0 1 2 3
*/
#include <vector>
#include <iostream>
#include <cstring>
#include <queue>
const int MAXN = 2e5+5;
int n, root, p[MAXN], mem[MAXN][2], vis[MAXN];
std::vector<int> adj[MAXN], ch[MAXN][2][2];
std::queue<int> order;
int solve(int u, int x){
	if (mem[u][x]!=-1) return mem[u][x];
	if (!vis[u]) {
		for (int v:adj[u]){
			int a=solve(v,0), b=solve(v,1);
			ch[u][a][b].push_back(v);
		}
		vis[u]=1;
	}
	if (!ch[u][0][0].empty()) mem[u][x]=0;
	else if ( (ch[u][1][1].size()+ch[u][1][0].size()+x)%2==0) mem[u][x]=1;
	else if (!ch[u][1][1].empty()) mem[u][x]=1;
	else mem[u][x]=0;
	return mem[u][x];
}

void reconstruct(int u, int x){
	for (int v:ch[u][0][1]) reconstruct(v,1);
	if ( (ch[u][1][1].size()+ch[u][1][0].size()+x)%2==0) {
		order.push(u);
		for (int v:ch[u][1][1]) reconstruct(v,0);
		for (int v:ch[u][1][0]) reconstruct(v,0);
	} else {
		reconstruct(ch[u][1][1][0],1);
		order.push(u);
		for (size_t i=1; i<ch[u][1][1].size(); ++i){
			reconstruct(ch[u][1][1][i],0);
		}
		for (int v:ch[u][1][0]) reconstruct(v,0);
	}
}
int main() {
	scanf("%d", &n);
	for (int i=1;i<=n;++i){
		int par; scanf("%d", &par);
		if (par==0) root=i;
		adj[par].push_back(i);
	}
	memset(mem, -1, sizeof mem);
	if (solve(root,0)){
		printf("YES\n");
		reconstruct(root,0);
		for(;!order.empty();order.pop()) printf("%d ", order.front());
		printf("\n");
	} else {
		printf("NO\n");
	}
}