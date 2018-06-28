#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define LOCAL
#ifdef LOCAL
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

#define getchar()      \
    (*_pbuf ? *_pbuf++ \
            : (_buf[fread(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;

int read_int() {
    int c, o = 0;
    while ((c = getchar()) < '0')
        ;
    do {
        o = (o << 3) + (o << 1) + (c - '0');
    } while ((c = getchar()) >= '0');
    return o;
}

using namespace std;
#define szof(v) ((int)(v).size())
#define allof(v) begin(v), end(v)
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
const int MAXN = 2e5 + 5;
int n, q;
ll a[MAXN], presum[MAXN], mn[4 * MAXN], mx[4 * MAXN], lzy[4 * MAXN];

void build(int u, int tl, int tr) {
    if (tl == tr) {
        mn[u] = mx[u] = -a[tl] + presum[tl - 1];
    } else {
        build(2 * u, tl, (tl + tr) / 2);
        build(2 * u + 1, (tl + tr) / 2 + 1, tr);
        mn[u] = min(mn[2 * u], mn[2 * u + 1]);
        mx[u] = max(mx[2 * u], mx[2 * u + 1]);
    }
}

void pushdown(int u, int tl, int tr) {
    if (tl != tr) {
        lzy[2 * u] += lzy[u];
        lzy[2 * u + 1] += lzy[u];
        mx[2 * u] += lzy[u];
        mn[2 * u] += lzy[u];
        mx[2 * u + 1] += lzy[u];
        mn[2 * u + 1] += lzy[u];
    }
    lzy[u] = 0;
}

ll query(int u, int tl, int tr, int pos) {
    pushdown(u, tl, tr);
    if (tl == tr) {
        assert(tl == pos);
        assert(mn[u] == mx[u]);
        return mn[u];
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            return query(2 * u, tl, tm, pos);
        } else {
            return query(2 * u + 1, tm + 1, tr, pos);
        }
    }
}

void update(int u, int tl, int tr, int l, int r, ll val) {
    if (l > tr || r < tl) {
        return;
    }
    pushdown(u, tl, tr);
    assert(lzy[u] == 0);
    if (l <= tl && tr <= r) {
        mx[u] += val;
        mn[u] += val;
        lzy[u] = val;
    } else {
        int tm = (tl + tr) / 2;
        update(2 * u, tl, tm, l, r, val);
        update(2 * u + 1, tm + 1, tr, l, r, val);
        mn[u] = min(mn[2 * u], mn[2 * u + 1]);
        mx[u] = max(mx[2 * u], mx[2 * u + 1]);
    }
}

int findzero(int u, int tl, int tr, int l, int r) {
    if (l > tr || r < tl || l > r) {
        return -1;
    }
    if (tl == tr) {
        assert(mn[u] == 0 && mx[u]==0);
        return tl;
    } else {
        pushdown(u, tl, tr);
        int tm = (tl + tr) / 2;
        if (mx[2 * u] >= 0 && mn[2 * u] <= 0) {
            int ansl = findzero(2 * u, tl, tm, l, r);
            if (ansl != -1) {
                return ansl;
            }
        }
        if (mx[2 * u + 1] >= 0 && mn[2 * u + 1] <= 0) {
            int ansr = findzero(2 * u + 1, tm + 1, tr, l, r);
            if (ansr != -1) {
                return ansr;
            }
        }
        return -1;
    }
}

void mmain() {
    scanf("%d%d", &n, &q);
    // n = read_int();
    // q = read_int();
    for (int i = 1; i <= n; ++i) {
        // a[i] = read_int();
        scanf("%d", a + i);
        presum[i] = a[i] + presum[i - 1];
    }
    build(1, 1, n);
    while (q--) {
        int p;
        ll x;
        scanf("%d %lld", &p, &x);
        // p = read_int();
        // x = (ll)read_int();
        ll delta = x - a[p];
        a[p] = x;
        update(1, 1, n, p, p, -delta);
        update(1, 1, n, p + 1, n, delta);
        int ans = -1;
        if (mn[1] <= 0 && 0 <= mx[1]) {
            ans = findzero(1, 1, n, 1, n);
        }
        printf("%d\n", ans);
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