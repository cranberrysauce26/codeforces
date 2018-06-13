#include <bits/stdc++.h>

#ifdef LOCAL
#define DEBUG(fmt, ...) printf(fmt, ##_VA_ARGS)
#else
#define DEBUG(fmt, ...)
#endif

using namespace std;
#define szof(v) ((int)(v).size())
#define allof(v) begin(v), end(v)
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int MAXN = 1e5 + 5;
int n, m, s[MAXN], visit[MAXN], f[MAXN];
vector<int> adj[MAXN];

bool solve(int u) {
    visit[u] = 1;
    int nch = 0;
    for (int v : adj[u]) {
        if (!visit[v]) {
            ++nch;
        }
    }
    if (nch == 0) {
        f[u] = s[u];
    } else {
    }
}

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", s + i);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int u = 1; u <= n; ++u) {
        if (!visit[u]) {
            if (!solve(u)) {
                printf("IMPOSSIBLE\n");
                return 0;
            }
        }
    }
    printf("POSSIBLE\n");
}
