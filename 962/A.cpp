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
const int MAXN = 2e5 + 5;
int n;
ll a[MAXN], sum[MAXN];

void mmain() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
        sum[i] = a[i] + sum[i - 1];
    }
    for (int i = 1; i <= n; ++i) {
        if (sum[i] >= sum[n]-sum[i]) {
            printf("%d\n", i);
            return;
        }
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