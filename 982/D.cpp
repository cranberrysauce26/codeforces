/*input
1
1
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

const int MAXN = 1e5+5;

void bit_upd(int x, int v, int* bit){
	for (;x<MAXN;x+=x&-x) bit[x]+=v;
}

int bit_q(int x, int*bit){
	int res=0;
	for (;x;x-=x&-x) res+=bit[x];
		return res;
}

int bitL[MAXN], bitR[MAXN];

int n, a[MAXN];

vector<ii> order;

map<int,int> szs;

int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n;
	for (int i=1; i<=n;++i) {
		cin>>a[i];
		order.push_back({a[i],i});
	}

	sort(all(order));
	int k=order.back().first+1, max_loc=1;

	bit_upd(1, 1, bitL);
	bit_upd(1, n, bitR);

	szs[n]=1;

	for (int j=n-1; j>=0; --j){
		int i=order[j].second, kk=order[j].first;
		int curL = bit_q(i, bitL);
		int curR = bit_q(i, bitR);
		assert(curL <= i);
		assert(i <= curR);
		int curSz=curR-curL+1;
		szs[curSz]--;
		if (szs[curSz]==0){
			auto it = szs.find(curSz);
			szs.erase(it);
		}
		if (curR-i>0) szs[curR-i]++;
		if (i-curL>0) szs[i-curL]++;
		// update bit
		bit_upd(curL, i-1-curR, bitR);
		bit_upd(i, -(i-1-curR), bitR);
		bit_upd(i+1, i+1-curL, bitL);
		bit_upd(curR+1, -(i+1-curL), bitL);
		if (szs.size()==1) {
			int nloc = szs.begin()->second;
			if (j>0) kk=order[j-1].first+1;
			if (nloc > max_loc) {
				k = kk;
				max_loc = nloc;
			} else if (nloc == max_loc) {
				if (kk < k) {
					k=kk;
				}
			}
		}
	}
	cout << k << endl;
}
