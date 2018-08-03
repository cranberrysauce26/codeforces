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
template <typename T>
using minheap = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxheap = priority_queue<T>;
const int MAXN = 3e5 + 5;
int n, a[MAXN];

void mmain() {
    ll x, y;
    scanf("%d%lld%lld", &n, &x, &y);
    a[0] = 1;
    int nregions = 0;
    for (int i = 1; i <= n; ++i) {
        char c;
        scanf(" %c", &c);
        a[i] = c == '1' ? 1 : 0;
        DEBUG("a[%d] = %d, a[i-1] = %d\n", i, a[i], a[i - 1]);
        if (a[i] == 0 && a[i - 1] == 1) {
            ++nregions;
        }
    }
    DEBUG("nregions = %d\n", nregions);
    if (nregions == 0) {
        printf("0\n");
        return;
    }
    ll ans;
    if (y <= x) {
        // just flip everything
        ans = y * nregions;
    } else {
        // reverse
        ans = x * (nregions - 1) + y;
    }

    printf("%lld\n", ans);
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