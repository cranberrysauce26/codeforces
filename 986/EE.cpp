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
const int MAX = 1e5 + 5, MAX_VAL = 1e7 + 1, MOD = 1e9 + 7;

ll powmod(ll x, ll e) {
    if (e == 0) {
        return 1LL;
    }
    ll h = powmod(x, e / 2);
    if (e % 2 == 0) {
        return (h * h) % MOD;
    } else {
        return (((h * h) % MOD) * x) % MOD;
    }
}

struct bit {
    vector<ll> b;
    bit() {}
    bit(int N) { b = vector<ll>(N + 5); }
    ll sum(int x) {
        ll res = 0;
        for (; x; x -= x & -x)
            res += b[x];
        return res;
    }
    ll sum(int l, int r) { return sum(r) - sum(l - 1); }
    void update(int x, ll v) {
        for (; x < szof(b); x += x & -x)
            b[x] += v;
    }

    void reset() { fill(b.begin(), b.end(), 0); }
};

struct query_t {
    query_t() : ans(1LL) {}
    int u, v, x;
    ll ans;
    vector<ii> f;
} query[MAX];

int n, q, a[MAX];
vector<int> adj[MAX];

int sp[MAX_VAL];

vector<int> primes;
vector<ii> pqueries[MAX_VAL];
vector<ii> pnodes[MAX_VAL];

void sieve() {
    DEBUG("Starting sieve\n");
    for (int i = 2; i * i < MAX_VAL; ++i) {
        if (sp[i] == 0) {
            sp[i] = i;
            for (int j = i * i; j < MAX_VAL; j += i) {
                sp[j] = i;
            }
        }
    }
    DEBUG("Finished sieve\n");
}

void factorize(int x, int id, vector<ii> *vec) {
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
    DEBUG("Starting label_primes\n");
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
    DEBUG("Finished label_primes\n");
}

/** HLD */

int depth[MAX], heavy[MAX], treesz[MAX], par[MAX];
void dfs(int u) {
    heavy[u] = -1;
    treesz[u] = 1;
    for (int v : adj[u]) {
        if (v != par[u]) {
            depth[v] = 1 + depth[u];
            par[v] = u;
            dfs(v);
            treesz[u] += treesz[v];
            if (heavy[u] == -1 || treesz[v] > treesz[heavy[u]]) {
                heavy[u] = v;
            }
        }
    }
}

int top[MAX], hldid[MAX], chainsz[MAX], hldnum = 0;
void hld_init(int u) {
    hldid[u] = ++hldnum;
    ++chainsz[top[u]];
    DEBUG("top[%d] = %d, hldid[%d] = %d\n", u, top[u], u, hldid[u]);
    for (int v : adj[u]) {
        if (v != par[u]) {
            if (v != heavy[u]) {
                top[v] = v;
                hld_init(v);
            } else {
                top[v] = top[u];
                hld_init(v);
            }
        }
    }
}

bit bit1, bit2;

void hld_update(int u, int val1, int val2) {
    DEBUG("hld_update(%d, %d, %d)\n", u, val1, val2);
    int lo = hldid[top[u]];
    int hi = hldid[u];
    if (val1 != 0) {
        bit1.update(lo, val1);
        bit1.update(hi + 1, -val1);
    }
    if (val2 != 0) {
        bit2.update(lo, val2);
        bit2.update(hi + 1, -val2);
    }
    u = top[par[top[u]]];
    while (u) {
        // chainsum1[u] += val1 * chainsz[u];
        // chainsum2[u] += val2 * chainsz[u];
        if (val1 != 0) {
            bit1.update(hldid[u], val1);
            bit1.update(hldid[u] + chainsz[u], -val1);
        }
        if (val2 != 0) {
            bit2.update(hldid[u], val2);
            bit2.update(hldid[u] + chainsz[u], -val2);
        }
        u = top[par[u]];
    }
}

inline ii count_between(int u) {
    int lo = hldid[top[u]];
    int hi = hldid[u];
    if (hi == lo + chainsz[top[u]] - 1) {
        return {bit1.sum(lo), bit2.sum(lo)};
    }
    return {bit1.sum(lo)-bit1.sum(hi+1), bit2.sum(lo)-bit2.sum(hi+1)};
}

ii hld_query(int u, int v) {
    ii res = {0, 0};
    while (top[u] != top[v]) {
        if (depth[top[u]] > depth[top[v]]) {
            ii toadd = count_between(u);
            res.first += toadd.first;
            res.second += toadd.second;
            u = par[top[u]];
        } else {
            ii toadd = count_between(v);
            res.first += toadd.first;
            res.second += toadd.second;
            v = par[top[v]];
        }
    }
    int lo = hldid[u], hi = hldid[v];
    if (lo > hi) {
        swap(lo, hi);
    }
    DEBUG("query(u = %d, v = %d) res = {%d, %d}\n", u, v, res.first,
          res.second);
    if (hi == hldid[top[u]] + chainsz[top[u]] - 1) {
        res.first += bit1.sum(lo);
        res.second += bit2.sum(lo);
    } else {
        res.first += bit1.sum(lo) - bit1.sum(hi + 1);
        res.second += bit2.sum(lo) - bit2.sum(hi + 1);
    }
    return res;
}

void solve(int p) {
    sort(allof(pnodes[p]));
    sort(allof(pqueries[p]));
    DEBUG("solving p = %d. Active nodes: ", p);
    for (auto pp : pnodes[p]) {
        DEBUG("(e = %d, u = %d) ", pp.first, pp.second);
    }
    DEBUG("\nQueries are: ");
    for (auto pp : pqueries[p]) {
        DEBUG("(e = %d, id = %d) ", pp.first, pp.second);
    }
    DEBUG("\n");

    for (auto pp : pnodes[p]) {
        hld_update(pp.second, 0, 1);
    }

    int qi = 0, pi = 0;

    while (qi < szof(pqueries[p])) {
        while (pi < szof(pnodes[p]) &&
               pnodes[p][pi].first < pqueries[p][qi].first) {
            hld_update(pnodes[p][pi].second, pnodes[p][pi].first, -1);
            ++pi;
        }
        int qid = pqueries[p][qi].second;
        ii ans = hld_query(query[qid].u, query[qid].v);
        int e = ans.first + pqueries[p][qi].first * ans.second;
        query[qid].ans = (query[qid].ans * powmod(p, e)) % MOD;
        DEBUG("p = %d, qid = %d, u = %d, v = %d, EXP = %d, query = (%d, %d), "
              "ans now %d\n",
              p, qid, query[qid].u, query[qid].v, e, ans.first, ans.second,
              query[qid].ans);
        ++qi;
    }
    // reset
    qi = 0, pi = 0;
    while (qi < szof(pqueries[p])) {
        while (pi < szof(pnodes[p]) &&
               pnodes[p][pi].first < pqueries[p][qi].first) {
            hld_update(pnodes[p][pi].second, -pnodes[p][pi].first, 1);
            ++pi;
        }
        ++qi;
    }

    for (auto pp : pnodes[p]) {
        hld_update(pp.second, 0, -1);
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
    DEBUG("Finished input\n");
    sieve();
    label_primes();
    dfs(1);
    DEBUG("Finished dfs\n");
    top[1] = 1;
    hld_init(1);
    DEBUG("Finished hld_init\n");
    bit1 = bit(n), bit2 = bit(n);
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
    DEBUG("*********Starting program*********\n\n");
    freopen("data.txt", "r", stdin);
#endif
    mmain();
    // bit b = bit(4);
    // b.update(1, 1);
    // b.update(2, -1);
    // b.update(1, 1);
    // b.update(3, -1);

    // printf("%d\n", b.sum(1,2));
#ifdef LOCAL
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    DEBUG("\nTime taken: %lf\n", elapsed_secs);
#endif
}