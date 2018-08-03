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
multiset<string> a[5], b[5];
void mmain() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        a[szof(s)].insert(s);
    }
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        b[szof(s)].insert(s);
    }
    int cnt = 0;
    for (int sz = 1; sz <= 4; ++sz) {
        assert(szof(a[sz]) == szof(b[sz]));
        for (auto it = a[sz].begin(); it != a[sz].end();) {
            auto j = b[sz].find(*it);
            if (j != b[sz].end()) {
                b[sz].erase(j);
                it = a[sz].erase(it);
            } else {
                ++it;
            }
        }
        assert(szof(a[sz]) == szof(b[sz]));
        cnt += szof(a[sz]);
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