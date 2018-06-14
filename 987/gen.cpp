#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("data.txt", "w", stdout);
    int n = 100000, m = 100000, k = 100, s = 75;
    printf("%d %d %d %d\n", n, m, k, s);
    for (int i = 0; i < m; ++i) {
        int u = rand()%n + 1, v = rand()%n+1;
        printf("%d %d\n", u, v);
    }
}