#include <iostream>
using namespace std;
long long a[100005];
int main() {
    freopen("data.txt", "r", stdin);
    int n; cin >> n;
    long long sum[100010];
    int j = 0;
    long long min = 1e12;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        min = a[i] < min ? a[i] : min;
    }
    min /= n;
    for (int i = 1; i <= n; ++i) {
        a[i] -= min * n;
    }
    while (1) {
        for (int i = 1; i <= n; ++i) {
            if (a[i]-i < 0) {
                printf("%d", i);
                return 0;
            } else {
                a[i] -= n;
            }
        }
    }
}