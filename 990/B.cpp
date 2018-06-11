/*input

*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

int n,  K;
// map<int,int> vals;
vector<int> A;

int main() {
	freopen("data.txt", "r", stdin);
	cin >> n >> K;
	for (int i = 1; i <= n; ++i) {
		int a; cin >> a;
		// vals[a]++;
		A.push_back(a);
	}
	int cnt = 0;
	sort(A.begin(), A.end());
	for (int i = 0; i < A.size(); ++i) {
		auto it = upper_bound(A.begin(), A.end(), A[i]);
		if (it!=A.end()) {
			if (*it <= A[i]+K) {
				++cnt;
				// printf("keeping i = %d, A[i] = %d\n", i, A[i]);
			}
		}
	}
	cout << n-cnt << "\n";
}
