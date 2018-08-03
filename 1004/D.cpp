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
const int MAX = 1e6 + 6;
ll freq[MAX];

void mmain() {
    // Reread the problem statement!
    // Check base cases! Does it work for n = 1?
    // Check for integer overflow! Are you using int instead of ll?
    int t;
    scanf("%d", &t);
    if (t == 1) {
        printf("1 1\n1 1\n");
        return;
    }
    for (int i = 0; i < t; ++i) {
        int a;
        scanf("%d", &a);
        freq[a]++;
    }
    vector<int> perm = {0, 1, 2};
    do {
        vector<ll> dists;
        for (ll x = 1; x < MAX;) {
            assert(szof(dists) < 4);
            ll want = x * 4;
            for (int i = 0; i < szof(dists); ++i) {
                if (i == 0) {
                    ll take = 2LL * (x - dists[i]) + 1LL;
                    if (szof(dists) > 1 && (x - dists[i] + 1) > dists[1]) {
                        take -= (x - dists[i] + 1) - dists[1];
                    }
                    want -= take;
                } else if (i == 2) {
                    ll take = 2LL * (x - dists[i]) + 1LL;
                    if ((x - dists[i] + 1) > dists[i - 1]) {
                        take -= (x - dists[i] + 1) - dists[i - 1];
                    }
                    want -= take;
                } else {
                    // i == 1
                    // both sides :(
                    ll take = 2LL * (x - dists[i]) + 1LL;
                    if ((x - dists[i] + 1) > dists[0]) {
                        take -= (x - dists[i] + 1) - dists[0];
                    }
                    if (szof(dists) >= 3 && (x - dists[i] + 1) > dists[2]) {
                        take -= (x - dists[i] + 1) - dists[2];
                    }
                    want -= take;
                }
            }

            if (freq[x] == want) {
                ++x;
            } else {
                dists.push_back(x);
                if (szof(dists) == 4) break;
            }

            // DEBUG("x = %lld\n", x);
            // ll expected, exp0, exp1, exp2, exp3;
            // exp0 = 4 * x;
            // if (szof(dists) >= 1) {
            //     exp1 = exp0 - 2LL * (x - dists[0]) - 1LL;
            //     DEBUG("    exp1 = %lld\n", exp1);
            // }
            // if (szof(dists) >= 2) {
            //     exp2 = exp1 - 2LL * (x - dists[1]) - 1LL;
            //     DEBUG("     exp2 = %lld\n", exp2);
            // }
            // if (szof(dists) >= 3) {
            //     assert(szof(dists) == 3);
            //     exp3 = exp2 - 2LL * (x - dists[2]) - 1LL;
            //     DEBUG("     exp3 = %lld\n", exp3);
            // }

            // if (szof(dists) == 0) {
            //     expected = exp0;
            // } else if (szof(dists) == 1) {
            //     expected = exp1;
            // } else if (szof(dists) == 2) {
            //     expected = exp2;
            // } else {
            //     expected = exp3;
            // }

            // // printf("x = %lld, expected = %lld, szof(dists) == %d\n", x,
            // // expected,
            // //        szof(dists));

            // if (freq[x] == expected) {
            //     // printf("x = %lld, all normal\n", x);
            //     ++x;
            // } else {
            //     // printf("x = %lld, hit boundary\n", x);

            //     // hit a boundary
            //     dists.push_back(x);
            //     if (szof(dists) == 4) break;
            // }
        }
    } while (next_permutation(allof(perm)));
    vector<ll> dists;
    for (ll x = 1; x < MAX;) {
        DEBUG("x = %lld\n", x);
        ll expected, exp0, exp1, exp2, exp3;
        exp0 = 4 * x;
        if (szof(dists) >= 1) {
            exp1 = exp0 - 2LL * (x - dists[0]) - 1LL;
            DEBUG("    exp1 = %lld\n", exp1);
        }
        if (szof(dists) >= 2) {
            exp2 = exp1 - 2LL * (x - dists[1]) - 1LL;
            DEBUG("     exp2 = %lld\n", exp2);
        }
        if (szof(dists) >= 3) {
            assert(szof(dists) == 3);
            exp3 = exp2 - 2LL * (x - dists[2]) - 1LL;
            DEBUG("     exp3 = %lld\n", exp3);
        }

        if (szof(dists) == 0) {
            expected = exp0;
        } else if (szof(dists) == 1) {
            expected = exp1;
        } else if (szof(dists) == 2) {
            expected = exp2;
        } else {
            expected = exp3;
        }

        // printf("x = %lld, expected = %lld, szof(dists) == %d\n", x, expected,
        //        szof(dists));

        if (freq[x] == expected) {
            // printf("x = %lld, all normal\n", x);
            ++x;
        } else {
            // printf("x = %lld, hit boundary\n", x);

            // hit a boundary
            dists.push_back(x);
            if (szof(dists) == 4) break;
        }
    }

    for (int i = 0; i <= 6; ++i) {
        printf("freq[%d]: %d\n", i, freq[i]);
    }
    // Now there are 4! cases
    // Do each?
    ll totdist = dists[0] + dists[1] + dists[2] + dists[3];
    int i1, i2;
    bool found = false;
    for (i1 = 0; i1 < 4; ++i1) {
        for (i2 = i1 + 1; i2 < 4; ++i2) {
            ll x = dists[i1] + dists[i2] - 1;
            ll x2 = totdist - (dists[i1] + dists[i2]) - 1;
            if (x * x2 == t) {
                // yay
                found = true;
                break;
            }
        }
    }
    if (!found) {
        printf("-1\n");
        return;
    }

    ll n = dists[i1] + dists[i2] - 1;
    ll m = totdist - (dists[i1] + dists[i2]) - 1;
    ll i = dists[i1];
    ll j;
    for (int i = 0; i < 4; ++i) {
        if (i != i1 && i != i2) {
            j = dists[i];
            break;
        }
    }
    printf("%lld %lld\n%lld %lld\n", n, m, i, j);
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