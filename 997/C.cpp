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

const ll MOD = 998244353;

// // x^e mod mod
ll powmod(ll x, ll e, ll mod = MOD) {
    if (e == 0) {
        return 1LL;
    }
    ll h = powmod(x, e / 2, mod);
    if (e % 2 == 0) {
        return (h * h) % mod;
    } else {
        return (x * ((h * h) % MOD)) % MOD;
    }
}

// returns the inverse of a mod m or -1 if it doesn't exist
// the code is tested
ll modinverse(ll a, ll m = MOD) {
    a = (a % m + m) % m;
    ll bm = 1, ba = 0, br = m;
    ll cm = 0, ca = 1, cr = a;
    ll tmpm, tmpa, tmpr, q;
    while (cr != 0) {
        q = br / cr;
        tmpm = bm - cm * q;
        tmpa = ba - ca * q;
        tmpr = br - cr * q;
        bm = cm, ba = ca, br = cr;
        cm = tmpm, ca = tmpa, cr = tmpr;
    }
    if (br != 1) return -1;
    ba = ((ba % m) + m) % m;
    assert((ba * a) % m == 1LL);
    return ba;
}

vector<ll> facts;
void compute_fact(int n, ll mod = MOD) {
    facts.resize(n + 1);
    facts[0] = 1LL;
    for (int i = 1; i <= n; ++i) {
        facts[i] = (facts[i - 1] * i) % mod;
    }
}

inline ll choose(int n, int k) {
    return (facts[n] *
            ((modinverse(facts[k]) * modinverse(facts[n - k])) % MOD)) %
           MOD;
}

void mmain() {
    ll n;
    cin >> n;
    compute_fact((int)n);
    ll intersection = 0;
    ll inv3 = modinverse(3);
    ll pow3 = powmod(3, n);
    ll single = 2LL * (powmod(pow3, n) - powmod(pow3 - 3LL, n));
    for (ll i = 1; i <= n; ++i) {
        pow3 = (pow3 * inv3) % MOD;
        ll f = 3LL * choose((int)n, (int)i) *
               (powmod(pow3, n) - powmod(pow3 - 1LL, n));
        if (i % 2 == 1)
            intersection += f;
        else
            intersection -= f;
        intersection %= MOD;
    }
    cout << ((single - intersection) % MOD + MOD) % MOD << "\n";
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