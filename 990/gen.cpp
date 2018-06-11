#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(NULL));
    freopen("data.txt", "w", stdout);
    int n = (int)1e6;
    int m = n;
    int k = n;
    printf("%d %d %d\n", n, m, k);
    for (int i = 1; i <= m; ++i) {
        int obs = (rand()%n)+1;
        printf("%d ", obs);
    }
    printf("\n");
    for (int i = 1; i <= k; ++i) {
        int cost = (rand()%10000)+5;
        printf("%d ", cost);
    }
    printf("\n");
}