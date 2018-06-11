/*input
6
10 8 9 11 13 5
010010011101

*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

int n;
char in;

priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pairs;
priority_queue<pair<ll,int>> single;
int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n;
	for (int i=1; i<=n; ++i){
		ll width; cin >> width;
		pairs.push({width, i});
	}
	for (int i=1; i<=2*n; ++i){
		scanf(" %c", &in);
		if (in=='0'){
			// introvert
			// must take negative
			auto row = pairs.top(); pairs.pop();
			single.push(row);
			cout << row.second << " ";
		} else {
			auto row = single.top();
			single.pop();
			cout << row.second << " ";
		}
	}
}
