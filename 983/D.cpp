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
#ifdef LOCAL
    DEBUG("press: ");
    for (int y : press) {
        DEBUG("%d ", y);
    }
    DEBUG("\n");
#endif
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
        DEBUG("maxcover(u) = %d, minp[2*u] = %d, minp[2*u+1] = %d\n",
              maxcover(u), minp[2 * u], minp[2 * u + 1]);
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
    DEBUG("update(%d, %d, %d, %d, %d, %d), maxunused = %d, minp = %d\n", u, tl,
          tr, l, r, c, maxunused[u], minp[u]);
}

void mark(int u, int tl, int tr, int c) {
    assert(maxunused[u] == c);
    DEBUG("mark(%d, %d, %d, %d)\n", u, tl, tr, c);
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
    memset(maxunused, -1, sizeof maxunused);
    DEBUG("sweeping\n");
    int i = 0;
    while (i < szof(ee)) {
        DEBUG("\nGROUP\n", i, ee[i].c);
        int j = i;
        while (j < szof(ee) && ee[i].x == ee[j].x) {
            update(1, 0, szof(press) - 1, ee[j].y1, ee[j].y2, ee[j].c);
            ++j;
        }
        DEBUG("i = %d, j = %d\n", i, j);

        while (maxunused[1] != -1) {
            int c = maxunused[1];
            used[c] = 1;
            DEBUG("used colour = %d\n", c);
            mark(1, 0, szof(press) - 1, c);
        }
        i = j;
    }
    used[0] = 1;
}

const int GRID_SZ = 100;
int grid[GRID_SZ][GRID_SZ];

void reset() {
    memset(grid, 0, sizeof grid);
    n = 0;
    memset(maxunused, 0, sizeof maxunused);
    memset(minp, 0, sizeof minp);
    for (int i = 0; i < 8 * MAXN; ++i) {
        cover[i].clear();
    }
    memset(used, 0, sizeof used);
    ee.clear();
    press.clear();
}

void mmain() {
    // scanf("%d", &n);
    int TT = 100;
    while (TT--) {
        reset();
        n = 100;
        vector<pair<ii, ii>> input;
        for (int i = 1; i <= n; ++i) {
            int x1, y1, x2, y2;
            // scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1 = rand() % GRID_SZ;
            x2 = rand() % GRID_SZ;

            if (x1 == x2) {
                if (x2 + 1 < GRID_SZ) {
                    ++x2;
                } else {
                    --x1;
                }
            }

            y1 = rand() % GRID_SZ;
            y2 = rand() % GRID_SZ;

            if (y1 == y2) {
                if (y2 + 1 < GRID_SZ) {
                    ++y2;
                } else {
                    --y1;
                }
            }

            int lft, rt, btm, tp;
            lft = min(x1, x2);
            rt = max(x1, x2);
            btm = min(y1, y2);
            tp = max(y1, y2);

            input.push_back({{lft, rt}, {btm, tp}});

            for (int x = lft; x < rt; ++x) {
                for (int y = btm; y < tp; ++y) {
                    grid[x][y] = i;
                }
            }

            ee.push_back({lft, btm, tp, i});
            ee.push_back({rt, btm, tp, -i});
        }
        sort(allof(ee));
        compress();
        sweep();
        int cnt1 = accumulate(used, used + n + 1, 0);

        vector<int> freq(n + 1, 0);

        for (int x = 0; x < GRID_SZ; ++x) {
            for (int y = 0; y < GRID_SZ; ++y) {
                freq[grid[x][y]] = 1;
            }
        }
        int cnt2 = accumulate(allof(freq), 0);
        printf("HELLO\n");
        if (cnt1 != cnt2) {
            printf("WA\n");
            for (auto r : input) {
                printf("lft = %d, rt = %d, btm = %d, tp = %d\n", r.first.first,
                       r.first.second, r.second.first, r.second.second);
            }
            printf("brute force is %d, got %d\n", cnt2, cnt1);
            for (int i = 0; i <= n; ++i) {
                if (used[i]) {
                    assert(used[i] == 1);
                    printf("colour %d is used in sol\n", i);
                }
            }
            return;
        } else {
            printf("AC got %d expected %d\n", cnt1, cnt2);
        }
    }
}

int main() {
#define LOCAL
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

/**
 * Definitions:
 *
 * For each node u in the segment tree:
 *
 * cover[u] := the set of colours such that the colour fully covers the node's
 * interval AND the set of colours do not cover the node's parent's interval.
 *
 * Define an array used[] to indicate whether or not a colour has appeared.
 * used[i] = 0 for each colour i initially.
 *
 * Call a colour c unused if used[c] = 0 and used if used[c] != 0
 *
 * Define maxcover(u) = max(cover[u]) is cover[u] is nonempty and 0 otherwise.
 *
 * Define maxc(p) for a path p to be the maximum of maxcover(v) for all v on
 * p
 *
 * Call a path p unused if maxc(p) is unused
 *
 * Call v a maximum vertex of path p if maxc(p) is in cover[v]
 *
 * Lemma 1: A colour c appears on the array iff there exists a path p with
 * maxc(p) = c
 *
 * For each node u, define maxunused[u] to be the maximum of maxc(p) over all
 * unused paths p starting from u and going to some leaf in the subtree rooted
 * at u, or -1 if no such path exists. maxunused[u] = 0 initially for each u.
 *
 * For each node u, define minp[u] to be the minimum of maxc(p) over all
 * paths p starting from u and going to some leaf in the subtree rooted
 * at u. minp[u] always exists.
 *
 * Lemma 2: maxunused[u] and minunused[u] can be calculated in O(1)
 * Suppose that u has no children. Then maxunused[u] = minunused[u] =
 * maxcover(u) Otherwise u has two children, v1 and v2. Let p be an unused path
 * from u to a leaf in subtree u. Let w be the maximum of p. Note that p has
 * only one maximum. WLOG let the end of the path lie in subtree v1. Then p is
 * simply the maximum unused path from v1 to a leaf in subtree v1 extended up to
 * u. Therefore maxunused[u] = max(max(cover[u]), maxunused[v1]) The same logic
 * applies to v2. Therefore maxunused[u] = max(max(cover[u]), maxunused[v1],
 * maxunused[v2])
 *
 * Lemma 3: add(l, r, c) and remove(l, r, c) can be done in lg^2(n)
 * Consider each node u such that [l, r] contains u's interval.
 * Then we must first add or remove c from cover[u]. Then for each node v on the
 * path from u to the root, recalculate maxunused[v]
 *
 * markused(l, r, c) sets used[c] = 1 and then updates the tree. The
 * precondition is that c is equal to maxunused[root]
 *
 * Lemma 4: markused(l, r, c) can be done in lg(n)
 * Consider each node u such that [l, r] contains u's interval.
 * Assuming the precondition that c = maxunused[root], then maxunused[u] = c.
 * Therefore we set maxunused[u] = -1, and for each parent on the path from u to
 * the root, recalculate maxunused
 *
 * Finally, the algorithm:
 *
 * for each stop in the linesweep
 *      for each event in the stop
 *          if it is the beginning of a rectangle, add it
 *          otherwise remove it
 *      while maxunused[1] != -1
 *          markused(maxunused[1])
 *
 * cnt = 0
 * for each colour
 *      if it is used, increment cnt
 * return cnt
 */