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

const int INF = 1e9 + 69;

void mmain() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<vii> t(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        --u, --v;
        t[u].push_back({w, v});
        t[v].push_back({w, u});
    }
    vii h1(n), h2(n), h3(n);
    function<ii(int, int)> heights = [&](int u, int p) {
        h1[u] = h2[u] = h3[u] = {0, u};
        for (auto e : t[u]) {
            if (e.second != p) {
                auto ans = heights(e.second, u);
                ans.first += e.first;
                ans.second = e.second;
                if (ans >= h1[u]) {
                    h3[u] = h2[u];
                    h2[u] = h1[u];
                    h1[u] = ans;
                } else if (ans >= h2[u]) {
                    h3[u] = h2[u];
                    h2[u] = ans;
                } else if (ans > h3[u]) {
                    h3[u] = ans;
                }
            }
        }
        assert(h1[u] >= h2[u]);
        return h1[u];
    };

    heights(0, -1);

    vi parh(n, 0);
    function<void(int, int)> pheights = [&](int u, int p) {
        for (auto e : t[u]) {
            if (e.second != p) {
                parh[e.second] = max(parh[e.second], e.first + parh[u]);
                if (e.second != h1[u].second) {
                    parh[e.second] = max(parh[e.second], e.first + h1[u].first);
                } else {
                    parh[e.second] = max(parh[e.second], e.first + h2[u].first);
                }
                pheights(e.second, u);
            }
        }
    };

    pheights(0, -1);

    auto works = [&](int d) {
        bool ok = false;
        function<int(int, int)> closest = [&](int u, int p) {
            int d1 = INF, d2 = INF;
            for (auto e : t[u]) {
                if (e.second != p) {
                    int dist = closest(e.second, u) + 1;
                    if (e.second == h1[u].second) {
                        d1 = dist;
                    } else if (e.second == h2[u].second) {
                        d2 = dist;
                    }
                }
            }

            if (h1[u].first <= d) {
                d1 = d2 = 0;
                if (parh[u] <= d) {
                    ok = true;
                }
                return 0;
            } else if (h2[u].first <= d) {
                if (parh[u] <= d && 1 + d1 <= k) {
                    ok = true;
                }
                return d1;
            } else if (h3[u].first <= d) {
                if (parh[u] <= d && 1 + d1 + d2 <= k) {
                    ok = true;
                }
                return INF;
            }
            return INF;
        };
        closest(0, -1);
        return ok;
    };

    int lo = 0, hi = INF;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (works(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    assert(lo == hi);
    printf("%d", lo);
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