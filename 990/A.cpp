/*input

*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

int main() {
	freopen("data.txt", "r", stdin);
	ll n, m, a, b;
	cin >> n >> m >> a >> b;
	
	ll tosub = n%m;
	ll subcost = tosub * b;


	ll toadd = m-n%m;
	ll addcost = toadd * a;

	ll ans = min(subcost, addcost);
	cout << ans << "\n";
}
