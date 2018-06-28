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
int n, k, grid[5][55], dest[105], pos[105], initial[105];
bool finished[105];
inline int cell(int x) {
    assert(0 <= x && x < 2 * n);
    if (x < n)
        return grid[1][1 + x];
    else
        return grid[2][1 + x - n];
}
void setcell(int x, int v) {
    assert(0 <= x && x < 2 * n);
    if (x < n)
        grid[1][1 + x] = v;
    else
        grid[2][1 + x - n] = v;
}
void mmain() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] != 0) {
                int id = grid[i][j];
                if (i == 1) {
                    dest[id] = j - 1;
                } else if (i == 4) {
                    dest[id] = j - 1 + n;
                } else if (i == 2) {
                    pos[id] = initial[id] = j - 1;
                } else {
                    pos[id] = initial[id] = j - 1 + n;
                }
            }
        }
    }
    if (k == 2 * n) {
        bool ok = false;
        for (int i = 1; i <= k; ++i) {
            if (pos[i] == dest[i]) {
                ok = true;
                // PRINT IT!!
            }
        }
    }

    while (true) {
        int colour = 0, x = 0;
        for (x = 0; x < 2*n; ++x) {
            if (cell(x) != 0) {
                colour = cell(x);
                break;
            }
        }

        int startc = colour;
        for (int y = x + 1; y < 2*n; ++y) {
            if (cell(y) == 0) {
                display(colour, y);
                if (y == dest[colour]) {
                    displayfinish(colour);
                }
            }
        }
    }

    // at least one gap
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