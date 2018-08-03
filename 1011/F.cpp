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
void mmain() {
    int n;
    scanf("%d", &n);
    vector<char> type(n);
    vi init(n, -1);
    vector<vi> ch(n);
    vi par(n, -1);
    auto read = [&]() {
        char s[5];
        for (int i = 0; i < n; ++i) {
            scanf(" %s", s);
            type[i] = s[0];
            if (type[i] == 'I') {
                scanf("%d", &init[i]);
            } else if (type[i] == 'N') {
                int u;
                scanf("%d", &u);
                --u;
                ch[i].push_back(u);
                par[u] = i;
            } else {
                int u, v;
                scanf("%d%d", &u, &v);
                --u, --v;
                ch[i].push_back(u);
                ch[i].push_back(v);
                par[u] = par[v] = i;
            }
        }
    };
    read();
    DEBUG("finished reading\n");
    function<int(int)> get_init = [&](int u) {
        if (type[u] == 'N') {
            init[u] = get_init(ch[u][0]) ^ 1;
        } else if (type[u] == 'A') {
            init[u] = get_init(ch[u][0]) & get_init(ch[u][1]);
        } else if (type[u] == 'O') {
            init[u] = get_init(ch[u][0]) | get_init(ch[u][1]);
        } else if (type[u] == 'X') {
            init[u] = get_init(ch[u][0]) ^ get_init(ch[u][1]);
        }
        return init[u];
    };
    get_init(0);
#ifdef LOCAL
    for (int u = 0; u < n; ++u) {
        DEBUG("init[%d] = %d\n", u, init[u]);
    }
#endif
    vector<vi> result(n, {0, 1});
    function<void(int)> get_result = [&](int u) {
        DEBUG("u = %d, par = %d\n", u, par[u]);
        if (par[u] != -1) {
            int p = par[u];
            assert(type[p] != 'I');
            if (type[p] == 'N') {
                result[u] = {result[p][1], result[p][0]};
            } else {
                int other = ch[p][0] == u ? init[ch[p][1]] : init[ch[p][0]];
                if (type[p] == 'A') {
                    result[u] = {result[p][0], result[p][other]};
                } else if (type[p] == 'O') {
                    result[u] = {result[p][other], result[p][1]};
                } else if (type[p] == 'X') {
                    result[u] = {result[p][0 ^ other], result[p][1 ^ other]};
                }
            }
        }
        DEBUG("result[%d] = {%d, %d}\n", u, result[u][0], result[u][1]);
        for (int c : ch[u]) {
            get_result(c);
        }
    };
    get_result(0);
    for (int u = 0; u < n; ++u) {
        if (type[u] == 'I') {
            printf("%d", init[u] == 0 ? result[u][1] : result[u][0]);
        }
    }
    // Reread the problem statement!
    // Check base cases! Does it work for n = 1?
    // Check for integer overflow! Are you using int instead of ll?
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