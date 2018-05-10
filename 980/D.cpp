/*input
4
1 0 0 2
*/
#include <bits/stdc++.h>
#define sq(x) ((x)*(x))
using namespace std;
typedef long long ll;
const int MAXN = 5e3+5;
int n, a[MAXN], ds[MAXN], rnk[MAXN], cnt[MAXN];
void init() {for (int i = 1; i <= n; ++i) ds[i] = i;}
int find(int x) {return (x==ds[x]) ? x : ds[x] = find(ds[x]);}
bool merge(int x, int y) {
	x = find(x), y = find(y);
	if (x==y) return false;
	if (rnk[x] < rnk[y]) ds[x]=y;
	else {
		if (rnk[x]==rnk[y]) ++rnk[x];
		ds[y]=x;
	}
	return true;
}

int cache[MAXN];

void remember() {
	for (int i = 1; i <= n; ++i) {
		cache[i] = find(i);
	}
}

int freq[MAXN];
double sqrtcache[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a+i);
	for (int i = 1; i <= n; ++i) sqrtcache[i] = sqrt((double)abs(a[i]));
	init();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < i; ++j) {
			if ( (a[i] <= 0 && a[j] >= 0) || (a[i] >= 0 && a[j] <= 0)) continue;
			ll g = sqrtcache[i]*sqrtcache[j];
			ll mult = 1LL*a[i]*a[j];
			if (sq(g-1)==mult || sq(g)==mult || sq(g+1)==mult) {
				merge(i,j);
				break;
			}
		}
	}
	remember();
	for (int i = 1; i <= n; ++i) {
		memset(freq, 0, sizeof freq);
		int j = i;
		for (j = i; j <= n && a[j]==0; ++j) ++cnt[1];
		int distinct = 0;
		for (; j <= n; ++j) {
			if (a[j]!=0 && freq[cache[j]] == 0) {
				++distinct;
				freq[cache[j]] = 1;
			}
			++cnt[distinct];
		}
	}
	for (int i = 1; i <= n; ++i) printf("%d\n", cnt[i]);
}