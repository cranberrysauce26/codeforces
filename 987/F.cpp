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
const int MAXN = 23;
int n, m;
bool visit[1 << MAXN], active[1 << MAXN];

void dfs(int u) {
    visit[u] = 1;
    DEBUG("dfs(%d)\n", u);

    for (int k = 0; k < n; ++k) {
        if (u & (1 << k)) {
            int v = u - (1 << k);
            if (!visit[v]) {
                dfs(v);
            }
        }
    }

    // visit inverse sub children
    if (active[u]) {
        int inv = (1 << n) - 1 - u;
        if (!visit[inv]) {
            dfs(inv);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u;
        scanf("%d", &u);
        active[u] = true;
    }
    int ncomps = 0;
    for (int u = 0; u < 1 << n; ++u) {
        if (!visit[u] && active[u]) {
            DEBUG("\nROOT = %d\n", u);
            visit[u] = 1;
            dfs((1 << n) - 1 - u);
            ++ncomps;
        }
    }
    printf("%d\n", ncomps);
}