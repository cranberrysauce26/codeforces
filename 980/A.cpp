#include <cstdio>
#include <cstring>
char c[500];
int main() {
	int np = 0;
	scanf(" %s", c);
	int n = strlen(c);	
	for (int i = 0; i < n; ++i) if (c[i] == 'o') ++np;
	if (np==0) printf("YES\n");
	else if ((n-np)%np == 0) printf("YES\n");
	else printf("NO\n");
}
