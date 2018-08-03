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

struct segnode {
    ii data;
    segnode *l, *r;
    segnode() : data({0, 0}), l(nullptr), r(nullptr) {}
    segnode(int left, int val, segnode *childl, segnode *childr)
        : data({left, val}), l(childl), r(childr) {}
    segnode(segnode *left, segnode *right) {
        l = left;
        r = right;
    }
    segnode(segnode *copy) { l = copy->l, r = copy->r, data = copy->data; }
};

typedef segnode *psegnode;

psegnode update(psegnode u, int tl, int tr, int a, int b, int val) {
    // update by adding interval [a, b]
    DEBUG("updating(u = %d, %d, %d, %d, %d, %d)\n", u, tl, tr, a, b, val);
    if (a <= tl && tr <= b) {
        psegnode node;
        DEBUG("Reached base case\n");
        if (u->data.first < a) {
            node = new segnode(a, val, u->l, u->r);
        } else {
            node = new segnode(u);
        }
        DEBUG("    setting data = (%d, %d)\n", node->data.first,
              node->data.second);
        return node;
    } else {
        int tm = (tl + tr) / 2;
        psegnode left, right;
        if (a <= tm) {
            left = update(u->l, tl, tm, a, b, val);
        } else {
            left = u->l;
        }
        if (tm + 1 <= b) {
            right = update(u->r, tm + 1, tr, a, b, val);
        } else {
            right = u->r;
        }
        psegnode node = new segnode(u);
        node->l = left;
        node->r = right;
        return node;
    }
}

int query(psegnode u, int tl, int tr, int a, int b) {
    DEBUG("QUERY(u, %d, %d, %d, %d), u->data = (%d, %d)\n", tl, tr, a, b,
          u->data.first, u->data.second);
    if (u->data.first >= a) {
        return u->data.second;
    }
    if (tl == tr) {
        return 0;
    }
    int tm = (tl + tr) / 2;
    if (b <= tm) {
        return query(u->l, tl, tm, a, b);
    } else {
        return query(u->r, tm + 1, tr, a, b);
    }
}

psegnode build(int tl, int tr) {
    if (tl == tr) {
        return new segnode();
    } else {
        int tm = (tl + tr) / 2;
        return new segnode(build(tl, tm), build(tm + 1, tr));
    }
}

const int MAXN = 5e5 + 5, MAXVAL = 5e5 + 5;
vector<int> histogram[MAXVAL];
int n;
minheap<pair<ii, ii>> ranges;

psegnode tree[MAXN];

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
    tree[0] = build(1, n);
    for (int i = 1; i <= n; ++i) {
        DEBUG("i = %d\n", i);
        auto prev = tree[i - 1];
        while (!ranges.empty() && ranges.top().first.first == i) {
            DEBUG(
                "\n****** Calling update for (%d, %d) val = %d, prev = %d\n\n",
                ranges.top().first.second, ranges.top().second.first,
                ranges.top().second.second, prev);
            prev =
                update(prev, 1, n, ranges.top().first.second,
                       ranges.top().second.first, ranges.top().second.second);
            DEBUG("prev->data = (%d, %d), prev = %d\n", prev->data.first,
                  prev->data.second, prev);
            ranges.pop();
        }
        tree[i] = prev;
        DEBUG("After updating tree[%d], data for root is (%d, %d)\n", i,
              tree[i]->data.first, tree[i]->data.second);
    }

    int q;
    scanf("%d", &q);
    DEBUG("STARTING QUERIES\n");
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        int ans = query(tree[l], 1, n, l, r);
        printf("%d\n", ans);
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