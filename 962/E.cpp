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

const ll INF = 1e15;

void mmain() {
    int n;
    scanf("%d", &n);
    ll lastp = -INF, lastb = -INF, maxgapb = 0, lastr = -INF, maxgapr = 0;
    ll firstr = -INF, firstb = -INF;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ll x;
        char c;
        scanf("%lld %c", &x, &c);
        DEBUG("%lld %c\n", x, c);
        DEBUG("cur ans = %lld\n", ans);
        if (c == 'R') {
            if (firstr == -INF) {
                firstr = x;
            }
            ll gap;
            if (lastp == -INF) {
                // gap doesn't matter
                // don't update lastr
            } else {
                if (lastr <= lastp) {
                    gap = x - lastp;
                } else {
                    gap = x - lastr;
                }
                maxgapr = max(maxgapr, gap);
            }
            lastr = x;
        } else if (c == 'B') {
            if (firstb == -INF) {
                firstb = x;
            }
            // corresponding
            ll gap;
            if (lastp == -INF) {
                // gap doesn't matter
                // don't update lastr
            } else {
                if (lastb <= lastp) {
                    gap = x - lastp;
                } else {
                    gap = x - lastb;
                }
                maxgapb = max(maxgapb, gap);
            }
            lastb = x;
        } else {
            assert(c == 'P');
            maxgapb = max(maxgapb, x - lastb);
            maxgapr = max(maxgapr, x - lastr);
            if (lastp == -INF) {
                // just add it
                if (firstb != -INF) {
                    ans += x - firstb;
                }
                if (firstr != -INF) {
                    ans += x - firstr;
                }
            } else {
                if (lastb == -INF && lastr == -INF) {
                    ans += x - lastp;
                    DEBUG("over here\n");
                } else if (lastb == -INF) {
                    ans += 2 * (x - lastp) - maxgapr;
                } else if (lastr == -INF) {
                    ans += 2 * (x - lastp) - maxgapb;
                } else {
                    maxgapb = max(maxgapb, x - lastb);
                    maxgapr = max(maxgapr, x - lastr);
                    ans += min(2*(x-lastp), 3*(x-lastp) - maxgapb - maxgapr);
                    DEBUG("x = %lld, lastp = %lld, maxgapb = %lld, maxgapr = %lld\n", x, lastp, maxgapb, maxgapr);
                }
            }
            maxgapb = 0;
            maxgapr = 0;

            lastb = -INF;
            lastr = -INF;

            lastp = x;
        }
    }

    if (lastr != -INF) {
        assert(firstr!=-INF);
        if (lastp == -INF) {
            ans += lastr - firstr;
        } else {
            ans += lastr - lastp;
        }
    }

    if (lastb != -INF) {
        assert(firstb != -INF);
        if (lastp == -INF) {
            ans += lastb - firstb;
        } else {
            ans += lastb - lastp;
        }
    }

    printf("%lld\n", ans);
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