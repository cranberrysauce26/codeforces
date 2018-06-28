#include <bits/stdc++.h>
using namespace std;
const int MAX_VAL = 1e7-5;
int main() {
    freopen("data.txt", "w", stdout);
    int n = 1e5;
    printf("%d\n", n);
    for (int i = 0; i < n - 1; ++i) {
        printf("%d %d\n", i + 1, i + 2);
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", (rand() % MAX_VAL)+1);
    }
    int q = 1e5;
    printf("%d\n", q);
    for (int i = 0; i < q; ++i) {
        printf("%d %d %d\n", 1+(rand()%n), 1+(rand()%n), (rand() % MAX_VAL)+1);
    }
}