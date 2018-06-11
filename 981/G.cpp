/*input
3 7
1 1 1 3
1 1 1 3
1 1 1 2
1 1 1 1
2 1 1
1 1 1 2
2 1 1
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using flagset = unordered_set<int>;

const int MAXN = 2e5+5;
const ll MOD = 998244353;

inline bool isin(const flagset& u, int x) {
	return u.find(x)!=u.end();
}

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
	flagset done, semi;
	ll sz;
	int nch; // cuz i'm lazy
	equation lzy;
} seg[4*MAXN];

int n, q;

void pushdown(int u) {
	for (int v = 2*u; v <= 2*u+1; ++v) {
		seg[v].sz = seg[u].lzy.eval(seg[v].sz, seg[v].nch);
		seg[v].lzy = seg[u].lzy.combine(seg[v].lzy);
	}
}

void update(int u, int tl, int tr, int l, int r, int x, bool certain) {
	if (l > tr || r < tl) return;
	if (tl != tr && seg[u].lzy.active()) {
		pushdown(u);
	}
	seg[u].lzy = equation();
	if (l <= tl && tr <= r) {
		bool indone;
		if (certain) indone = true;
		else indone = isin(seg[u].done, x);

		if (indone) {
			seg[u].sz = (seg[u].sz*2LL)%MOD;
			seg[u].lzy = equation(2, 0);
		} else if (isin(seg[u].semi, x)) {
			assert(tl!=tr);
			int tm = (tl+tr)/2;
			update(2*u, tl, tm, l, r, x, false);
			update(2*u+1, tm+1, tr, l, r, x, false);

			seg[u].sz = (seg[2*u].sz+seg[2*u+1].sz)%MOD;
		} else {
			seg[u].sz = (seg[u].sz+seg[u].nch)%MOD;
			seg[u].lzy = equation(1, 1);
		}
		seg[u].done.insert(x);
	} else {
		int tm = (tl+tr)/2;
		bool done = certain;
		if (!done) done = isin(seg[u].done, x);
		update(2*u, tl, tm, l, r, x, done);
		update(2*u+1, tm+1, tr, l, r, x, done);

		seg[u].sz = (seg[2*u].sz+seg[2*u+1].sz)%MOD;

		bool ldone = isin(seg[2*u].done, x);
		bool rdone = isin(seg[2*u+1].done, x);

		if (!done) {
			if (ldone && rdone) {
				seg[u].done.insert(x);
			} else {
				seg[u].semi.insert(x);
			}
		}
	}
}

ll query(int u, int tl, int tr, int l, int r) {
	if (l > tr || r < tl) return 0;
	if (tl != tr && seg[u].lzy.active()) {
		pushdown(u);
	}
	seg[u].lzy = equation();
	if (l <= tl && tr <= r) {
		return seg[u].sz;
	}
	int tm = (tl+tr)/2;
	ll lft = query(2*u, tl, tm, l, r);
	ll rt = query(2*u+1, tm+1, tr, l, r);
	return (lft+rt)%MOD;
}

void init(int u, int tl, int tr) {
	seg[u].nch = tr-tl+1;
	if (tl!=tr) {
		int tm = (tl+tr)/2;
		init(2*u, tl, tm);
		init(2*u+1, tm+1, tr);
	}
}

int main() {
	freopen("data.txt", "w", stdout);
	// scanf("%d%d", &n, &q);
	srand(time(NULL));
	n = 10000, q = 200000;
	init(1, 1, n);
	while (q--) {
		int t, l, r;
		// scanf("%d%d%d", &t, &l, &r);
		// t = (rand()%2)+1;
		t = 1;
		int tmpl = (rand()%n)+1;
		int tmpr = (rand()%n)+1;
		l = min(tmpl, tmpr), r= max(tmpl, tmpr);
		if (t==1) {
			int x = (rand()%n)+1;
			// int x;
			// scanf("%d", &x);
			update(1, 1, n, l, r, x, isin(seg[1].done, x));
		} else {
			ll ans = query(1, 1, n, l, r);
			cout << ans << "\n";
		}
	}
	printf("DONE\n");
}