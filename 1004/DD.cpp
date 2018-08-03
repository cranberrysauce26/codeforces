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
const int MAX = 1e6 + 10;
int freq[MAX];

bool solve(vi order) {
    DEBUG("******SOLVING********\n");
    bool works = true;
    vi d(4, -1);
    int nborders = 0;
    auto compute_expected = [&](int k) {
        int ans = 0;
        for (int i = 0; i < 4; ++i) {
            int dd = d[(i + 1) % 4];
            int hi = k, lo = 1;

            if (d[i] != -1) {
                hi = min(hi, d[i] - 1);
            }

            if (dd != -1) {
                lo = max(lo, k - dd + 1);
            }

            ans += max(0, hi - lo + 1);
        }
        // DEBUG("expected(%d) = %d, dists = %d %d %d %d\n", k, ans, d[0], d[1],
        //   d[2], d[3]);
        return ans;
    };
    for (int i = 1; i < MAX;) {
        // compute expected
        int expected = compute_expected(i);
        if (freq[i] != expected) {
            if (nborders == 4) {
                works = false;
                break;
            } else {
                d[order[nborders]] = i;
                ++nborders;
            }
        } else {
            ++i;
        }
    }
    if (works) {
        DEBUG("WORKS!!\n");
        int nrows = d[1] + d[3] - 1;
        int ncols = d[0] + d[2] - 1;
        int row = d[1];
        int col = d[0];
        printf("%d %d\n%d %d\n", nrows, ncols, row, col);
    }
    return works;
}

void mmain() {
    int t;
    scanf("%d", &t);
    for (int i = 0, a; i < t; ++i) {
        scanf("%d", &a);
        ++freq[a];
    }
    if (freq[0] != 1) {
        printf("-1\n");
        return;
    }
    if (solve({0, 1, 2, 3})) return;
    if (solve({0, 1, 3, 2})) return;
    if (solve({0, 2, 1, 3})) return;
    printf("-1\n");
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