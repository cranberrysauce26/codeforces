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

void mmain() {
    // Reread the problem statement!
    // Check base cases! Does it work for n = 1?
    // Check for integer overflow! Are you using int instead of ll?
    int n;
    scanf("%d", &n);
    vi a(n);
    map<int, vi> positions;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        positions[a[i]].push_back(i);
    }
    vi lo, hi;
    for (auto x : positions) {
        lo.push_back(x.second[0]);
        hi.push_back(x.second.back());
    }
    sort(allof(lo));
    sort(allof(hi));
    ll cnt = 0;
    for (int i = 0; i < szof(lo); ++i) {
        auto it = upper_bound(allof(hi), lo[i]);
        cnt += 1LL * (end(hi) - it);
    }
    cout << cnt << "\n";
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