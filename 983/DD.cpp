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
const int MAXN = 1e5 + 5, INF = 1e9;

struct event {
    int x, y1, y2, c;
    bool operator<(const event& e) const {
        return x != e.x ? x < e.x : c < e.c;
    }
};

int n, used[MAXN];
vector<event> ee;
vector<int> press;

void compress() {
    for (auto e : ee) {
        press.push_back(e.y1);
        press.push_back(e.y2);
    }
    sort(allof(press));
    press.erase(unique(allof(press)), end(press));
    for (auto& e : ee) {
        e.y1 = lower_bound(allof(press), e.y1) - begin(press);
        e.y2 = lower_bound(allof(press), e.y2) - begin(press);
        --e.y2;
    }
}

int maxunused[8 * MAXN], minp[8 * MAXN];
set<int> cover[8 * MAXN];

inline int maxcover(int u) {
    return cover[u].empty() ? 0 : *(cover[u].crbegin());
}

void recalculate(int u, int tl, int tr) {
    // max
    if (tl == tr) {
        maxunused[u] = minp[u] = maxcover(u);
    } else {
        int mxl = -1, mxr = -1, mxself = -1;
        if (maxcover(u) <= maxunused[2 * u]) {
            mxl = maxunused[2 * u];
        }
        if (maxcover(u) <= maxunused[2 * u + 1]) {
            mxr = maxunused[2 * u + 1];
        }
        if (!used[maxcover(u)] &&
            (maxcover(u) >= minp[2 * u + 1] || maxcover(u) >= minp[2 * u])) {
            mxself = maxcover(u);
        }

        maxunused[u] = max(mxself, max(mxl, mxr));
        int mnl = INF, mnr = INF, mnself = INF;
        if (maxcover(u) <= minp[2 * u]) {
            mnl = minp[2 * u];
        }
        if (maxcover(u) <= minp[2 * u + 1]) {
            mnr = minp[2 * u + 1];
        }
        if (maxcover(u) >= minp[2 * u] || maxcover(u) >= minp[2 * u + 1]) {
            mnself = maxcover(u);
        }

        minp[u] = min(mnself, min(mnr, mnl));
        assert(minp[u] != INF);
    }
}

void update(int u, int tl, int tr, int l, int r, int c) {
    if (tl > r || tr < l) {
        return;
    }

    if (l <= tl && tr <= r) {
        if (c > 0) {
            cover[u].insert(c);
        } else {
            cover[u].erase(-c);
        }
        recalculate(u, tl, tr);
    } else {
        int tm = (tl + tr) / 2;
        update(2 * u, tl, tm, l, r, c);
        update(2 * u + 1, tm + 1, tr, l, r, c);
        recalculate(u, tl, tr);
    }
}

void mark(int u, int tl, int tr, int c) {
    assert(maxunused[u] == c);
    if (maxcover(u) == c) {
        maxunused[u] = -1;
    } else {
        int tm = (tl + tr) / 2;
        assert(maxunused[2 * u] <= c);
        if (maxunused[2 * u] == c) {
            mark(2 * u, tl, tm, c);
        }
        assert(maxunused[2 * u + 1] <= c);
        if (maxunused[2 * u + 1] == c) {
            mark(2 * u + 1, tm + 1, tr, c);
        }
        recalculate(u, tl, tr);
    }
}

void sweep() {
    int i = 0;
    while (i < szof(ee)) {
        int j = i;
        while (j < szof(ee) && ee[i].x == ee[j].x) {
            update(1, 0, szof(press) - 1, ee[j].y1, ee[j].y2, ee[j].c);
            ++j;
        }
        while (maxunused[1] != -1) {
            int c = maxunused[1];
            used[c] = 1;
            mark(1, 0, szof(press) - 1, c);
        }
        i = j;
    }
    used[0] = 1;
}

void mmain() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int lft, rt, btm, tp;
        lft = min(x1, x2);
        rt = max(x1, x2);
        btm = min(y1, y2);
        tp = max(y1, y2);
        ee.push_back({lft, btm, tp, i});
        ee.push_back({rt, btm, tp, -i});
    }
    sort(allof(ee));
    compress();
    sweep();
    printf("%d\n", accumulate(used, used + n + 1, 0));
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