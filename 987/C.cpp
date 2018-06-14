#include <bits/stdc++.h>
#define LOCAL
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
const int MAXN = 3005, INF = 1e9;
int n, s[MAXN], c[MAXN];

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", s + i);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", c + i);
    }
    int ans = INF;
    for (int i = 1; i < n - 1; ++i) {

        int minl = INF, minr = INF;

        for (int j = 0; j < i; ++j) {
            if (s[j] < s[i]) {
                minl = min(minl, c[j]);
            }
        }
        for (int j = i+1; j < n; ++j) {
            if (s[j] > s[i]) {
                minr = min(minr, c[j]);
            }
        }

        if (minl != INF && minr != INF) {
            ans = min(ans, minl+minr+c[i]);
        }
    }
    if (ans==INF) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
}