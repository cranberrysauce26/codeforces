#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e4;
int main() {
    freopen("data.txt", "w", stdout);
    int n = 200;
    printf("%d\n", n);
    set<pair<int, int>> s;
    while (s.size() < n) {
        s.insert(make_pair(rand() % MAX - MAX / 2, rand() % MAX - MAX / 2));
    }
    for (auto p : s) {
        printf("%d %d\n", p.first, p.second);
    }
    int q = 200;
    printf("%d\n", q);
    for (int i = 0; i < q; ++i) {
        int u = 1+rand()%n;
        int m = 1+rand()%MAX;
        printf("%d %d\n", u, m);
    }
}