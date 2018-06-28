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
const int MAXN = 1e4 + 5;
const ll MOD = 998244353;
int n;
ll a[MAXN], dp[MAXN], fact[MAXN];

inline void clampmod(ll &a, ll mod) {
	a %= mod;
	if (a<0) a+=mod;
}

// calculates (a*b) modulo mod safely
ll mulmod(ll a, ll b, ll mod) {
	clampmod(a,mod); clampmod(b,mod);

	ll res = 0;
	while (b != 0) {
		if (b&1LL) {
			res = (res+a)%mod;
		}
		a = (a*2)%mod;
		b /= 2;
	}
	return res;
}
// x^e mod mod
ll powmod(ll x, ll e, ll mod) {
	if (e==0) {
		return 1LL;
	}
	ll h = powmod(x, e/2, mod);
	if (e%2==0) {
		return mulmod(h,h,mod);
	} else {
		return mulmod(x, mulmod(h,h,mod),mod);
	}
}

ll gcd(ll a, ll b) {
	return b==0 ? a : gcd(b, a%b);
}

// returns the inverse of a mod m or -1 if it doesn't exist
// the code is tested
ll modinverse(ll a, ll m) {
	clampmod(a,m);
	ll bm=1, ba=0, br=m;
	ll cm=0, ca=1, cr=a;
	ll tmpm, tmpa, tmpr, q;
	while (cr!=0) {
		q = br/cr;
		tmpm = bm-cm*q;
		tmpa = ba-ca*q;
		tmpr = br-cr*q;
		bm=cm, ba=ca, br=cr;
		cm=tmpm, ca=tmpa, cr=tmpr;
	}
	if (br!=1) return -1;
	ba = ((ba%m)+m)%m;
	assert((ba*a)%m == 1LL);
	return ba;
}

void computefact() {
    fact[0] = 1LL;
    for (ll i = 1; i < MAXN; ++i) {
        fact[i] = mulmod(i, fact[i-1], MOD);
    }
}

ll choose(ll a, ll b) {
    DEBUG("choose(%lld, %lld)\n", a, b);
    if (a < b) return 0;

    // a choose b
    // fact[a] / fact[b] fact[a-b]
    ll p1 = fact[a];
    // ll p2 = pow(fact[b], MOD - 2);
    ll p2 = modinverse(fact[b], MOD);
    ll p3 = modinverse(fact[a-b], MOD);
    DEBUG("p1 = %lld, p2 = %lld, p3 = %lld\n", p1, p2, p3);
    ll ans = mulmod(p1, mulmod(p2, p3, MOD), MOD);
    // ans = (ans * p3) % MOD;
    return ans;
}

void mmain() {
    computefact();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
    }
    dp[n + 1] = 1LL;
    for (int i = n; i; --i) {
        if (a[i] > 0 && a[i] + i <= n) {
            dp[i] = choose(n-i, a[i]);
            DEBUG("dp[%d] initially %lld\n", i, dp[i]);
            for (int j = i + a[i] + 1; j <= n; ++j) {
                // choose function
                // j - a[i]-1 choose a[i]-1
                ll ch = choose(j - i - 1, a[i]);
                // ch = (ch * dp[j]) % MOD;
                ch = mulmod(ch, dp[j], MOD);
                dp[i] = (dp[i] + ch) % MOD;
            }
        } else {
            dp[i] = 0;
        }
        DEBUG("dp[%d] = %lld\n", i, dp[i]);
    }
    ll cnt = 0;
    for (int i = 1; i <= n; ++i) {
        cnt = (cnt+dp[i])%MOD;
    }
    printf("%lld\n", cnt);
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