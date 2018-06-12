#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;

const int MAXN = 1e5 + 5;
int n, m;
vector<int> adj[MAXN], testadj[MAXN];

int visit[MAXN], par[MAXN], loopidx[MAXN];
vector<int> mainloop;
set<int> valid;

bool findloop(int u, vector<int> adj[]) {
    visit[u] = 1;
    for (int v : adj[u]) {
        if (!visit[v]) {
            par[v] = u;
            if (findloop(v, adj)) {
                return true;
            }
        } else if (visit[v] == 1) {
            // found a loop
            int w = u;
            while (true) {
                mainloop.push_back(w);
                if (w == v)
                    break;
                w = par[w];
            }
            reverse(mainloop.begin(), mainloop.end());
            for (int i = 0; i < (int)mainloop.size(); ++i) {
                loopidx[mainloop[i]] = i;
                valid.insert(i);
                // printf("mainloop[%d] = %d\n", i, mainloop[i]);
            }
            return true;
        }
    }
    visit[u] = 2;
    return false;
}

int lastidx[MAXN];

inline bool are_cyc_neighbours(int u, int v) {
    if (loopidx[u] == -1 || loopidx[v] == -1)
        return false;
    int diff = (loopidx[u] - loopidx[v] + sz(mainloop)) % sz(mainloop);
    return diff == sz(mainloop) - 1 || diff == 1;
}

void update_ans(int &ans, int ans2, int i) {
    if (ans2 != -1) {
        if (ans == -1) {
            ans = ans2;
        } else {
            int dist1 = (ans - i + sz(mainloop)) % sz(mainloop);
            int dist2 = (ans2 - i + sz(mainloop)) % sz(mainloop);
            if (dist2 > dist1) {
                ans = ans2;
            }
        }
    }
}

int dfs(int u, int i) {
    // printf("dfs(%d, %d)\n", u, i);
    visit[u] = 2;
    int &ans = lastidx[u];
    ans = -1;
    for (int v : adj[u]) {
        if (!are_cyc_neighbours(u, v)) {
            if (loopidx[v] != -1) {
                update_ans(ans, loopidx[v], i);
            }
            if (!visit[v]) {
                if (loopidx[v] == -1) {
                    int ans2 = dfs(v, i);
                    update_ans(ans, ans2, i);
                }
            } else if (visit[v] == 1) {
                int ans2 = lastidx[v];
                update_ans(ans, ans2, i);
            }
        }
    }
    visit[u] = 1;
    // printf("returning from dfs(%d, %d) = %d\n", u, i, ans);
    return ans;
}

void markloop(int i, int j) {
    // printf("marking loop %d, %d\n", i, j);
    // //printf("markloop %d, %d\n", i, j);
    if (i <= j) {
        auto it = valid.upper_bound(j);
        while (it != valid.end()) {
            it = valid.erase(it);
        }
        it = valid.begin();
        while (it != valid.end() && *it < i) {
            it = valid.erase(it);
        }
    } else {
        auto it = valid.upper_bound(j);
        while (it != valid.end() && *it < i) {
            it = valid.erase(it);
        }
    }
}

bool works(int x) {
    // printf("checking if %d works\n", x);
    for (int u = 1; u <= n; ++u) {
        if (u != x) {
            for (int v : adj[u]) {
                if (v != x) {
                    testadj[u].push_back(v);
                }
            }
        }
    }
    memset(visit, 0, sizeof visit);
    for (int u = 1; u <= n; ++u) {
        if (!visit[u]) {
            if (findloop(u, testadj)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
    }
    memset(loopidx, -1, sizeof loopidx);
    bool foundloop = false;
    for (int u = 1; u <= n; ++u) {
        if (!visit[u]) {
            if (findloop(u, adj)) {
                foundloop = true;
                break;
            }
        }
    }
    if (!foundloop) {
        printf("1\n");
        return 0;
    }

    memset(visit, 0, sizeof visit);
    memset(lastidx, -1, sizeof lastidx);
    for (int u : mainloop) {
        if (!visit[u]) {
            int ans = dfs(u, loopidx[u]);
            if (ans != -1) {
                markloop(ans, loopidx[u]);
            }
        }
    }

    if (valid.empty()) {
        // //printf("vlid is empty\n");
        printf("-1\n");
        return 0;
    }

    // for (int x : valid) {
    // 	//printf("%d is valid\n", mainloop[x]);
    // }

    int ans = mainloop[*valid.begin()];

    if (works(ans)) {
        printf("%d\n", ans);
    } else {
        printf("-1\n");
    }
}