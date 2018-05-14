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
	// freopen("data.txt", "r", stdin);
	ll n; cin >> n;
	++n;
	if (n==1) cout << 0 << endl;
	else if (n%2==0) {
		cout << n/2 << endl;
	} else {
		cout << n << endl;
	}
}
