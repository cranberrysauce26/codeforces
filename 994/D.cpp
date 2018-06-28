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

int n, m;
ii s[2][20];

vector<ii> good_choices;
set<int> good;

bool intersect(ii a, ii b, int &val) {
    val = -1;
    if (a.first==b.first) {
        val = a.first;
    }
    if (a.first==b.second) {
        if (val!=-1) {
            return false;
        }
        val = a.first;
    }
    if (a.second==b.first) {
        if (val!=-1) {
            return false;
        }
        val = a.second;
    }
    if (a.second==b.second) {
        if (val!=-1) {
            return false;
        }
        val = a.second;
    }
    if (val==-1) return false;
    return true;
}

void find_good() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int val;
            if (intersect(s[0][i], s[1][j], val)) {
                DEBUG("adding val = %d, first is (%d, %d) second is (%d, %d)\n", val, s[0][i].first, s[0][i].second, s[1][j].first, s[1][j].second);
                good.insert(val);
            }
        }
    }
}

bool check2() {
    for (int i = 0; i < n; ++i) {
        set<int> all;
        for (int j = 0; j < m; ++j) {
            int val;
            if (intersect(s[0][i], s[1][j], val)) {
                all.insert(val);
            }
        }
        DEBUG("i = %d. all: ", i);
        for (int x : all) {
            DEBUG("%d ", x);
        }
        DEBUG("\n");
        if (szof(all) > 1) {
            return false;
        }
    }

    for (int j = 0; j < m; ++j) {
        set<int> all;
        for (int i = 0; i < n; ++i) {
            int val;
            if (intersect(s[0][i], s[1][j], val)) {
                all.insert(val);
            }
        }
        if (szof(all) > 1) {
            return false;
        }
    }
    return true;
}

void mmain() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &s[0][i].first, &s[0][i].second);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &s[1][i].first, &s[1][i].second);
    }
    find_good();
    if (szof(good) == 1) {
        printf("%d\n", *good.begin());
        return;
    }
    if (check2()) {
        printf("0\n");
        return;
    }
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