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

void mmain() {
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    int k = 0;
    char pre = '*';
    for (int i = 0; i < n; ++i) {
        char c;
        scanf(" %c", &c);
        if (c == '*') {
            pre = '*';
        } else {
            if (pre == '*') {
                if (a < b) swap(a, b);
                if (a > 0) {
                    --a;
                    ++k;
                    pre = 'A';
                }
            } else if (pre == 'A') {
                if (b > 0) {
                    --b;
                    ++k;
                    pre = 'B';
                } else {
                    pre = '*';
                }
            } else {
                assert(pre == 'B');
                if (a > 0) {
                    --a;
                    ++k;
                    pre = 'A';
                } else {
                    pre = '*';
                }
            }
        }
    }
    printf("%d\n", k);
}

int main() {
#ifdef LOCAL
    clock_t begin = clock();
    printf("*********Starting program*********\n\n");
    freopen("data.txt", "r", stdin);
#endif
    mmain();
#ifdef LOCAL
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime taken: %lf\n", elapsed_secs);
#endif
}