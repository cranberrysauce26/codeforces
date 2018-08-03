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
    int n, m;

    scanf("%d%d", &n, &m);
    vector<int> events;
    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        events.push_back(l);
        events.push_back(r + 1);
    }

    for (int i = 0; i < n; ++i) {
        printf("%d", i & 1);
    }
    printf("\n");
    return;

    events.push_back(1);
    events.push_back(n + 1);
    sort(allof(events));
    events.erase(unique(allof(events)), end(events));
    int lastxtra = -1;
    for (int i = 0; i < szof(events) - 1; ++i) {
        int l = events[i], r = events[i + 1];
        // printf("l = %d, r = %d\n", l, r);
        int sz = r - l;

        if (sz % 2 == 0) {
            for (int j = 0; j < sz / 2; ++j) printf("0");
            for (int j = 0; j < sz / 2; ++j) printf("1");
            lastxtra = -1;
        } else {
            if (lastxtra == 0) {
                // add an extra 1
                for (int j = 0; j <= sz / 2; ++j) printf("1");
                for (int j = 0; j < sz / 2; ++j) printf("0");
                lastxtra = 1;
            } else {
                for (int j = 0; j <= sz / 2; ++j) printf("0");
                for (int j = 0; j < sz / 2; ++j) printf("1");
                lastxtra = 0;
            }
        }

        // for (int j = 0; j < sz; ++j) {
        //     if (j < sz / 2)
        //         printf("%d", i & 1);
        //     else
        //         printf("%d", (i & 1) ^ 1);
        // }
        // printf("\n");
        // for (int x = l; x < r; ++x) {
        //     if (x - l <= r - x)
        //         printf("%d", i & 1);
        //     else
        //         printf("%d", (i & 1) ^ 1);
        // }
    }
    printf("\n");
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