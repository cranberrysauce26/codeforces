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

int seq[100];
bool isf[100];
int n, m;

void mmain() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", seq+i);
    }
    for (int i = 0; i < m; ++i) {
        int x; scanf("%d", &x);
        isf[x] = true;
    }
    for (int i = 0; i < n; ++i) {
        if (isf[seq[i]]) {
            printf("%d ", seq[i]);
        }
    }
    printf("\n");
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