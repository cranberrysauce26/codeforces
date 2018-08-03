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
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
template <typename T>
using minheap = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxheap = priority_queue<T>;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

void mmain() {
    int n, k;
    scanf("%d%d", &n, &k);
    int g = 0;
    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%d", &a);
        a %= k;
        a = gcd(a, k);
        g = gcd(a, g);
    }
    g = gcd(g, k);
    if (g == 0) {
        // Can this even happen?
        printf("1\n0\n");
        return;
    }
    DEBUG("g = %d\n", g);
    printf("%d\n", k % g == 0 ? k / g : k / g + 1);
    // a * g >= k, a >= k/g
    for (int x = 0; x < k; x += g) {
        printf("%d ", x);
    }
    // Reread the problem statement!
    // Check base cases! Does it work for n = 1?
    // Check for integer overflow! Are you using int instead of ll?
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