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

set<pair<ll, int>> visit;
unordered_set<ll> dests;

void dfs(ll x, int rem) {
    visit.insert({x, rem});
    if (rem > 0) {
        if (visit.find(make_pair(x + 1, rem - 1)) == visit.end()) {
            dfs(x + 1, rem - 1);
        }
        if (visit.find(make_pair(x + 5, rem - 1)) == visit.end()) {
            dfs(x + 5, rem - 1);
        }
        if (visit.find(make_pair(x + 10, rem - 1)) == visit.end()) {
            dfs(x + 10, rem - 1);
        }
        if (visit.find(make_pair(x + 50, rem - 1)) == visit.end()) {
            dfs(x + 50, rem - 1);
        }
    } else {
        // DEBUG("dest = %lld\n", x);
        // ++cnt;
        dests.insert(x);
    }
}

void mmain() {
    // int lastans = 0;
    int n;
    scanf("%d", &n);
    vector<int> small = {0,   4,   10,  20,  35,  56,  83,  116,
                         155, 198, 244, 292, 341, 390, 439, 488};
    if (n <= 15) {
        printf("%d\n", small[n]);
    } else {
        printf("%d\n", 49LL * (n - 15) + small[15]);
    }

    ll x = 5;
    int y = x;

    // dfs(0, 200);
    // int ans = dests.size();
    // if (ans == 49LL * (200 - 15) + small[15]) {
    //     printf("cool\n");
    // } else {
    //     printf("no\n");
    // }
    // for (int n = 1; n <= 200; ++n) {
    //     visit.clear();
    //     dests.clear();
    //     dfs(0, n);
    //     // printf("%d, ", szof(dests));
    //     printf("n = %d, ans = %d, delta = %d\n", n, szof(dests),
    //            szof(dests) - lastans);
    //     lastans = szof(dests);
    // }
    // int n;
    // scanf("%d", &n);
    // if (n <=)
    // dfs(0, n);
    // cout << dests.size() << "\n";
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