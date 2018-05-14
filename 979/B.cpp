/*input
1
aaab
abcd
aaaa
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

string s[3];
ll freq[3][52], mxfreq[3];
ll n;

inline int hsh(char c) {
	if ('a' <= c && c <= 'z') return c-'a';
	else return c-'A'+26;
}

string name[3] = {"Kuro", "Shiro", "Katie"};
pair<ll, string> nequal[3];

int main() {
	// freopen("data.txt", "r", stdin);
	cin >> n >> s[0] >> s[1] >> s[2];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < sz(s[i]); ++j) {
			freq[i][hsh(s[i][j])]++;
		}
		
		for (int j = 0; j < 52; ++j) mxfreq[i] = max(mxfreq[i], freq[i][j]); 
	}

	for (int i = 0; i < 3; ++i) {
		if (mxfreq[i]+n <= 1LL*sz(s[i])) nequal[i].first = mxfreq[i]+n;
		else {
			if (mxfreq[i] == sz(s[i])) {
				if (n==1) nequal[i].first = sz(s[i])-1;
				else nequal[i].first = sz(s[i]);
			} else {
				nequal[i].first = sz(s[i]);
			}
		}
		// printf("nequal[%d] = %d\n", i, nequal[i].first);
		nequal[i].second = name[i];
	}

	sort(nequal, nequal+3);

	if (nequal[2].first==nequal[1].first) return !printf("Draw\n");

	cout << nequal[2].second << endl;
}
