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
const int MAXN = 1e5+5;

struct knight {
    int id;
    ll c, p;
    bool operator<(const knight& k) const {
        return p < k.p;
    }
} kk[MAXN];

int n, k;
ll ans[MAXN];

void mmain() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &kk[i].p);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &kk[i].c);
        kk[i].id = i;
    }
    if (k==0) {
        for (int i = 1; i <= n; ++i) {
            printf("%lld ", kk[i].c);
        }
        printf("\n");
        return;
    }
    sort(kk+1, kk+1+n);
    multiset<ll> best;
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        DEBUG("i = %d\n", i);
        ans[kk[i].id] = sum + kk[i].c;
        if (szof(best) < k) {
            sum += kk[i].c;
            best.insert(kk[i].c);
        } else {
            ll lowest = *best.begin();
            if (kk[i].c > lowest) {
                sum += kk[i].c-lowest;
                best.erase(best.begin());
                best.insert(kk[i].c);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
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