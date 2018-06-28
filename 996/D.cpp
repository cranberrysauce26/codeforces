#pragma GCC optimize("O3")
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
typedef vector<int> vi;
const int MAXN = 105;
int n, a[2 * MAXN];
void mmain() {
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; ++i) {
        scanf("%d", a + i);
    }
    int cnt = 0;
    for (int i = 1; i <= 2 * n; i += 2) {
        int j = i + 1;
        while (j <= 2 * n && a[j] != a[i]) ++j;
        DEBUG("i = %d, j = %d, colour = %d\n", i, j, a[i]);
        for (int k = j; k > i + 1; --k) {
            swap(a[k], a[k - 1]);
            ++cnt;
            DEBUG(" incremented cnt = %d\n", cnt);
        }
    }
    printf("%d\n", cnt);
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