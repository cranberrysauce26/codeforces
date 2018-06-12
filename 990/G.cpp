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
const int MAXN = 1e5 + 5, MAXG = 2e5;
int n, val[MAXN], visit[MAXN];
ll num_gcd_pairs[MAXG];
vector<int> adj[MAXN], nodes_with_val[MAXG];

int dfs(int u, int g) {
    int ans = 1;
    visit[u] = 1;
    for (int v : adj[u]) {
        if (!visit[v] && val[v] % g == 0) {
            ans += dfs(v, g);
        }
    }
    return ans;
}

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", val + i);
        nodes_with_val[val[i]].push_back(i);
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int g = MAXG; g >= 1; --g) {
        vector<int> active;
        for (int g2 = g; g2 <= MAXG; g2 += g) {
            for (int u : nodes_with_val[g2]) {
                active.push_back(u);
            }
        }
        if (active.empty()) {
            continue;
        }
        DEBUG("g = %d, nodes: ", g);
#ifdef LOCAL
        for (int u : active) {
            DEBUG("%d ", u);
        }
        printf("\n");
#endif
        ll &cnt = num_gcd_pairs[g];
        cnt = 0;
        for (int u : active) {
            if (!visit[u]) {
                int treesz = dfs(u, g);
                DEBUG("component u = %d, treesz = %d\n", u, treesz);
                cnt += 1LL * treesz * (treesz + 1) / 2;
            }
        }
        DEBUG("g = %d, num_pairs[g] = %lld\n", g, num_gcd_pairs[g]);
        for (int u : active) {
            visit[u] = 0;
        }
    }

    for (int g = MAXG; g >= 1; --g) {
        for (int g2 = 2 * g; g2 <= MAXG; g2 += g) {
            num_gcd_pairs[g] -= num_gcd_pairs[g2];
        }
    }

    for (int i = 1; i <= MAXG; ++i) {
        if (num_gcd_pairs[i]) {
            cout << i << " " << num_gcd_pairs[i] << "\n";
        }
    }
}
