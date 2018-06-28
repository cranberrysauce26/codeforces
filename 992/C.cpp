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

const ll MOD = 1e9+7;


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

void mmain() {
    ll x, k;
    cin >> x >> k;
    if (x==0) {
        cout << "0\n";
        return;
    }
    ll twok = powmod(2,k,MOD);
    ll twokk = powmod(2,k+1,MOD);
    clampmod(x, MOD);
    ll ans = mulmod(twokk, x, MOD) - twok + 1LL;
    clampmod(ans, MOD);
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