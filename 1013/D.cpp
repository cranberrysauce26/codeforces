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
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
template <typename T>
using minheap = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxheap = priority_queue<T>;

struct rect {
    int r1, r2, c1, c2, cost;
    rect() : r1(0), r2(0), c1(0), c2(0), cost(0) {}
    void add(ii pnt) {
        DEBUG("add (%d, %d) call cost = %d\n", pnt.first, pnt.second, cost);
        int r = pnt.first, c = pnt.second;
        assert(c >= c2);
        if (c1 == 0) {
            assert(r1 == r2 && c1 == c2 && r1 == 0);
            r1 = r2 = r;
            c1 = c2 = c;
            return;
        }
        if (r1 <= r && r <= r2 && c1 <= c && c <= c2) {
            return;
        }
        if (r1 <= r && r <= r2) {
            cost += c2 - c - 1;
            c2 = c;
            return;
        }
        if (r < r1) {
            cost += r1 - r - 1;
            r1 = r;
        } else {
            assert(r > r2);
            cost += r - r2 - 1;
            r2 = r;
        }
        cost += c - c2;
        c2 = c;
    }
    void frame(int n, int m) {
        DEBUG(
            "In frame before cost is %d, r1 = %d, r2 = %d, c1 = %d, c2 = %d\n",
            cost, r1, r2, c1, c2);
        auto contrib = [](int a, int b) {
            if (a != 0 && b != 0) return a + b - 1;
            return 0;
        };
        cost += 1;
        // upper left
        cost += contrib(c1 - 1, r1 - 1);
        // upper right
        cost += contrib(m - c2, r1 - 1);
        // lower left
        cost += contrib(c1 - 1, n - r2);
        // lower right
        cost += contrib(m - c2, n - r2);
    }
};

void mmain() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    vii p(q);
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &p[i].first, &p[i].second);
    }
    // sort left to right by column, then up to down
    sort(allof(p), [&](const ii &a, const ii &b) {
        return a.second != b.second ? a.second < b.second : a.first < b.first;
    });
    rect r;
    for (auto pnt : p) {
        r.add(pnt);
    }
    r.frame(n, m);
    printf("%d\n", r.cost);
    // Reread the problem statement!
    // Check base cases! Does it work for n = 1?
    // Check for integer overflow! Are you using int instead of ll?
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