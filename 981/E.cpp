/*input
7 2
1 5 1
3 7 2
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

const int MAXN = 1e4+5;

typedef bitset<MAXN> sum_t;

int n, q;

bool possible[MAXN];

vector<int> seg[4*MAXN];

void update(int u, int l, int r, int tl, int tr, int x) {
	if (l > tr || r < tl) return;
	else if (l <= tl && tr <= r) {
		seg[u].push_back(x);
	} else {
		int tm = (tl+tr)/2;
		update(u<<1, l, r, tl, tm, x);
		update(u<<1|1, l, r, tm+1, tr, x);
	}
}

void query(int u, int tl, int tr, sum_t parsums) {
	sum_t sums = parsums;
	// printf("u = %d, tl = %d, tr = %d\n", u, tl, tr);

	for (int v : seg[u]) {
		// printf("	updating v = %d\n", v);
		sums |= sums << v;
	}

	for (int i = 1; i <= n; ++i) {
		possible[i] |= sums[i];
	}

	if (tl != tr) {
		int tm = (tl+tr)/2;

		query(2*u, tl, tm, sums);
		query(2*u+1, tm+1, tr, sums);
	}
}


int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n >> q;
	while (q--) {
		int l, r, x; cin >> l >> r >> x;
		update(1, l, r, 1, n, x);
	}
	query(1, 1, n, sum_t(1));
	int cnt = 0;
	for (int i = 0; i <= n; ++i) {
		if (possible[i]) {
			++cnt;
		}
	}
	cout << cnt << "\n";
	for (int i = 0; i <= n; ++i) {
		if (possible[i]) {
			cout << i << " ";
		}
	}
}
