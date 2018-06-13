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
int n, p;
char s[2005], ans[2005];
int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    scanf("%d %d %s", &n, &p, s);

    bool works = false;

    for (int q = 0; q < p; ++q) {
        int n0 = 0, n1 = 0, nx = 0;
        for (int i = q; i < n; i += p) {
            if (s[i] == '1') {
                ++n1;
            } else if (s[i] == '0') {
                ++n0;
            } else {
                ++nx;
            }
        }
        if (n1 != 0 && n0 != 0) {
            // always possible
            for (int i = q; i < n; i += p) {
                if (s[i] != '.') {
                    ans[i] = s[i];
                } else {
                    ans[i] = '0';
                }
            }
            works = true;
        } else {
            // at most 1 colour
            if (n1 == 0 && n0 == 0) {
                // no colours
                for (int i = q, cnt = 0; i < n; i += p, cnt ^= 1) {
                    ans[i] = '0' + cnt;
                }
                if (nx > 1) {
                    works = true;
                }
            } else {
                // exactly 1 colour
                if (nx == 0) {
                    // no dots
                    for (int i = q; i < n; i += p) {
                        ans[i] = s[i];
                    }
                } else {
                    // one colour and some dots
                    char target = n0 == 0 ? '0' : '1';
                    for (int i = q; i < n; i += p) {
                        if (s[i] == '.') {
                            ans[i] = target;
                        } else {
                            ans[i] = s[i];
                        }
                    }
                    works = true;
                }
            }
        }
    }
    if (!works) {
        printf("No\n");
    } else {
        printf("%s\n", ans);
    }
}