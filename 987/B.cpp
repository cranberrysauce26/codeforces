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
int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    int x, y;

    scanf("%d%d", &x, &y);

    if (x == y) {
        printf("=\n");
        return 0;
    }

    if (x > 2 && y > 2) {
        if (x < y) {
            printf(">\n");
        } else {
            printf("<\n");
        }
        return 0;
    }

    // case work on x
    if (x == 1) {
        assert(y > 1);
        printf("<\n");
    } else if (x == 2) {
        if (y == 1) {
            printf(">\n");
        } else if (y == 3) {
            printf("<\n");
        } else if (y == 4) {
            printf("=\n");
        } else {
            printf(">\n");
        }
    } else if (x == 3) {
        assert(y == 1 || y == 2);
        printf(">\n");
    } else if (x == 4) {
        assert(y == 1 || y == 2);
        if (y == 1) {
            printf(">\n");
        } else {
            printf("=\n");
        }
    } else {
        assert(y == 1 || y == 2);
        assert(x > 4);
        if (y == 1) {
            printf(">\n");
        } else {
            printf("<\n");
        }
    }
}