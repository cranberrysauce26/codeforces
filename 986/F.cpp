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

inline void clampmod(ll &a, ll mod) {
    a %= mod;
    if (a < 0) a += mod;
}

// calculates (a*b) modulo mod safely
ll mulmod(ll a, ll b, ll mod) {
    clampmod(a, mod);
    clampmod(b, mod);

    ll res = 0;
    while (b != 0) {
        if (b & 1LL) {
            res = (res + a) % mod;
        }
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}
// x^e mod mod
ll powmod(ll x, ll e, ll mod) {
    if (e == 0) {
        return 1LL;
    }
    ll h = powmod(x, e / 2, mod);
    if (e % 2 == 0) {
        return mulmod(h, h, mod);
    } else {
        return mulmod(x, mulmod(h, h, mod), mod);
    }
}

struct query_t {
    ll n, k;
    int id;
    bool operator<(const query_t &x) const {
        return k != x.k ? k < x.k : id < x.id;
    }
} query[10004];

bool ans[10004];

vector<ll> allprimes;
const ll HIGH = 31622800;
bitset<HIGH> isprime;
void sieve() {
    isprime.set();
    for (ll i = 2; i * i < HIGH; ++i) {
        if (isprime[i]) {
            for (ll j = i * i; j < HIGH; j += i) {
                isprime[j] = 0;
            }
        }
    }
    for (ll i = 2; i < HIGH; ++i) {
        if (isprime[i]) {
            allprimes.push_back(i);
        }
    }
}

void factorize(ll k, vector<ll> &primes) {
    for (ll p : allprimes) {
        if (p*p > k) {
            break;
        }
        if (k%p==0) {
            while (k%p==0) {
                k/=p;
            }
            primes.push_back(p);
        }
    }
    if (k != 1) {
        primes.push_back(k);
    }
}

int gsz;
vector<pair<ll, int>> g[100005];
ll dist[100005];

void build_graph(const vector<ll> &primes) {
    // primes are sorted
    assert(szof(primes) >= 3);
    gsz = primes[0];
    for (int i = 0; i < gsz; ++i) {
        g[i].clear();
    }
    for (int i = 0; i < gsz; ++i) {
        for (int j = 1; j < szof(primes); ++j) {
            int k = (int) ( (1LL*i + primes[j]) % (1LL*gsz));
            g[i].push_back({primes[j], k});
            g[k].push_back({primes[j], k});
        }
    }
}

void dijkstra(int start) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
        pq;
    pq.push({0, start});
    fill(dist, dist + gsz, numeric_limits<ll>::max());
    dist[start] = 0;
    while (!pq.empty()) {
        int u;
        ll d;
        tie(d, u) = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto e : g[u]) {
            if (dist[e.second] == numeric_limits<ll>::max() ||
                dist[e.second] > e.first + d) {
                dist[e.second] = e.first + d;
                pq.push({dist[e.second], e.second});
            }
        }
    }
}

void mmain() {
    sieve();
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; ++i) {
        scanf("%lld %lld", &query[i].n, &query[i].k);
        query[i].id = i;
    }
    sort(query, query + t);
    int lo = 0, hi = 0;
    while (lo < t) {
        while (hi + 1 < t && query[hi + 1].k == query[lo].k) {
            ++hi;
        }

        ll k = query[lo].k;
        DEBUG("\nk = %lld\n", k);

        if (k == 1) {
            lo = hi + 1;
            continue;
        }

        vector<ll> primes;
        factorize(k, primes);
        if (szof(primes) == 1) {
            DEBUG("Case 1\n");
            for (int i = lo; i <= hi; ++i) {
                if (query[i].n % primes[0] == 0) {
                    ans[query[i].id] = 1;
                }
            }
        } else if (szof(primes) == 2) {
            // ?
            ll p1 = primes[0], p2 = primes[1];
            DEBUG("Case 2, p1 = %lld, p2 = %lld\n", p1, p2);
            for (int i = lo; i <= hi; ++i) {
                if (query[i].n > p1 * p2 - p1 - p2) {
                    ans[query[i].id] = 1;
                } else {
                    ll inv2 = powmod(p2, p1 - 2, p1);
                    assert(mulmod(inv2, p2, p1)==1);
                    ll y0 = mulmod(query[i].n, inv2, p1);
                    assert(query[i].n % p1 == mulmod(p2, y0, p1));
                    ll x0 = (query[i].n - p2 * y0) / p1;
                    assert(x0*p1+y0*p2==query[i].n);
                    DEBUG("x0 = %lld, y0 = %lld\n", x0, y0);
                    if (x0 < 0) {
                        ll toadd =
                            (-x0) % p2 == 0 ? (-x0) / p2 : (-x0) / p2 + 1;
                        x0 += toadd * p2;
                        y0 -= toadd * p1;
                    }
                    if (y0 < 0) {
                        ll toadd =
                            (-y0) % p1 == 0 ? (-y0) / p1 : (-y0) / p1 + 1;
                        y0 += toadd * p1;
                        x0 -= toadd * p2;
                    }

                    if (x0 >= 0 && y0 >= 0) {
                        ans[query[i].id] = 1;
                    }
                }
            }
        } else {
            DEBUG("Case 3\n");
            // build graph
            build_graph(primes);
            dijkstra(0);

            for (int i = lo; i <= hi; ++i) {
                if (query[i].n >= dist[query[i].n % primes[0]]) {
                    ans[query[i].id] = 1;
                }
            }
        }
        lo = hi + 1;
    }

    for (int i = 0; i < t; ++i) {
        if (ans[i]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int main() {
#ifdef LOCAL
    clock_t begin = clock();
    DEBUG("*********Starting program*********\n\n");
    freopen("data.txt", "r", stdin);
#endif
    mmain();
#ifdef LOCAL
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    DEBUG("\nTime taken: %lf\n", elapsed_secs);
#endif
}