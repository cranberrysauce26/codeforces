#include <bits/stdc++.h>
// #define LOCAL
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
int n;
ll l, w;
vector<ll> pos, neg;

bool works(int i, int j) {
    ll x1 = pos[i], x2 = neg[j];
    if (x1 > x2) {
        return false;
    }
    return (x2-x1+l)*w > abs(x1+x2+l);
}

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    cin >> n >> l >> w;
    for (int i = 0; i < n; ++i) {
        ll x;
        int v;
        cin >> x >> v;
        if (v == 1) {
            pos.push_back(x);
        } else {
            neg.push_back(x);
        }
    }
    sort(allof(pos));
    sort(allof(neg));
    int i = 0, j = 0;
    ll ans = 0;
    while (i < szof(pos)) {
        while (j < szof(neg) && !works(i, j)) {
            ++j;
        }
        ans += 1LL * (szof(neg) - j);
        ++i;
    }
    cout << ans << "\n";
}