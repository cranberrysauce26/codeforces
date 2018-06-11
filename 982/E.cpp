/*input
10 10 10 1 -1 0
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

ll w, h, x, y, vx, vy;

ll mulmod(ll a, ll b, ll mod) {
	a %= mod;
	if (a < 0) a += mod;
	b %= mod;
	if (b < 0) b += mod;

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

ll gcd(ll a, ll b) {
	return b==0 ? a : gcd(b, a%b);
}

ll inv(ll a, ll m) {
	a %= m;
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
	return ba;
}

ll chinese(ll a1, ll m1, ll a2, ll m2) {
	ll z1 = inv(m2, m1);
	ll z2 = inv(m1, m2);
	const ll mod = m1*m2;

	ll ans1 = mulmod(a1, mulmod(m2, z1, mod), mod);
	ll ans2 = mulmod(a2, mulmod(m1, z2, mod), mod);

	ll ans = (ans1+ans2)%mod;
	return ans;
}


ll solve() {
	// t = -vx * x (mod w)
	// t = -vy * y (mod h)

	ll a1 = (-vx*x+w)%w;
	ll a2 = (-vy*y+h)%h;

	assert(a1 >= 0);
	assert(a2 >= 0);

	ll modgcd = gcd(w,h);

	assert(w%modgcd==0);
	assert(h%modgcd ==0);

	if (modgcd == 1LL) {
		ll ans= chinese(a1, w, a2, h);
		assert(ans%w == a1 && ans%h==a2);
		return ans;
	} else {
		if (a1 % modgcd != a2 % modgcd) {
			return -1LL;
		}
		ll ww = w, hh = h;
		if (gcd(ww/modgcd, h)==1) {
			ww /= modgcd;
		} else if (gcd(hh/modgcd, w)==1) {
			hh/=modgcd;
		} else {
			cout << "Impossible\n";
			assert(false);
		}
		ll ans= chinese(a1, ww, a2, hh);
		assert(ans!=-1);
		assert(ans%w == a1 && ans%h==a2);
		return ans;
	}
}

ll crosses(ll x, ll T, ll vx, ll w) {
	ll ncross = 0;
	if (x==0) {
		if (vx==-1) ncross=1;
	} else if (x==w) {
		if (vx==1) ncross=1;
	}
	assert( (x+vx*T)%w == 0);
	if (vx==1) {
		ll high = (T+x)/w - 1;
		ll low = x/w+1;
		ncross += high-low+1;
	} else if (vx==-1) {
		ll low = (x-T)/w+1;
		ll high = x%w==0 ? x/w-1 : x/w;
		ncross += high-low+1;
	}
	return ncross;
}

int main() {
	// freopen("data.txt", "r", stdin);
	cin >> w >> h >> x >> y >> vx >> vy;

	if (x%w==0 && y%h==0) {
		cout << x << " " << y << "\n";
		return 0;
	}

	if (vx==0 && vy==0) {
		cout << "-1\n";
		return 0;
	}

	if (vx==0) {
		if (x%w!=0) {
			cout << "-1\n";
		} else {
			if (vy == 1) {
				cout << x << " " << h << "\n";
			} else {
				cout << x << " 0\n";
			}
		}
		return 0;
	}

	if (vy==0) {
		if (y%h!=0) {
			cout << "-1\n";
		} else {
			if (vx==1) {
				cout << w << " " << y << "\n";
			} else {
				cout << "0 " << y << "\n";
			}
		}
		return 0;
	}

	assert(vx!=0 && vy!=0);

	ll T = solve();
	if (T==-1) {
		cout << "-1\n";
		return 0;
	}
	assert(T >= 0);
	
	ll xcross = crosses(x,T,vx, w);
	ll newvx = (xcross%2==0) ? vx : -vx;

	ll ycross = crosses(y,T,vy, h);
	ll newvy = (ycross%2==0) ? vy : -vy;

	if (newvx==1) cout << w << " ";
	else if (newvx==-1) cout << "0 ";

	if (newvy==1) cout << h;
	else if (newvy==-1) cout << "0";

	return 0;
}
