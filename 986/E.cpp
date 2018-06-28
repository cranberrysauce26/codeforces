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
const int MAX = 1e5 + 5, MAX_VAL = 1e7 + 1, MOD = 1e9 + 7;

ll powmod(ll x, ll e) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) {
            res = (res * x) % MOD;
        }
        x = (x * x) % MOD;
        e >>= 1;
    }
    return res;
}

struct query_t {
    query_t() : ans(1LL) {}
    int u, v, x;
    ll ans;
} query[MAX];

int n, q, a[MAX];
vector<int> adj[MAX];

int sp[MAX_VAL];

vector<int> primes;
vector<ii> pqueries[MAX_VAL];
vector<ii> pnodes[MAX_VAL];

void sieve() {
    for (int i = 2; i * i < MAX_VAL; ++i) {
        if (sp[i] == 0) {
            sp[i] = i;
            for (int j = i * i; j < MAX_VAL; j += i) {
                sp[j] = i;
            }
        }
    }
}

void factorize(int x, int id, vector<ii>* vec) {
    while (x != 1) {
        int p = sp[x], e = 0;
        if (p == 0) {
            p = x;
        }
        while (x % p == 0) {
            x /= p;
            ++e;
        }
        vec[p].push_back({e, id});
    }
}

void label_primes() {
    for (int i = 1; i <= q; ++i) {
        factorize(query[i].x, i, pqueries);
    }
    for (int i = 1; i <= n; ++i) {
        factorize(a[i], i, pnodes);
    }
    for (int i = 2; i < MAX_VAL; ++i) {
        if (!pqueries[i].empty()) {
            primes.push_back(i);
        }
    }
}

int depth[MAX], par[MAX], enter[MAX], leave[MAX], dfslist[3 * MAX], dfst = 0;

void dfs(int u, int p, int h) {
    depth[u] = h;
    par[u] = p;
    dfslist[++dfst] = u;
    enter[u] = dfst;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, h + 1);
            dfslist[++dfst] = u;
        }
    }
    dfslist[++dfst] = u;
    leave[u] = dfst;
}

int lcatree[12 * MAX];
void lca_build(int u, int tl, int tr) {
    if (tl == tr) {
        lcatree[u] = dfslist[tl];
    } else {
        int tm = (tl + tr) / 2;
        lca_build(2 * u, tl, tm);
        lca_build(2 * u + 1, tm + 1, tr);
        lcatree[u] = depth[lcatree[2 * u]] < depth[lcatree[2 * u + 1]]
                         ? lcatree[2 * u]
                         : lcatree[2 * u + 1];
    }
}
int lca_query(int u, int tl, int tr, int l, int r) {
    if (l <= tl && tr <= r) {
        return lcatree[u];
    }
    int tm = (tl + tr) / 2;
    if (tm + 1 > r) {
        return lca_query(2 * u, tl, tm, l, r);
    } else if (tm < l) {
        return lca_query(2 * u + 1, tm + 1, tr, l, r);
    } else {
        int ansl = lca_query(2 * u, tl, tm, l, r);
        int ansr = lca_query(2 * u + 1, tm + 1, tr, l, r);
        return depth[ansl] < depth[ansr] ? ansl : ansr;
    }
}

ii bit[3 * MAX];

void bitupd(int x, ii v) {
    for (; x < 3 * MAX; x += x & -x) {
        bit[x].first += v.first;
        bit[x].second += v.second;
    }
}

ii bitquery(int x) {
    ii res = {0, 0};
    for (; x; x -= x & -x) {
        res.first += bit[x].first;
        res.second += bit[x].second;
    }
    return res;
}

ii curval[MAX];

ii query_path(int u, int v) {
    int w =
        lca_query(1, 1, dfst, min(enter[u], enter[v]), max(enter[u], enter[v]));
    ii ru = bitquery(enter[u]);
    ii rv = bitquery(enter[v]);
    ii rw = bitquery(enter[w]);
    ii ans = {ru.first + rv.first - 2 * rw.first + curval[w].first,
              ru.second + rv.second - 2 * rw.second + curval[w].second};
    return ans;
}

void update_node(int u, ii val) {
    curval[u].first += val.first;
    curval[u].second += val.second;
    bitupd(enter[u], val);
    bitupd(leave[u], {-val.first, -val.second});
}

void solve(int p) {
    vector<pair<int, ii>> upds;

    sort(allof(pnodes[p]));
    sort(allof(pqueries[p]));

    for (auto pp : pnodes[p]) {
        update_node(pp.second, {0, 1});
        upds.push_back({pp.second, {0, -1}});
    }

    int qi = 0, pi = 0;

    while (qi < szof(pqueries[p])) {
        while (pi < szof(pnodes[p]) &&
               pnodes[p][pi].first < pqueries[p][qi].first) {
            update_node(pnodes[p][pi].second, {pnodes[p][pi].first, -1});
            upds.push_back({pnodes[p][pi].second, {-pnodes[p][pi].first, 1}});
            ++pi;
        }
        int qid = pqueries[p][qi].second;
        ii ans = query_path(query[qid].u, query[qid].v);
        int e = ans.first + pqueries[p][qi].first * ans.second;
        query[qid].ans = (query[qid].ans * powmod(p, e)) % MOD;
        ++qi;
    }

    for (auto pp : upds) {
        update_node(pp.first, pp.second);
    }
}

void mmain() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        scanf("%d%d%d", &query[i].u, &query[i].v, &query[i].x);
    }
    sieve();
    label_primes();
    dfs(1, 0, 0);
    lca_build(1, 1, dfst);
    for (int i = 0; i < szof(primes); ++i) {
        solve(primes[i]);
    }
    for (int i = 1; i <= q; ++i) {
        printf("%lld\n", query[i].ans);
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