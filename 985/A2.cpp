/*input
6
4 3 2
*/
#include <bits/stdc++.h>
using namespace std;
int n, p[100];

int main() {
	cin >> n;
	for (int i = 1; i <= n/2; ++i) cin >> p[i];

	sort(p+1, p+1+(n/2));

	// case 1: go to odd
	int odd = 0;
	for (int i = 1, at = 1; i <= n/2; ++i, at+=2) {
		odd += abs(at-p[i]);
	}

	int even = 0;
	for (int i = n/2, at = n; i >= 1; --i, at-=2) {
		even += abs(at-p[i]);
	}
	printf("%d\n", min(odd, even));
}