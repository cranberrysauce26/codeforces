#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    freopen("data.txt", "r", stdin);
	ll n,m,a,b;
	cin>>n>>m>>a>>b;
	if(n%m==0){
		printf("0\n");
		return 0;
	}
	if(n==m){
		cout<<"0\n";
	}
	if(n>m){
		ll f=m;
		while(f<n){
			f+=f;
		}
		f=(f-n)*a;
		ll t=(n-m)*b;
		// printf("%I64d\n",min(t,f));
        cout << min(t,f) << "\n";
	}
	if(n<m){
		ll f=(m-n)*a;
		ll t=n*b;
		// printf("%I64d\n",min(f,t));
        cout << min(t,f) << "\n";
	}
}