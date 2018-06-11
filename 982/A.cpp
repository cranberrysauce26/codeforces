/*input
2
00
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;
int n;
char a[1005];
int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	scanf(" %s", a);

	if (n==1) {
		if (a[0]=='1') printf("YES\n");
		else printf("NO\n");
		return 0;
	}

	bool no_neighbour=true;

	for (int i=0; i+1<n; ++i){
		if (a[i]=='1' && a[i+1]=='1') no_neighbour=false;
	}

	if (!no_neighbour) return !printf("NO\n");

	bool f2=false;
	if (n>=2 && a[0]=='0' && a[1]=='0') f2=true;
	if (n>=2 && a[n-1]=='0'&&a[n-2]=='0') f2=true;
	for (int i=0; i+2<n;++i){
		if (a[i]=='0'&&a[i+1]=='0'&&a[i+2]=='0') f2=true;
	}
	if (f2) return !printf("NO\n");
	printf("YES\n");
}
