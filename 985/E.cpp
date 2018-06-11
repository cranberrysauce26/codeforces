/*input
6 4 0
1 3 2 4 2 1
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

ll n, k, d, a[500005];

int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n >> k >> d;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	sort(a+1, a+1+n);
	a[n+1] = a[n];
	set<int> solvable;
	solvable.insert(n+1);
	for (ll i = n; i >= 1; --i) {
		auto it = solvable.lower_bound(i+k);
		if (it!=solvable.end()){
			int j = *it;
			if (a[j-1]-a[i] <= d) {
				solvable.insert(i);
			}
		}
	}
	if (solvable.find(1)!=solvable.end()) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}
}
