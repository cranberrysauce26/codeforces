/*input
10 1
accbaaccac
6 8 3
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

int n, m, pref[26][200005];
char s[200005];
int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		scanf(" %c", &s[i]);
		pref[s[i]-'a'][i] = 1;
		for (int c = 0; c < 26; ++c) pref[c][i] += pref[c][i-1];
	}

	while (m--) {
		int x, y, len;
		cin >> x >> y >> len;
		vector<int> freqx(26), freqy(26);
		for (int i = 0; i < 26; ++i) {
			freqx[i] = pref[i][x+len-1]-pref[i][x-1];
			freqy[i] = pref[i][y+len-1]-pref[i][y-1];
		}
		sort(all(freqx));
		sort(all(freqy));

		if (freqx==freqy) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
}
