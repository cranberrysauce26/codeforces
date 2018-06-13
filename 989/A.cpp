#include <bits/stdc++.h>
// #define LOCAL
#ifdef LOCAL
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

using namespace std;
#define szof(v) ((int)(v).size())
#define allof(v) begin(v), end(v)
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

char s[105];

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    scanf(" %s", s);
    int n = strlen(s);
    for (int i = 1; i < n - 1; ++i) {
        if (s[i - 1] != '.' && s[i] != '.' && s[i + 1] != '.' &&
            s[i - 1] != s[i] && s[i] != s[i + 1] && s[i - 1] != s[i + 1]) {
            printf("Yes\n");
            return 0;
        }
    }
    printf("No\n");
    return 0;
}