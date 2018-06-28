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
int n, k, a[MAXN], nxt[MAXN], pre[MAXN];
ll cnt = 0;

ll countways(ll a, ll b, ll c) {
    // 0 <= k <= a
    // 0 <= k <= c
    // 0 <= c-k <= b ===> k <= c and k >= c-b
    ll ans = min(a, c) - max(c - b, 0LL) + 1;
    DEBUG("countways(%lld, %lld, %lld) = %lld\n", a, b, c, ans);
    return max(ans, 0LL);
}

void mmain() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = n; i >= 0; --i) {
        if (a[i + 1] != 1) {
            nxt[i] = i + 1;
        } else {
            nxt[i] = nxt[i + 1];
        }
        pre[nxt[i]] = i;
    }
    int i = nxt[0];
    if (i == n + 1) {
        if (k != 1) {
            printf("0\n");
        } else {
            printf("%d\n", n);
        }
        return;
    }

    if (k == 1) {
        for (int i = 1; i <= n; ++i) {
            if (a[i] == 1) {
                ++cnt;
            }
        }
    }

    while (i <= n) {
        // DEBUG("i = %d\n", i);
        assert(a[i] != 1);
        int prezeroes = i - pre[i] - 1;
        // ll prod = a[i], sum = a[i];
        double prod = a[i], sum = a[i];

        int j = i;
        int nsteps = 0;
        while (j <= n && prod <= (sum + n - j + prezeroes) * k) {
            int extra = prezeroes + nxt[j] - j - 1;
            // DEBUG("j = %d, prod = %lld, sum = %lld, extra = %d\n", j, prod,
            // sum,
            //   extra);
            // if (prod % k == 0) {
            ll z = prod / k - sum;
            if (abs(z - round(z)) < 1e-6) {
                // DEBUG("z = %lf\n", z);
                if (0 <= z && z <= extra) {
                    cnt += countways(prezeroes, extra - prezeroes, z);
                }
            }
            // }

            j = nxt[j];
            prod *= a[j];
            // DEBUG("old sum = %lld\n", sum);
            sum += a[j] + nxt[j] - j - 1;
            // DEBUG("just multiplied sum = %lld, added %lld, prod =
            // %lld\n", sum, a[j] + nxt[j] - j - 1, prod);
            ++nsteps;
        }
        assert(nsteps < 100);
        i = nxt[i];
    }
    printf("%d\n", cnt);
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