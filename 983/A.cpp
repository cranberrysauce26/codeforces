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

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

inline void simplify(ll &p, ll &q) {
    p %= q;
    ll d = gcd(p, q);
    p /= d;
    q /= d;
}

bool finite(ll p, ll q, ll b) {
    simplify(p, q);
    ll d = gcd(q, b);
    while (d != 1) {
        q /= d;
        d = gcd(q, d);
    }
    return q==1;
}

void mmain() {
    int n;
    scanf("%d", &n);
    while (n--) {
        ll p, q, b;
        scanf("%lld %lld %lld", &p, &q, &b);
        if (finite(p, q, b)) {
            printf("Finite\n");
        } else {
            printf("Infinite\n");
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