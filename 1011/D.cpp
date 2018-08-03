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

int ntimes = 0;

inline int ask(int y) {
    ++ntimes;
    assert(ntimes <= 60);
    printf("%d\n", y);
    fflush(stdout);
    int ans;
    scanf("%d", &ans);
    if (ans == 0 || ans == -2) {
        exit(0);
    }
    assert(ans == -1 || ans == 1);
    return ans;
}

void mmain() {
    int n, m;
    scanf("%d%d", &m, &n);
    vi truth(n);
    for (int i = 0; i < n; ++i) {
        truth[i] = ask(1);
    }
    int lo = 1, hi = m, i = 0;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        int ans = ask(mid);
        ans *= truth[i];
        if (ans == 1) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
        i = (i + 1) % n;
    }
    assert(lo == hi);
    assert(ask(lo) == 0);
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