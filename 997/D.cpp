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

const ll MOD = 1e9 + 7;

/**
 * Compute the number of cycles of length a in a tree T.
 * Is this correct?
 *
 * Definition: A cycle is any sequence of positive length u1, u2, ..., uk
 * such that u[i] is adjacent to u[i+1] for each i (for k, it's cyclic).
 *
 * Given any cycle in T1xT2, it can be decomposed into a cycle in T1 and a cycle
 * in T2. There are an additional (k choose |cycle in T1|) ways to arrange it.
 * Proof: There are k spots. |cyc1| of them are of type 1, the rest are type 2.
 *
 * So you need to compute the number of cycles of length a in a tree for each
 * even a 0 <= a <= 75. The size of the tree is 4000.
 *
 * OK...
 * For each cycle, it has a top vertex. Then it can be shifted a times and also
 * reversed. So count it 2*a times. So let u be the top vertex.
 * Then say u has children v1, v2, ..., v[c]. Then choose x of these children,
 * and you get 2*x+sum of subs in x that sum to a - 2*x.
 * Maybe dp on the children?
 * Let f(i, j) be the number of ways to make a sum of j using the first i.
 * Then f(i, j) = sum f(i-1,)
 */

vector<ll> solve(const vector<vi> &t, int k) {
    int n = szof(t);
    vi par(n);
    function<void(int, int)> dfs = [&](int u, int p) {
        par[u] = p;
        for (int v : t[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
    };
    dfs(0, -1);
    vector<ll> dp(k + 1);
    vector<vector<ll>> f(k + 1, vector<ll>(n));
    fill(allof(f[0]), 1);
    for (int l = 1; l <= k; ++l) {
        dp[l] = 0;
        for (int u = 0; u < n; ++u) {
            ll cur = 0;
            for (int last = 1; last < l; ++last) {
                // 2 * last actually
                cur += dp[l - last] * f[last][u] % MOD;
                cur %= MOD;
                DEBUG(
                    "l = %d, cur now %lld, dp[l-last] = %lld, f[last][u] = "
                    "%lld\n",
                    l, cur, dp[l - last], f[last][u]);
            }
            dp[l] += cur;
            dp[l] %= MOD;
            for (int v : t[u]) {
                if (v != par[u]) {
                    cur += f[l - 1][v];
                    cur %= MOD;
                    DEBUG("u = %d, l = %d, v = %d, cur now %lld\n", u, l, v,
                          cur);
                }
            }
            // f[u][l] = cur;
            f[l][u] = cur;
        }
    }
    vector<ll> ans(k + 1);
    for (int i = 0; i < k + 1; ++i) {
        for (int u = 0; u < n; ++u) {
            ans[i] += f[i][u];
            ans[i] %= MOD;
        }
    }
    return ans;
}

struct chooser {
    chooser(int mx) {
        factorial.resize(mx + 1);
        invfactorial.resize(mx + 1);
        factorial[0] = 1LL;
        invfactorial[0] = 1LL;
        for (int i = 1; i <= mx; ++i) {
            factorial[i] = factorial[i - 1] * i % MOD;
            invfactorial[i] = pow(factorial[i], MOD - 2);
            DEBUG("factorial[%d] = %lld, inv = %lld\n", i, factorial[i],
                  invfactorial[i]);
        }
    }

    ll pow(ll n, ll e) {
        if (e == 0) return 1LL;
        ll h = pow(n, e / 2);
        h = h * h % MOD;
        if (e % 2 == 0) return h;
        return h * n % MOD;
    }

    int choose(int n, int k) {
        int ans = (int)(factorial[n] * invfactorial[k] % MOD *
                        invfactorial[n - k] % MOD);
        DEBUG("%d choose %d = %d\n", n, k, ans);
        return ans;
    }

    vector<ll> factorial, invfactorial;
};

void mmain() {
    int n1, n2, k;
    scanf("%d%d%d", &n1, &n2, &k);
    if (k & 1) {
        printf("0\n");
        return;
    }
    DEBUG("over here\n");
    k /= 2;
    vector<vi> t1, t2;
    t1.resize(n1);
    for (int i = 0; i < n1 - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        t1[u].push_back(v);
        t1[v].push_back(u);
    }
    t2.resize(n2);
    for (int i = 0; i < n2 - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        t2[u].push_back(v);
        t2[v].push_back(u);
    }
    DEBUG("Finished inputting\n");
    auto dp1 = solve(t1, k);
    auto dp2 = solve(t2, k);

    chooser choose(k);
    ll ans = 0;
    for (int a = 0; a <= k; ++a) {
        ll left = dp1[a];
        ll right = dp2[k - a];
        DEBUG("a=%d, left =%lld, right = %lld\n", a, left, right);
        ans += left * right % MOD * choose.choose(k, a) % MOD * 4 * a % MOD;
        ans %= MOD;
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