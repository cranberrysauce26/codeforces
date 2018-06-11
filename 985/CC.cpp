/*input
1 5 0
1 1 1 1 1


4 2 3
2 2 8 4 6 7 4 4
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll arr[100005];

int main(){
  int n, k, l;
  scanf("%d%d%d", &n, &k, &l);
  for (int i = 0; i<n*k; i++)
    scanf("%lld", &arr[i]);
  sort(arr, arr+n*k);
  int maxIndex = upper_bound(arr, arr+n*k, arr[0]+l)-arr-1;
  if (maxIndex < n-1){
    printf("0");
    return 0;
  }
  int needed = n - maxIndex/k - 1;
  printf("needed = %d\n", needed);
  ll sum = 0;
  for (int i = 0; i<= maxIndex; i+=k)
    sum += arr[i];
  cout << "sum is " << sum << " maxidx = " << maxIndex << "\n";
  while (needed && maxIndex){
    cout << "needed is " << needed << " and maxidx = " << maxIndex << "\n";
    if (maxIndex%k != 0){
      sum += arr[maxIndex];
      needed--;
    }
    maxIndex--;
  }
  printf("%lld", sum);
}