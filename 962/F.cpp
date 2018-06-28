#include <bits/stdc++.h>
#define LOCAL
#ifdef LOCAL
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

using namespace std;
#define szof(v) ((int)(v).size())
#define allof(v) begin(v), end(v)
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
const int MAX = 1e5 + 5;
int n, m, disc[MAX], finish[MAX], dfst = 0, cycleader[MAX], simple[MAX];
ii edges[MAX];
vector<int> adj[MAX];

/*
Consider a cycle c0, c1, ..., c[k-1]
If one of the edges is bad, then they are all bad. Therefore they are good iff they are all good.
Create an equivalence relation R to be R(e1, e2) iff e1 and e2 are connected by a cycle
*/
void dfs(int u) {
    disc[u] = ++dfst;
    for (int e : adj[u]) {
        int v = edges[e].first == u ? edges[e].second : edges[e].first;
        if (!disc[v]) {
            dfs(v);
        } else {
            if (!finish[v]) {
                // you have a cycle!
                if (cycleader[v] > 0) {
                    cycleader[v] = -1;
                } else if (cycleader[v] == 0) {
                    cycleader[v] = u;
                    // update the cycles
                }
            }
        }
    }
    finish[u] = ++dfst;
}

void mmain() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &edges[i].first, &edges[i].second);
        adj[edges[i].first].push_back(i);
        adj[edges[i].second].push_back(i);
    }
    for (int u = 1; u <= n; ++u) {
        if (!disc[u]) {
            dfs(u);
        }
    }
}

int main() {
#ifdef LOCAL
    clock_t begin = clock();
    printf("*********Starting program*********\n\n");
    freopen("data.txt", "r", stdin);
#endif
    mmain();
#ifdef LOCAL
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime taken: %lf\n", elapsed_secs);
#endif
}