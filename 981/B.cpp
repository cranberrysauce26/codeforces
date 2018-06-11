/*input
1
1000000000 239
3
14 15
92 65
35 89
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

int n, m;

unordered_map<int, ll> v;

int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n;

	for (int i = 0; i < n; ++i) {
		int a; ll x;
		cin >> a >> x;
		v[a] = x;
	}

	cin >> m;

	for (int i = 0; i < m; ++i) {
		int a; ll x;
		cin >> a >> x;
		if (v.find(a) == v.end()) {
			v[a] = x;
		} else {
			if (x > v[a]) {
				v[a] = x;
			}
		}
	}


	ll sum = 0;

	for (auto p : v) {
		sum += p.second;
	}

	cout << sum << "\n";
}
