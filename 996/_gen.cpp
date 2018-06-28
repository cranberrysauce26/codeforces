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
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;

void random_tree(int n) {
    vector<ii> edges;
    vi dest(n);
    for (int i = 0; i < n; ++i) dest[i] = i;
    random_shuffle(allof(dest));

    vi src;
    src.push_back(dest.back());
    dest.pop_back();
    while (!dest.empty()) {
        int i = rand() % szof(src);
        int a = src[i];
        int b = dest.back();
        dest.pop_back();
        edges.push_back({a, b});
        src.push_back(b);
    }

    // this is 0-indexed
    // convert to 1-indexed if necessary
}

int main() {
    freopen("data.txt", "w", stdout);
    srand(time(NULL));
    int n = 1e5;
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        int x = rand();
        assert(x >= 0);
        printf("%d\n", x);
    }
}