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
const int MAXN = 2e5 + 5;
int n;
ll freq[MAXN];

void mmain() {
    scanf("%d", &n);
    vector<pair<ll, int>> events;
    for (int i = 0; i < n; ++i) {
        // scanf("%lld %lld", &I[i].first, &I[i].second);
        ll start, end;
        scanf("%lld %lld", &start, &end);
        events.push_back({start, 1});
        events.push_back({end+1, -1});
    }
    sort(allof(events));
    int cur = 0;
    ll lastx = -1;
    for (auto e : events) {
        if (lastx != -1) {
            freq[cur] += e.first - lastx;
        }
        cur += e.second;
        lastx = e.first;
    }
  
    for (int i = 1; i <= n; ++i) {
        printf("%lld", freq[i]);
        if (i != n) {
            printf(" ");
        } else {
            printf("\n");
        }
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