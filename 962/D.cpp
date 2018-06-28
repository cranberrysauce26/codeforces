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
typedef priority_queue<ll, vector<ll>, greater<ll>> minheap;
const int MAXN = 150005;
int n;
ll a[MAXN];
set<ll> twice;
map<ll, minheap> indices;
void mmain() {
    scanf("%d", &n);
    map<ll,int> freq;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", a+i);
        indices[a[i]].push(i);
        ++freq[a[i]];
    }
    for (auto pp : freq) {
        if (pp.second >= 2) {
            twice.insert(pp.first);
        }
    }
    while (!twice.empty()) {
        ll val = *twice.begin();
        auto &heap = indices[val];
        DEBUG("val = %lld, szof(heap) = %d\n", val, szof(heap));
        assert(szof(heap) >= 2);
        int i1 = heap.top(); heap.pop();
        int i2 = heap.top(); heap.pop();
        DEBUG("i1 = %d, i2 = %d, szof(heap) = %d\n", i1, i2, szof(heap));
        if (szof(heap) < 2) {
            twice.erase(twice.begin());
            DEBUG(" popping, new top is %lld\n", twice.empty() ? -1 : *twice.begin());
        }
        a[i1] = -1;
        a[i2] *= 2LL;
        indices[2LL*val].push(i2);
        if (szof(indices[2LL*val]) >= 2) {
            twice.insert(2LL*val);
        }
    }
    int cnt = 0;
    for (int i =1; i <= n; ++i) {
        if (a[i]!=-1) {
            ++cnt;
        }
    }
    printf("%d\n", cnt);
    for (int i= 1; i <= n; ++i) {
        if (a[i]!=-1) {
            printf("%lld ", a[i]);
        }
    }
    printf("\n");
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