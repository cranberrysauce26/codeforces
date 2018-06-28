#include <bits/stdc++.h>
using namespace std;
const long long HI = 1e18;
int main() {
    freopen("data.txt", "w", stdout);
    int n = 1000;
    printf("%d\n", n);
    vector<long long> v(n), u(n);
    for (int i = 0; i < n; ++i) {
        v[i] = rand() % HI;
        u[i] = rand() % HI;
        long long l = min(u[i], v[i]);
        long long r = max(u[i], v[i]);
        cout << l << " " << r << "\n";
    }
}