/*input
6
1 2 4 8 16 32
4
1 6
2 5
3 4
1 2
*/
#include <bits/stdc++.h>
using namespace std;

int n, q, a[5005], mxf[5005][5005];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a+i);
	}
	for (int i = 1; i <= n; ++i) mxf[i][i] = a[i];
	for (int i = 1; i < n; ++i) mxf[i][i+1] = a[i]^a[i+1];
	for (int k = 1; (1<<k) <= n; ++k){
		for (int i=1; i<=(1<<k); ++i){
			for (int l=1; l+(1<<k)+i-1<=n; ++l){
				mxf[l][l+(1<<k)+i-1]=mxf[l][l+i-1]^mxf[l+(1<<k)][l+(1<<k)+i-1];
			}
		}
	}
	for (int sz=2; sz<=n; ++sz){
		for (int l=1; l+sz-1<=n; ++l){
			mxf[l][l+sz-1]=max(mxf[l][l+sz-1],max(mxf[l+1][l+sz-1],mxf[l][l+sz-2]));
		}
	}
	scanf("%d", &q);
	while (q--){
		int l,r; scanf("%d%d", &l, &r);
		printf("%d\n", mxf[l][r]);
	}
}
