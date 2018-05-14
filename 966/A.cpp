#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> e, s;

int n, m, v, ne, ns, q;

inline int ceil(int a, int b) {
	if (a%b==0) return a/b;
	return a/b+1;
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d%d%d%d", &n, &m, &ns, &ne, &v);
	s.resize(ns); e.resize(ne);
	for (int i = 0; i < ns; ++i) scanf("%d", &s[i]);
	for (int i = 0; i < ne; ++i) scanf("%d", &e[i]);
	scanf("%d", &q);
	while (q--) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &y1, &x1, &y2, &x2);

		if (y1==y2) {
			printf("%d\n", abs(x1-x2));
			continue;
		}

		ll ans = 1000000000000000LL;
		auto it1 = upper_bound(s.begin(), s.end(), x2);
		
		if (it1!=s.end()) ans = min(ans, 1LL*abs(*it1 - x1)+abs(*it1-x2)+abs(y2-y1));
		if (it1!=s.begin()) {
			--it1;
			ans = min(ans, 1LL*abs(*it1 - x1)+abs(*it1-x2)+abs(y2-y1));
		}

		auto it3 = upper_bound(e.begin(), e.end(), x2);
		
		if (it3!=e.end()) ans = min(ans, 1LL*abs(*it3-x1)+abs(*it3-x2)+ceil(abs(y2-y1), v));
		if (it3!=e.begin()){
			--it3;
			ans = min(ans, 1LL*abs(*it3-x1)+abs(*it3-x2)+ceil(abs(y2-y1), v));
		}
		cout << ans << endl;
	}
}