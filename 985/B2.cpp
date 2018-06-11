/*input
4 5
10100
01000
00110
00101


*/

#include <bits/stdc++.h>
using namespace std;

int n, m, A[2005][2005], res[2005];

int main() {
	scanf("%d%d", &n, &m);
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			char ch; scanf(" %c", &ch);
			A[r][c] = ch-'0';
			res[c] += A[r][c];
		}
	}

	for (int sw = 1; sw <= n; ++sw) {
		bool works = true;
		for (int c = 1; c <= m; ++c) {
			res[c] -= A[sw][c];
			if (res[c] <= 0) {
				works = false;
			}
		}
		if (works) {
			printf("YES\n");
			return 0;
		}
		for (int c = 1; c <= m; ++c) {
			res[c] += A[sw][c];
			if (res[c] <= 0) {
				works = false;
			}
		}
	}
	printf("NO\n");
}