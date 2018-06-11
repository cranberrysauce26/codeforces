/*input

*/
#include <bits/stdc++.h>
#include <cstdint>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;
inline ll ceil(ll a, ll b) {
	if(a%b==0) return a/b;
	return a/b+1LL;
}
int main() {
	ll n, k, M, D;
	cin >> n >> k >> M >> D;
	ll best=0;
	for (ll d=1LL; d<=D; ++d){
		ll lo;
		if (d>=1LL+(n-1)/k){
			lo=1LL;
		} else {
			lo=n/(d*k+1LL)+1LL;
		}
		ll hi;
		if (d-1LL>=1LL+(n-1LL)/k){
			hi=min(M,0LL);		
		} else {
			hi=min(M,n/(k*(d-1LL)+1LL));
		}
		if (lo<=hi){
			ll x=hi;
			best=max(best, x*d);
		}
	}
	cout << best << "\n";
}
