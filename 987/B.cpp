/*input
1000000000 999999999
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;
typedef long double ld;

int main() {
	// freopen("data.txt", "r", stdin);

	ll X, Y; cin >> X >> Y;

	if (X==1) {
		if (Y==1) {
			printf("=\n");
		} else {
			printf("<\n");
		}
		return 0;
	} else if (Y==1) {
		if (X==1) {
			// redundant
			printf("=\n");
		} else {
			printf(">\n");
		}
		return 0;
	}

	if (X==Y) {
		printf("=\n");
		return 0;
	}

	ld x = ld(X), y = ld(Y);

	ld logx = log(x);
	ld logy = log(y);

	ld diff = y*logx - x*logy;

	const ld EPS = 1e-6;
	cout << "diff = " << diff << "\n";

	if (diff > EPS) {
		printf(">\n");
	} else if (diff < -EPS) {
		printf("<\n");
	} else {
		printf("=\n");
	}
}