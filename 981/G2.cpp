/*input
8 5
1 8 8 3
1 1 8 3
1 6 8 3
1 7 8 2
2 8 8
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int,int>;

const ll MOD = 998244353;
const int MAXN = 2e5+5;

struct equation {
	equation(ll _a, ll _b) : a(_a%MOD), b(_b%MOD) {}
	equation() : a(1), b(0) {}
	ll a, b;
	bool active() const {
		return a!=1 || b!=0;
	}
	ll eval(ll x, ll y) const {
		return ((a*x)%MOD+(b*y)%MOD)%MOD;
	}
	equation combine(equation e) const {
		return equation((a*e.a)%MOD, (a*e.b+b)%MOD);
	}
};

struct node {
	ll sz;
	equation lzy;
} seg[4*MAXN];

void pushdown(int u, int tl, int tr) {
	int tm = (tl+tr)/2;
	seg[2*u].sz = seg[u].lzy.eval(seg[2*u].sz, tm-tl+1);
	seg[2*u].lzy = seg[u].lzy.combine(seg[2*u].lzy);
	seg[2*u+1].sz = seg[u].lzy.eval(seg[2*u+1].sz, tr-tm);
	seg[2*u+1].lzy = seg[u].lzy.combine(seg[2*u+1].lzy);
	seg[u].lzy = equation();
}

void update(int u, int tl, int tr, int l, int r, bool contains) {
	if (l > tr || r < tl || l > r) return;

	if (tl!=tr && seg[u].lzy.active()) {
		pushdown(u, tl, tr);
	}
	if (l <= tl && tr <= r) {
		if (contains) {
			seg[u].sz = (seg[u].sz*2LL)%MOD;
			seg[u].lzy = equation(2, 0);
		} else {
			seg[u].sz = (seg[u].sz+(tr-tl+1))%MOD;
			seg[u].lzy = equation(1, 1);
		}
	} else {
		int tm = (tl+tr)/2;
		update(2*u, tl, tm, l, r, contains);
		update(2*u+1, tm+1, tr, l, r, contains);
		seg[u].sz = (seg[2*u].sz+seg[2*u+1].sz)%MOD;
	}
}

ll query(int u, int tl, int tr, int l, int r) {
	if (l > tr || r < tl) return 0;
	if (tl!=tr && seg[u].lzy.active()) {
		pushdown(u, tl, tr);
	}
	if (l <= tl && tr <= r) {
		return seg[u].sz;
	} else {
		int tm = (tl+tr)/2;
		ll lft = query(2*u, tl, tm, l, r);
		ll rt = query(2*u+1, tm+1, tr, l, r);
		return (lft+rt)%MOD;
	}
}

set<ii> s[MAXN];
int n, q;

void split(int x, int at) {
	auto it = s[x].lower_bound(ii(at, -1));
	if (it!=s[x].begin()) {
		--it;
		int itl = it->first, itr = it->second;
		if (at <= itr) {
			s[x].erase(it);
			s[x].insert(ii(itl, at-1));
			s[x].insert(ii(at, itr));
		}
	}
}

int main() {
	scanf("%d%d", &n, &q);
	while (q--) {
		int t; scanf("%d", &t);
		if (t==1) {
			int l, r, x; scanf("%d%d%d", &l, &r, &x);

			split(x, l); split(x, r+1);

			int last = l;

			while (1) {
				auto it = s[x].lower_bound(ii(l,-1));
				if (it == s[x].end()) break;
				if (it->first > r) break;

				assert(it->second <= r);
				update(1, 1, n, last, it->first-1, false);
				update(1, 1, n, it->first, it->second, true);
				last = it->second+1;

				s[x].erase(it);
			}

			update(1, 1, n, last, r, false);
			s[x].insert(ii(l, r));
		} else {
			int l, r; scanf("%d%d", &l, &r);
			ll ans = query(1, 1, n, l, r);
			printf("%d\n", (int)ans);
		}
	}
}