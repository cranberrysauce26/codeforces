/*input
19 6
##..............###
#......#####.....##
.....#########.....
....###########....
...#############...
..###############..
.#################.
.#################.
.#################.
.#################.
#####....##....####
####............###
####............###
#####...####...####
.#####..####..#####
...###........###..
....###########....
.........##........
#.................#
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
#define ceil(a,b) (1+((a)-1)/(b))
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;
char g[105][105];
int n, k, freq[105][105];

bool hvalid(int r, int c) {
	if (c+k-1>n) return false;
	for (int i=0; i<k; ++i){
		if (g[r][c+i]=='#') return false;
	}
	return true;
}
void hcover(int r, int c){
	for (int i=0; i<k; ++i){
		++freq[r][c+i];
	}
}

bool vvalid(int r, int c){
	if (r+k-1>n) return false;
	for (int i=0; i<k; ++i){
		if (g[r+i][c]=='#') return false;
	}
	return true;
}

void vcover(int r, int c){
	for (int i=0; i<k; ++i){
		freq[r+i][c]++;
	}
}

int main() {
	scanf("%d%d", &n, &k);
	for (int r=1; r<=n; ++r){
		for (int c=1; c<=n; ++c){
			scanf(" %c", &g[r][c]);
		}
	}

	for (int r=1; r<=n; ++r){
		for (int c=1; c<=n; ++c){
			if (hvalid(r,c)){
				hcover(r,c);
			}
		}
	}

	for (int c=1; c<=n; ++c){
		for (int r=1; r<=n; ++r) {
			if (vvalid(r,c)){
				vcover(r,c);
			}
		}
	}
	int bestr=1, bestc=1;
	for (int r=1; r<=n; ++r){
		for (int c=1; c<=n;++c){
			if (freq[r][c]>freq[bestr][bestc]){
				bestr=r,bestc=c;
			}
		}
	}
	printf("%d %d\n", bestr, bestc);
}
