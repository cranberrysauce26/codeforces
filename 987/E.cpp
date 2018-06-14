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
const int MAXN = 1e6+6;
int n, nxt[MAXN];
bool visit[MAXN];

int dfs(int u) {
    visit[u] = true;
    if (!visit[nxt[u]]) {
        return 1 + dfs(nxt[u]);
    }
    return 1;
}

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", nxt+i);
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visit[i]) {
            cnt += dfs(i)-1;
        }
    }

    if (cnt%2 == n%2) {
        printf("Petr\n");
    } else {
        printf("Um_nik\n");
    }
}