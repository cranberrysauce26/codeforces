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
const int MAXN = 1e5 + 5;
int n;
ll m, a[MAXN];
ll segsum[MAXN];
ll gapsum(int i) { return a[i] - segsum[i]; }

void mmain() {
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
    }
    a[n + 1] = m;
    for (int i = 1; i <= n+1; i += 2) {
        segsum[i] = a[i] - a[i - 1] + segsum[i - 1];
        segsum[i+1] = segsum[i];
        DEBUG("segsum[%d] = %lld, segsum[%d] = %lld\n", i, segsum[i], i+1, segsum[i]);
    }

    ll ans = segsum[n+1];
    DEBUG("initial ans = %lld\n", ans);
    for (int i = 0; i <= n; i += 2) {
        // try at beginning of a[i]

        if (a[i] + 1 == a[i + 1]) continue;

        ll test1 = segsum[i] + (a[i + 1] - a[i] - 1) + gapsum(n + 1) - gapsum(i+1);
        DEBUG("i = %d, test1 = %lld\n", i, test1);
        // ll test2 = segsum[i] + (a[i+1]-)
        ans = max(ans, test1);
    }
    for (int i = 1; i <= n; i += 2) {
        if (a[i] + 1 == a[i + 1]) continue;
        ll test2 = segsum[i] + (a[i + 1] - a[i] - 1) + gapsum(n + 1) - gapsum(i+1);
        DEBUG("i = %d, test2 = %lld\n", i, test2);
        ans = max(ans, test2);
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