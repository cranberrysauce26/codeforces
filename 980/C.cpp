/*input
4 3
2 14 3 4
*/
#include <bits/stdc++.h>
using namespace std;
int n, k, ng, g[300], gsz[300], p[100005];
int main() {
	scanf("%d%d", &n, &k);
	memset(g, -1, sizeof g);
	g[0] = 0;
	ng = 1;
	for (int i = 0; i < n; ++i) scanf("%d", p+i);
	for (int i = 0; i < n; ++i) {
		// printf("i = %d\n", i);
		if (g[p[i]] == -1) {
			int r = p[i]-1;
			while (r >= 0 && g[r] == -1) --r;
			int l = r;
			while (l-1 >= 0 && g[l-1] == g[r]) --l;
			// printf("l = %d, r = %d\n", l, r);
			assert(0 <= l && l <= r);
			if (p[i]-l+1 <= k) {
				for (int x=r+1; x<=p[i]; ++x) g[x]=g[l];
			} else {
				int st = max(r+1, p[i]-k+1);
				for (int x = st; x<=p[i]; ++x) g[x]=ng;
				// g[p[i]] = ng++;
				++ng;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		assert(g[p[i]]!=-1);
		int l = p[i];
		while (l-1 >= 0 && g[l-1] == g[p[i]]) --l;
		printf("%d ", l);
	}
	printf("\n");
}