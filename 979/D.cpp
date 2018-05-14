/*input
5
1 1
1 2
2 1 1 3
2 1 1 2
2 1 1 1
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

const int LOG = 20;

struct xor_t {
	int max_bits = 1;
	set<int> s;
	inline void add(int x) {
		s.insert(x);
		while ((1<<max_bits) < x) ++max_bits;
	}

	inline int query(int x, int mx) {
		auto lo = s.begin(), hi = s.upper_bound(mx);
		if (hi==s.begin()) return -1;
		--hi;
		int pre = 0;
		auto tmp = s.begin();
		for (int k = max_bits; k >= 0 && *lo < *hi; --k){
			// printf("k = %d, *lo = %d, *hi = %d\n", k, *lo, *hi);
			if (x&(1<<k)) {
				// you want it to be zero
				// so decrease hi
				tmp = s.lower_bound(pre | (1<<k));
				if (tmp == s.begin()) {
					pre |= 1<<k;
					continue;
				}
				--tmp;
				if (*tmp < *lo) {
					pre |= 1<<k;
					continue;
				}
				if (*tmp > *hi) {
					continue;
				}
				hi = tmp;
			} else {
				// you want it to be one
				tmp = s.lower_bound(pre | (1<<k));
				if (tmp==s.end()) continue;
				if (*tmp > *hi) continue;
				lo = tmp;
				pre |= 1<<k;
			}
		}
		assert(lo==hi);
		return *lo;
	}
};
bool took[100005];
xor_t xors[100005];

void add(int v) {
	if (took[v]) return;
	took[v]=true;

	for (int f = 1; f*f <= v; ++f) {
		if (v%f==0) {
			xors[f].add(v);
			xors[v/f].add(v);
		}
	}
}

int main() {
	// freopen("data.txt", "r", stdin);
	int q, t, x, v, k, s;
	scanf("%d", &q);
	while (q--) {
		scanf("%d", &t);
		if (t==1) {
			scanf("%d", &v);
			add(v);
		} else {
			scanf("%d%d%d", &x, &k, &s);
			if (x%k != 0) printf("-1\n");
			else {
				// v <= s-x
				int ans = xors[k].query(x, s-x);
				printf("%d\n", ans);
			}
		}
	}
}