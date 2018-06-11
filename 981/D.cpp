/*input
1 1
1
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef unsigned long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

int n, k;
ll a[55], presum[55];

ll dp[55][55], dp2[55][55], val[55][55];

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		presum[i] = a[i]+presum[i-1];
	}

	if (k==1) {
		cout << presum[n] << "\n";
		return 0;
	}

	for (int i = 1; i <= n; ++i) {
		val[1][i] = presum[i];
		for (int j = 2; j <= k; ++j) {
			dp[j][i] = (1LLU << (n+1)) - 1;
		}
	}

	ll ans = 0;

	for (int bit = 63; bit >= 0; --bit) {
		for (int j = 2; j <= k; ++j) {
			for (int i = j; i <= n; ++i) {
				dp2[j][i] = 0;
				for (int p = j; p <= i; ++p) {
					if (dp[j][i] & (1LLU << p)) {
						if ((presum[i]-presum[p-1]) & val[j-1][p-1] & (1LLU << bit)) {
							dp2[j][i] |= 1LLU << p;
						}
					}
				}
				if (dp2[j][i]) {
					val[j][i] |= 1LLU << bit;
				}
			}
		}

		if (dp2[k][n]) {
			ans |= 1LLU << bit;
			for (int j = 2; j <= k; ++j) {
				for (int i = j; i <= n; ++i) {
					dp[j][i] = dp2[j][i];
				}
			}
		}
	}

	cout << ans << "\n";
}
