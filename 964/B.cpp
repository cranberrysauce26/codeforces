/*input
5 5 3 4 5
1 2 3 4 5
*/
#include <bits/stdc++.h>
using namespace std;

int n, A, B, C, T, ans = 0;

int main() {
	scanf("%d%d%d%d%d", &n, &A, &B, &C, &T);
	for (int i = 0; i < n; ++i) {
		int t; scanf("%d", &t);
		// t, ..., r you cash it in on day r
		// A+(r-t)*(B-C)
		// (r-t)
		if (B < C) {
			// A * ()
			ans += A+(T-t)*(C-B);
		} else {
			ans += A;
		}
	}
	printf("%d\n", ans);
}