#define LOCAL

#pragma GCC optimize("O3")
#include <bits/stdc++.h>
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

void mmain() {
    ll n;
    cin >> n;
    ll cnt = 0;
    while (n) {
        if (n >= 100) {
            cnt += n/100;
            n %= 100;
        } else if (n >= 20) {
            cnt += n/20;
            n %= 20;
        } else if (n >= 10) {
            cnt += n/10;
            n %= 10;
        } else if (n >= 5) {
            cnt += n/5;
            n %= 5;
        } else if (n >= 1) {
            cnt += n/1;
            n %= 1;
        }
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