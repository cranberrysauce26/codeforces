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
typedef long double ld;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
const int MAX = 205, LOG = 15;

ld M[LOG][MAX][MAX];
int n, q;
ii pnts[MAX];
inline bool collinear(int i, int j, int k) {
    return (pnts[k].second - pnts[j].second) *
               (pnts[j].first - pnts[i].first) ==
           (pnts[k].first - pnts[j].first) * (pnts[j].second - pnts[i].second);
}

int ds[MAX], dsz[MAX];

void precompute() {
    vector<int> lines;
    for (int i = 0; i < n; ++i) {
        lines.clear();
        for (int j = 0; j < n; ++j) {
            ds[j] = j;
            dsz[j] = 2;
        }

        for (int j = 0; j < n; ++j) {
            if (i != j) {
                for (int k : lines) {
                    if (collinear(i, j, k)) {
                        ds[j] = k;
                        ++dsz[k];
                    }
                }
                if (ds[j] == j) {
                    lines.push_back(j);
                }
            }
        }
        M[0][i][i] = 1;
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            M[0][i][j] = ld(1) / ld(szof(lines) * dsz[ds[j]]);
            M[0][i][i] -= M[0][i][j];
        }
    }
#ifdef LOCAL
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            DEBUG("%Lf ", M[0][i][j]);
        }
        DEBUG("\n");
    }
#endif
    for (int lg = 1; lg < LOG; ++lg) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    M[lg][i][j] =
                        M[lg][i][j] + M[lg - 1][i][k] * M[lg - 1][k][j];
                }
            }
        }
    }
}

ld res[MAX], tmp[MAX];

void generate(int u, int pow) {
    for (int i = 0; i < n; ++i) {
        res[i] = tmp[i] = 0;
    }
    res[u] = 1;
    for (int k = 0; k < LOG; ++k) {
        if (pow & (1 << k)) {
            for (int i = 0; i < n; ++i) {
                tmp[i] = res[i];
                res[i] = 0;
            }
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < n; ++c) {
                    res[r] += M[k][r][c] * tmp[c];
                }
            }
        }
    }
}

vector<vector<int>> all_lines;
bool used[MAX][MAX];
void locate_all_lines() {
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u == v) {
                continue;
            }
            if (!used[u][v]) {
                all_lines.push_back({});
                all_lines.back().push_back(u);
                all_lines.back().push_back(v);
                for (int w = 0; w < n; ++w) {
                    if (w != v && w != u && collinear(u, v, w)) {
                        all_lines.back().push_back(w);
                    }
                }
                for (int w1 : all_lines.back()) {
                    for (int w2 : all_lines.back()) {
                        used[w1][w2] = true;
                    }
                }
            }
        }
    }
#ifdef LOCAL
    for (auto l : all_lines) {
        DEBUG("line: ");
        for (int v : l) {
            DEBUG("%d ", v);
        }
        DEBUG("\n");
    }
#endif
}

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &pnts[i].first, &pnts[i].second);
    }
    locate_all_lines();
    precompute();
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int u, m;
        scanf("%d%d", &u, &m);
        --u;
        generate(u, m - 1);
        DEBUG("destination is %d, vector is: ", u);
#ifdef LOCAL
        for (int v = 0; v < n; ++v) {
            DEBUG("%Lf ", res[v]);
        }
        DEBUG("\n");
#endif
        ld ans = 0;
        for (auto l : all_lines) {
            ld sum = 0;
            for (int v : l) {
                sum += res[v];
            }
            sum /= ld(szof(l));
            ans = max(ans, sum);
        }
        cout << std::setprecision(10) << std::fixed << ans << "\n";
    }
}