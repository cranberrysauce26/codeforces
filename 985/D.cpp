/*input
15 5
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

ll n, h;

ll case1() {
	ld nn = n, hh = h;

	ld bound = hh;

	ld bound2 = (sqrt(nn*8+1)-1)/2;
	bound = min(bound, bound2);

	ld target = sqrt(nn*2);

	if (target < bound+1e-6) {
		ld p = floor(target);
		ll toret= (ll)ceil(nn/p+p/2-0.5);
		return toret;
	}

	ld p = floor(bound);
	ld ans = ceil(nn/p+p/2-0.5);
	ll toret= (ll)min(ans, nn);
	return toret;
}

ll case2() {
	ld nn = n, hh = h;

	if (nn-hh*(hh+1)*ld(0.5) < 0.5) return -1LL;

	ld arg = nn+hh*(hh-1)*ld(0.5);

	ld target = sqrt(arg);

	if (target <= hh) {
		return -1LL;
	}

	ld p1 = floor(target);

	ld ans1 = ceil(arg/p1+p1-hh);

	ld p2 = ceil(target);

	ld ans2 = ceil(arg/p2+p2-hh);

	ll toret= (ll)min(ans1, ans2);
	return toret;
}

int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n >> h;

	if (n==0) {
		cout << "0\n";
		return 0;
	}

	if (h==0) {
		cout << "IMPOSSIBLE\n";
		return 0;
	}

	ll ans1 = case1();
	ll ans2 = case2();

	if (ans2!=-1) {
		ans1 = min(ans1, ans2);
	}
	cout << ans1 << "\n";
}