#include <bits/stdc++.h>
// #define LOCAL
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
const int MAXN = 1e5 + 5, INF = 1e9;
int n, m, k, s, a[MAXN], dist[105][MAXN], visit[MAXN];
vector<int> adj[MAXN];

void bfs(int t) {
    queue<int> q;
    for (int u = 1; u <= n; ++u) {
        if (a[u] == t) {
            q.push(u);
            visit[u] = 1;
        } else {
            visit[u] = 0;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!visit[v]) {
                q.push(v);
                dist[t][v] = dist[t][u] + 1;
                visit[v] = 1;
            }
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    scanf("%d%d%d%d", &n, &m, &k, &s);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int type = 1; type <= k; ++type) {
        bfs(type);
    }
    
    for (int u = 1; u <= n; ++u) {
        ll ans = 0;
        vector<int> vals;
        for (int t=1; t<=k; ++t) {
            vals.push_back(dist[t][u]);
        }
        sort(allof(vals));
        for (int i = 0; i < s; ++i) {
            ans += vals[i];
        }
        cout << ans;
        if (u == n) {
            cout << "\n";
        } else {
            cout << " ";
        }
    }
}