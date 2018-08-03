#pragma GCC optimize("O3")
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
typedef vector<int> vi;
using edge_t = pair<ll, int>;
using vll = vector<ll>;

struct tree_sparse_table {
    tree_sparse_table() {}
    tree_sparse_table(const vector<vector<edge_t>> &t, int root = 0) {
        lg = 0;
        n = szof(t);
        while (1 << lg <= n) ++lg;
        p = vector<vi>(lg, vi(n, -1));
        depth = vi(n, 0);
        height = vll(n, 0);
        function<void(int)> dfs = [&](int u) {
            for (ii e : t[u]) {
                int v = e.second;
                if (v != p[0][u]) {
                    p[0][v] = u;
                    depth[v] = 1 + depth[u];
                    height[v] = e.first + height[u];
                    dfs(v);
                }
            }
        };
        dfs(root);
        for (int k = 1; k < lg; ++k) {
            for (int u = 0; u < n; ++u) {
                p[k][u] = p[k - 1][u] == -1 ? -1 : p[k - 1][p[k - 1][u]];
            }
        }
    }

    int anc(int u, int d) const {
        for (int k = lg - 1; k >= 0; --k)
            if (d & (1 << k)) u = (u == -1) ? -1 : p[k][u];
        return u;
    }

    int lca(int u, int v) const {
        if (depth[u] > depth[v])
            u = anc(u, depth[u] - depth[v]);
        else if (depth[v] > depth[u])
            v = anc(v, depth[v] - depth[u]);
        assert(depth[u] == depth[v]);
        if (u == v) return u;
        for (int k = lg - 1; k >= 0; --k)
            if (p[k][u] != p[k][v]) u = p[k][u], v = p[k][v];
        assert(p[0][u] == p[0][v] && u != v);
        return p[0][u];
    }

    ll dist(int u, int v) const {
        int w = lca(u, v);
        return height[u] + height[v] - 2 * height[w];
    }

    int lg, n;
    vi depth;
    vll height;
    vector<vi> p;
};

void mmain() {
    int n, q;
    vector<vector<edge_t>> tree;
    scanf("%d%d", &n, &q);
    vll down_profit(n), up_profit(n), contribution(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &down_profit[i]);
    }
    tree.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        --u, --v;
        tree[u].push_back({w, v});
        tree[v].push_back({w, u});
    }
    function<ll(int, int)> compute_down_profit = [&](int u, int p) {
        for (ii e : tree[u]) {
            auto v = e.second;
            auto w = e.first;
            if (v != p) {
                auto pr = compute_down_profit(v, u);
                if (pr > 2 * w) {
                    contribution[v] = pr - 2 * w;
                    down_profit[u] += contribution[v];
                }
            }
        }
        return down_profit[u];
    };
    compute_down_profit(0, -1);
    function<void(int, int, ll)> compute_up_profit = [&](int u, int p, ll pw) {
        up_profit[u] = 0;
        if (p != -1) {
            // is it worth?
            ll wouldget =
                up_profit[p] + down_profit[p] - contribution[u] - 2 * pw;
            if (wouldget > 0) {
                up_profit[u] += wouldget;
            }
        }
        for (ii e : tree[u]) {
            if (e.second != p) {
                compute_up_profit(e.second, u, e.first);
            }
        }
    };
    compute_up_profit(0, -1, -1);
    function<void(int, int)> reweight = [&](int u, int p) {
        for (auto &e : tree[u]) {
            if (e.second != p) {
                // update e.first!
                e.first =
                    down_profit[e.second] - e.first - contribution[e.second];
                reweight(e.second, u);
            }
        }
    };
    reweight(0, -1);
    tree_sparse_table table(tree);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        int w = table.lca(u, v);
        ll dist = table.dist(u, v);
        ll ans = dist + down_profit[w] + up_profit[w];
        cout << ans << "\n";
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