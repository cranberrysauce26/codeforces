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
ll n;

bool is_square(ll x) {
    if (x<=0) return false;
    double sqroot = sqrt(double(x));
    ll flr = (ll)sqroot;
    return flr*flr==x || (flr+1)*(flr+1)==x;
}

void mmain() {
    cin >> n;
    vector<int> dig;
    ll tmp = n;
    while (tmp != 0) {
        dig.push_back(tmp%10);
        tmp /= 10;
    }
    int ndig = szof(dig);
    for (int i = 0; i < ndig; ++i) {
        DEBUG("dig[%d] = %d\n", i, dig[i]);
    }
    int ans = -1;
    for (int mask = 0; mask < (1<<ndig); ++mask) {
        // remove it
        ll x = 0, pp = 1;
        int cnt = 0;
        int last = -1;
        for (int i = 0; i < ndig; ++i) {
            if (mask & (1<<i)) {
                ++cnt;
                // you remove i
                // do nothing
            } else {
                x += pp * dig[i];
                pp *= 10LL;
                last = dig[i];
            }
        }

        if (is_square(x) && last != 0) {
            DEBUG("x = %lld\n", x);
            if (ans==-1) {
                ans = cnt;
            } else {
                ans = min(ans, cnt);
            }
        }
    }
    printf("%d\n", ans);
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