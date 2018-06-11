/*input
x
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

char s[55];

bool ispali(int l, int r) {
	while (l < r) {
		if (s[l] != s[r]) return false;
		++l;
		--r;
	}
	return true;
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf(" %s", s);
	int n = strlen(s);
	for (int sz = n; sz >= 0; --sz) {
		for (int i = 0; i + sz - 1 <= n-1; ++i) {
			if (!ispali(i, i+sz-1)) return !printf("%d\n", sz);
		}
	}
	printf("0\n");
}
