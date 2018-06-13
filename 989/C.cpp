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

char ret[50][50];

void solve1(vector<pair<int, char>> vals, int left) {
    assert(vals[0].first == 1);
    for (int col = left; col < 50; ++col) {
        for (int row = 0; row < 50; ++row) {
            ret[row][col] = vals[0].second;
        }
    }
    int row = 1, col = left + 1;
    for (int i = 1; i < 4; ++i) {
        while (vals[i].first--) {
            ret[row][col] = vals[i].second;
            row += 2;
            if (row == 49) {
                row = 1;
                col += 2;
            }
        }
    }
}

void reducea(int a, int b, int c, int d) {
    assert(a > 1 && b > 1 && c > 1 && d > 1);
    int row = 0, col = 0;
    int cnt = 0;
    while (a != 1 && b != 1 && c != 1 && d != 1) {
        if (cnt % 2 == 0) {
            ret[row][col] = 'A';
            --a;
        } else {
            ret[row][col] = 'B';
            --b;
        }
        ++row;
        if (row == 50) {
            ++col, ++cnt;
            row = 0;
        }
        ++cnt;
    }

    --c;
    while (row != 0) {
        ret[row][col] = 'C';
        ++row;
        if (row == 50) {
            ++col;
            row = 0;
        }
    }
    while (row < 50) {
        ret[row][col] = 'C';
        ++row;
    }
    vector<pair<int, char>> vals(4);
    if (a == 1) {
        vals[0] = {a, 'A'};
        vals[1] = {b, 'B'};
    } else {
        assert(b == 1);
        vals[0] = {b, 'B'};
        vals[1] = {a, 'A'};
    }
    vals[2] = {c, 'C'};
    vals[3] = {d, 'D'};
    solve1(vals, col + 1);
}
int visit[50][50];
void dfs(int r, int c, char colour) {
    if (visit[r][c] || ret[r][c] != colour)
        return;
    visit[r][c] = 1;
    if (r - 1 >= 0) {
        dfs(r - 1, c, colour);
    }
    if (r + 1 < 50) {
        dfs(r + 1, c, colour);
    }
    if (c - 1 >= 0) {
        dfs(r, c - 1, colour);
    }
    if (c + 1 < 50) {
        dfs(r, c + 1, colour);
    }
}
bool works(int a, int b, int c, int d) {
    int na = 0, nb = 0, nc = 0, nd = 0;
    for (int r = 0; r < 50; ++r) {
        for (int c = 0; c < 50; ++c) {
            if (!visit[r][c]) {
                if (ret[r][c] == 'A') {
                    dfs(r, c, 'A');
                    ++na;
                } else if (ret[r][c] == 'B') {
                    dfs(r, c, 'B');
                    ++nb;
                } else if (ret[r][c] == 'C') {
                    dfs(r, c, 'C');
                    ++nc;
                } else {
                    dfs(r, c, 'D');
                    ++nd;
                }
            }
        }
    }
    DEBUG("na = %d, nb = %d, nc = %d, nd = %d\n", na, nb, nc, nd);
    return na == a && nb == b && nc == c && nd == d;
}

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    if (a == 1 || b == 1 || c == 1 || d == 1) {
        vector<pair<int, char>> vals;
        vals.push_back({a, 'A'});
        vals.push_back({b, 'B'});
        vals.push_back({c, 'C'});
        vals.push_back({d, 'D'});
        sort(allof(vals));
        solve1(vals, 0);
    } else {
        reducea(a, b, c, d);
    }
#ifdef LOCAL
    if (!works(a, b, c, d)) {
        DEBUG("NOOO!! IT DOESNT WORK\n");
        // return 0;
    }
#endif
    printf("50 50\n");
    for (int row = 0; row < 50; ++row) {
        for (int col = 0; col < 50; ++col) {
            printf("%c", ret[row][col]);
        }
        printf("\n");
    }
}