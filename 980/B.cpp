/*input
5 5
*/
#include <bits/stdc++.h>

int n, k;

int main() {
	scanf("%d%d", &n, &k);
	printf("YES\n");
	for (int i = 0; i < n; ++i) printf(".");
	printf("\n");
	if (k%2 == 0) {
		for (int r = 0; r < 2; ++r) {
			printf(".");
			for (int i = 1; i <= n-2; ++i) {
				if (i <= k/2) printf("#");
				else printf(".");
			}
			printf(".\n");
		}
	} else if (k <= n-2) {
		/// [1, k/2] ... (n-1)/2...[n-2-k/2+1, n-2]
		printf(".");
		for (int i = 1; i <= n-2; ++i) {
			if (i <= k/2 || i >= n-2-k/2+1 || i==(n-1)/2) printf("#");
			else printf(".");
		}
		printf(".\n");
		for (int i = 0; i < n; ++i) printf(".");
		printf("\n");
	} else {
		printf(".");
		for (int i = 1; i <= n-2; ++i) {
			printf("#");
		}
		printf(".\n");
		k -= n-2;
		// k is now even
		printf(".");
		for (int i = 1; i <= n-2; ++i) {
			if (i <= k/2 || i >= n-2-k/2+1) printf("#");
			else printf(".");
		}
		printf(".\n");
	}

	for (int i = 0; i < n; ++i) printf(".");
	printf("\n");
}