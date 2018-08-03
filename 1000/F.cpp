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

const int MAXN = 5e5 + 5, MAXVAL = 5e5 + 5;
vector<int> histogram[MAXVAL];
int n;
minheap<pair<ii, ii>> ranges;
ii seg[4 * MAXN];

void add(int u, int tl, int tr, int l, int r, int val) {
    if (tl > r || tr < l) return;
    if (l <= tl && tr <= r) {
        if (seg[u].first < l) {
            seg[u] = {l, val};
        }
    } else {
        int tm = (tl + tr) / 2;
        add(2 * u, tl, tm, l, r, val);
        add(2 * u + 1, tm + 1, tr, l, r, val);
    }
}

int query(int u, int tl, int tr, int a, int b) {
    if (seg[u].first >= a) {
        return seg[u].second;
    }
    if (tl == tr) {
        return 0;
    }
    int tm = (tl + tr) / 2;
    int toret;
    if (b <= tm) {
        toret = query(2 * u, tl, tm, a, b);
    } else {
        toret = query(2 * u + 1, tm + 1, tr, a, b);
    }
    return toret;
}
void mmain() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int a;
        scanf("%d", &a);
        if (histogram[a].empty()) histogram[a].push_back(0);
        histogram[a].push_back(i);
    }
    for (int a = 1; a < MAXVAL; ++a) {
        if (!histogram[a].empty()) {
            histogram[a].push_back(n + 1);
            for (int j = 1; j < szof(histogram[a]) - 1; ++j) {
                ranges.push({{histogram[a][j - 1] + 1, histogram[a][j]},
                             {histogram[a][j + 1] - 1, a}});
            }
        }
    }
    int q;
    scanf("%d", &q);
    vector<pair<ii, int>> qq(q);
    vector<int> ans(q, -1);
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &qq[i].first.first, &qq[i].first.second);
        qq[i].second = i;
    }
    sort(allof(qq));
    for (int i = 0; i < q; ++i) {
        DEBUG("Query i = %d, id = %d, l = %d, r = %d\n", i, qq[i].second,
              qq[i].first.first, qq[i].first.second);
        while (!ranges.empty() &&
               ranges.top().first.first <= qq[i].first.first) {
            DEBUG("Adding (l = %d, m = %d, r = %d, v = %d)\n",
                  ranges.top().first.first, ranges.top().first.second,
                  ranges.top().second.first, ranges.top().second.second);
            add(1, 1, n, ranges.top().first.second, ranges.top().second.first,
                ranges.top().second.second);
            ranges.pop();
        }
        int ret = query(1, 1, n, qq[i].first.first, qq[i].first.second);
        ans[qq[i].second] = ret;
    }
    for (int a : ans) {
        printf("%d\n", a);
    }
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