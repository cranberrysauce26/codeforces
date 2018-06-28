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
const int MAXN = 2e5 + 5, SQRT = 500;
int n, q;
ll presum[MAXN], a[MAXN];
ll shift[MAXN];
unordered_map<ll, unordered_set<int>> histogram[MAXN];
int maxbucket = 0;

ll bit[MAXN];

void update(int x, ll v) {
    for (; x < MAXN; x += x & -x) {
        bit[x] += v;
    }
}

ll sum(int x) {
    ll res = 0;
    for (; x; x -= x & -x) {
        res += bit[x];
    }
    return res;
}

void mmain() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        presum[i] = a[i] + presum[i - 1];
        update(i, a[i]);
    }

    maxbucket = n / SQRT;

    for (int i = 1; i <= n; ++i) {
        int bucket = i / SQRT;
        histogram[bucket][a[i] - presum[i - 1]].insert(i);
    }
    int certain_no_work = 0;
    int lowest_works = n+1;
    while (q--) {
        // int at = query(1, 1, n);
        int p;
        ll x;
        scanf("%d%lld", &p, &x);
        int cb = p / SQRT;
        DEBUG("cb = %d\n", cb);

        ll delta = x - a[p];
        a[p] = x;
        update(p, delta);

        DEBUG("p = %d, x = %lld, delta = %lld\n", p, x, delta);
        for (int b = cb + 1; b <= maxbucket; ++b) {
            shift[b] -= delta;
        }
        // update cb

        {
            ll sumbelow = sum(p - 1);
            ll oldv = a[p] - delta - sumbelow;
            histogram[cb][oldv - shift[cb]].erase(p);
            histogram[cb][a[p] - sumbelow - shift[cb]].insert(p);
        }

        for (int i = p + 1; i < (cb + 1) * SQRT; ++i) {
            ll val = a[i] - sum(i - 1) - shift[cb];
            // DEBUG("i = %d, erasing from val = %lld, inserting to val =
            // %lld\n",i, val+delta, val);
            histogram[cb][val + delta].erase(i);
            histogram[cb][val].insert(i);
        }

        if (cb <= certain_no_work) {
            certain_no_work = cb - 1;
        }

        if (lowest_works < p) {
            printf("%d\n", lowest_works);
            continue;
        } else {
            lowest_works = n+1;
        }

        // query
        bool found = false;
        for (int b = certain_no_work+1; b <= maxbucket && !found; ++b) {
            if (!histogram[b][-shift[b]].empty()) {
                DEBUG("found with hist vla = %lld\n", -shift[b]);
                found = true;
                lowest_works = *begin(histogram[b][-shift[b]]);
                printf("%d\n", *begin(histogram[b][-shift[b]]));
            } else {
                certain_no_work = b;
            }
        }

        if (!found) {
            printf("-1\n");
        }
    }
}
#define LOCAL
int main() {
#ifdef LOCAL
    clock_t begin = clock();
    printf("*********Starting program*********\n\n");
    freopen("data.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    mmain();
#ifdef LOCAL
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime taken: %lf\n", elapsed_secs);
#endif
}