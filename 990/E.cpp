#include <bits/stdc++.h>
// #define LOCAL
#ifdef LOCAL
    #define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)                                                                          
#else
    #define DEBUG(fmt, args...)
#endif

using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;
const int MAXN = 1e6+6;
int n, m, k, cost[MAXN], obs[MAXN];

int main() {
	#ifdef LOCAL
	freopen("data.txt", "r", stdin);
	#endif
	scanf("%d%d%d", &n, &m, &k);
	memset(obs, -1, sizeof obs);
	for (int i = 0; i < m; ++i) {
		int x; scanf("%d", &x);
		obs[x] = 1;
	}

	if (obs[0] == 1) {
		DEBUG("obstacle at 0\n");
		printf("-1\n");
		return 0;
	}
	int maxdiff = 0;
	for (int i = 0; i < n; ++i) {
		if (obs[i] != -1) {
			if (i==0) {
				obs[i] = 0;
			} else if (obs[i-1] != -1) {
				obs[i] = obs[i-1];
			} else {
				obs[i] = i;
			}
			maxdiff = max(maxdiff, i-obs[i]+1);
		}
	}

	for (int i = 1; i <= k; ++i) {
		scanf("%d", cost+i);
	}
	
	ll ans = numeric_limits<ll>::max();
	for (int jmp = maxdiff+1; jmp <= k; ++jmp) {
		int x = 0, njmps = 0;
		DEBUG("jmp = %d\n", jmp);
		while (x < n) {
			assert(obs[x]==-1);
			if (x+jmp >= n) {
				++njmps;
				break;
			} else if (obs[x+jmp]==-1) {
				x += jmp;
				++njmps;
			} else {
				x = obs[x+jmp]-1;
				++njmps;
			}
		}
		ans = min(ans, 1LL * njmps * cost[jmp]);
	}
	if (ans==numeric_limits<ll>::max()) {
		cout << "-1\n";
	} else {
		cout << ans << "\n";
	}
}