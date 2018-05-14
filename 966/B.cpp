/*input
5 12 20
7 8 4 11 9
*/
#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
using namespace std;

typedef long long ll;
const int INF = 1e9;
int n;
ll x1, x2;

vector<pair<ll,int>> c;

inline ll ceil(ll a, ll b) {return a%b==0 ? a/b : a/b+1;}

int main() {
	cin >> n >> x1 >> x2;
	c.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> c[i].first;
		c[i].second = i+1;
	}
	sort(all(c));

	int i2, kk2;

	for (i2 = n-1; i2 >= 0; --i2) {
		kk2 = ceil(x2, c[i2].first);
		if (i2+kk2-1 < n) break;
	}

	int i1, kk1;
	for (i1 = n-1; i1 >= 0; --i1) {
		kk1 = ceil(x1, c[i1].first);
		if (i1+kk1-1 < n) break;
	}


	for (int j1 = 0; j1 < n; ++j1) {
		int req1 = ceil(x1, c[j1].first);
		if (j1+req1-1 < n && j1+req1-1 < i2) {
			// works
			cout << "Yes\n" << req1 << " " << kk2 << "\n";
			for (int i = 0; i < req1; ++i) cout << c[j1+i].second << " ";
			cout << "\n";

			for (int i = 0; i < kk2; ++i) cout << c[i2+i].second << " ";
			cout << "\n";
			return 0;
		}
	}

	for (int j2 = 0; j2 < n; ++j2) {
		int req2 = ceil(x2, c[j2].first);
		if (j2+req2-1 < n && j2+req2-1 < i1) {
			// works
			cout << "Yes\n" << kk1 << " " << req2 << "\n";
			for (int i = 0; i < kk1; ++i) cout << c[i1+i].second << " ";
			cout << "\n";

			for (int i = 0; i < req2; ++i) cout << c[j2+i].second << " ";
			cout << "\n";
			return 0;
		}
	}
	cout << "No\n";
}