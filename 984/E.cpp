/*input
4
4 2
5 1
1 4
1 3
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n, a[2005], b[2005], maxb[11], cntb[11], mem[2005][150], end_mask;

/**
 * Algorithm.
 * 
 * Suppose that you go to a position p
 * then if you visit it later, you might as well have not visited it now
 * So if you visit, maxb[p]<nxta
 */
int solve(int ai, int mask){
	// you are at position pos with visited mask and next a is ai
	int& ans=mem[ai][mask];
	if (ans!=-1) return ans;

	printf("solve(%d, %d)\n", ai, mask);
	if (mask==end_mask) {
		assert(ai==n+1);
		return ans=0;
	}

	ans=INF;

	vector<int> leavemsk(11);
	int lft=-1, rt=-1;

	for(int i=1; i<=10; ++i){
		if (maxb[i]!=0 && maxb[i]<ai && (mask&(1<<i))==0) {
			// printf("	ai=%d, mask=%d, i=%d\n", ai, mask, i);
			if (lft==-1) lft=i;
			rt=i;
			leavemsk[i]=1<<i;
		}
		leavemsk[i] |= leavemsk[i-1];
	}

	int pos=a[ai-1];

	if (ai==n+1){
		assert(lft!=-1);
		assert(rt!=-1);
		assert(lft<=rt);

		int dist=min(abs(rt-pos)+abs(rt-lft), abs(pos-lft)+abs(rt-lft));
		printf("solve(%d,%d): l=%d, r=%d, dist=%d\n", ai, mask, lft, rt, dist);
		ans=dist;
	} else {
		for (int pos2=1; pos2<=10; ++pos2){
			int lo=min(pos,min(a[ai],pos2)), hi=max(pos,max(a[ai],pos2));
			int mask2=mask|(leavemsk[hi]^leavemsk[lo-1]);
			// int gone=leave[hi]-leave[lo-1];
			// int dist=abs(hi-pos)+abs(pos-lo);
			int dist=abs(pos2-pos)+abs(a[ai]-pos2);
			// printf("solve(%d,%d) pos=%d, pos2=%d, nxta=%d, lo=%d, hi=%d, dist=%d, mask2=%d, mask|=%d\n", ai, mask, pos, pos2, a[ai], lo, hi, dist, mask2, (leavemsk[hi]^leavemsk[lo-1]));
			ans=min(ans,solve(ai+1,mask2)+dist);
		}
	}
	printf("solve(%d, %d) = %d\n", ai, mask, ans);
	return ans;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	a[0]=1;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i], &b[i]);
		maxb[b[i]]=max(maxb[b[i]],i);
		end_mask|=1<<b[i];
		cntb[b[i]]++;
	}
	// for (int i=1; i<=10; ++i) {
		// printf("maxb[%d]=%d\n",i,maxb[i]);
	// }
	memset(mem, -1, sizeof mem);
	int ans=solve(1,0);
	printf("%d\n", ans+2*n);
}