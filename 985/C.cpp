/*input
4 2 3
2 2 8 4 6 7 4 4
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

int n, k;
ll I;
ll a[100005];
int main() {
	// freopen("data.txt", "r", stdin);
	// scanf("%d%d%d", &n, &k, &I);
	cin >> n >> k >> I;
	for (int i = 1; i <= n*k; ++i) {
		// scanf("%d", a+i);
		cin >> a[i];
	}

	sort(a+1, a+1+n*k);
	if (a[n]-a[1] > I) {
		return !printf("0\n");
	}

	int r = n*k;
	while (r > 1 && a[r]-a[1] > I) --r;

	// for (int i = 1; i <= n*k; ++i) printf("%d ", a[i]);
		// printf("\n");

	assert(r >= n);
	// printf("r = %d\n", r);
	ll sum = a[1];
	int prel = 1;
	for (int i = 2; i <= n; ++i) {
		int j = min(prel+k, i+r-n);
		// printf("i = %d, j = %d\n", i, j);
		sum += a[j];
		prel = j;
	}
	// printf("%d\n", sum);
	cout << sum << "\n";
}