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
vector<bool> find_bridges(const vector<vector<int>> &g, const vector<ii> &e) {
    vector<bool> isbridge(szof(e), 0);
    vector<int> lowlink(szof(g), -1), disc(szof(g), -1);

    auto adj = [&](int u, int edge) { return e[edge].first == u ? e[edge].second : e[edge].first; };

    int dfst = 0;
    function<void(int, int)> dfs = [&](int u, int par_edge) {
        lowlink[u] = disc[u] = dfst++;
        for (int ee : g[u]) {
            int v = adj(u, ee);
            if (disc[v] == -1) {
                dfs(v, ee);
                lowlink[u] = min(lowlink[u], lowlink[v]);
            } else if (ee != par_edge) {
                lowlink[u] = min(lowlink[u], disc[v]);
            }
        }
        // Let the dfs parent of u be p
        // then (p,u) is a bridge
        // iff lowlink[u] > disc[p]

        if (par_edge != -1) {
            int p = adj(u, par_edge);
            if (lowlink[u] > disc[p]) {
                isbridge[par_edge] = true;
            }
        }
    };

    for (int u = 0; u < szof(g); ++u) {
        if (disc[u] == -1) {
            dfs(u, -1);
        }
    }

    return isbridge;
}

/**
 * Returns the bridge tree of undirected graph g (or the bridge forest, iff g is disconnected), inputted as an edge list.
 * The number of vertices is n = szof(g)
 * g[u] contains the id's of the edges adjacent to u for 0 <= u < n
 * e[id] is (a, b) representing an undirected edge between vertices a and b
 *
 * The function returns the bridge tree as an adjancency list.
 */
vector<vector<int>> bridge_tree(const vector<vector<int>> &g, const vector<ii> &e) {
    auto adj = [&](int u, int edge) { return e[edge].first == u ? e[edge].second : e[edge].first; };
    auto isbridge = find_bridges(g, e);
    vector<vector<int>> tree;
    vector<bool> visit(szof(g), 0);
    int numcomps = 0;

    function<void(int, int)> build_tree = [&](int u, int comp) {
        visit[u] = 1;
        for (int ee : g[u]) {
            int v = adj(u, ee);
            if (!visit[v]) {
                if (isbridge[ee]) {
                    tree.push_back(vector<int>());
                    assert(szof(tree) - 1 == numcomps);
                    tree[comp].push_back(numcomps);
                    tree[numcomps].push_back(comp);
                    ++numcomps;
                    build_tree(v, numcomps - 1);
                } else {
                    build_tree(v, comp);
                }
            }
        }
    };

    for (int u = 0; u < szof(g); ++u) {
        if (!visit[u]) {
            tree.push_back(vector<int>());
            assert(szof(tree) - 1 == numcomps);
            ++numcomps;
            build_tree(u, numcomps - 1);
        }
    }
    return tree;
}

pair<int, ii> tree_diameter_with_endpoints(const vector<vector<int>>& tree) {
    int dia = 0;
    ii ends;
    // Returns a pair (distance, vertex) representing the farthest vertex from u
    function<ii(int, int, int)> farthest = [&](int u, int p, int depth) {
        int dist = depth, end = u;
        for (int v : tree[u]) {
            if (v != p) {
                auto res = farthest(v, u, depth + 1);
                if (res.first > dist) {
                    dist = res.first;
                    end = res.second;
                }
            }
        }
        return make_pair(dist, end);
    };
    ends.first = farthest(0, -1, 0).second;
    auto ans = farthest(ends.first, -1, 0);
    ends.second = ans.second;
    dia = ans.first;
    return make_pair(dia, ends);
}

void mmain() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> g(n);
    vector<ii> e(m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &e[i].first, &e[i].second);
        --e[i].first;
        --e[i].second;
        g[e[i].first].push_back(i);
        g[e[i].second].push_back(i);
    }
    auto tree = bridge_tree(g, e);
    int dia = tree_diameter_with_endpoints(tree).first;
    printf("%d\n", dia);
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