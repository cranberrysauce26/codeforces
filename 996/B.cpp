#pragma GCC optimize("O3")
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
typedef vector<int> vi;
const int MAXN = 1e5+5;
int n;
ll a[MAXN];

inline ll ceil(ll a, ll b) {
    if (a < 0) {
        return a/b;
    }
    return a%b==0 ? a/b : a/b+1;
}
void mmain() {
    scanf("%d", &n);
    ll ans = numeric_limits<ll>::max();
    int mini = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%lld", a+i);
        ll tr = 1LL*ceil(a[i]-i, n)*n + i;
        DEBUG("tr for i = %d, a[i] = %lld is %lld\n", i, a[i], tr);
        if (tr < ans) {
            ans = tr;
            mini = i+1;
        }
    }
    cout << mini << "\n";
}
#define LOCAL
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