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

vector<pair<ll, int>> factorize(ll n) {
    vector<pair<ll, int>> ans;
    for (ll f = 2; f * f <= n; ++f) {
        int e = 0;
        while (n % f == 0) {
            n /= f;
            ++e;
        }
        if (e) {
            ans.push_back({f, e});
        }
    }
    if (n != 1) {
        ans.push_back({n, 1});
    }
    return ans;
}

ll l, r, x, y, z;

vector<pair<ll, int>> ff;

ll ans = 0, same = 0;

inline ll ceil(ll a, ll b) {
    return a%b==0 ? a/b : a/b+1;
}

void recurse(int i, ll a) {
    DEBUG("recurse(i = %d, a = %lld)\n", i, a);
    // hi
    if (i==szof(ff)) {
        if (a > r/x) return;
        if (a < ceil(l,x)) return;

        ll b = z/a;
        if (b > r/x) return;
        if (b < ceil(l, x)) return;

        if (gcd(a,b)!=1) return;

        DEBUG("a = %lld, b = %lld\n", a, b);
        ++ans;
    } else {
        for (int e = 0; e <= ff[i].second; ++e) {
            DEBUG("i = %d, prime = %lld, e = %d\n", i, ff[i].first, e);
            recurse(i+1, a);
            a = (a * ff[i].first);
            if (a > r/x) {
                DEBUG("ending a = %lld\n", a);
                return;
            }

        }
    }
}

void mmain() {
    cin >> l >> r >> x >> y;
    if (y % x != 0) {
        cout << "0\n";
        return;
    }

    z = y / x;

    if (z == 1) {
        // only solution is a = b = x
        if (l <= x && x <= r) {
            cout << "1\n";
        } else {
            cout << "0\n";
        }
        return;
    }

    ff = factorize(z);

    DEBUG("z = %lld\n", z);
    recurse(0, 1LL);
    cout << ans << "\n";
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