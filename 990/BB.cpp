#include<bits/stdc++.h>
using namespace std;


#define MAX          (int)1e5+10
#define MIN          -(int)1e5+10
#define ll           long long
#define pii          pair<ll,ll>
#define sf(a)        scanf("%d",&a)
#define pf(a)        printf("%d",a)
#define spc          printf(" ")
#define nl           printf("\n");
#define mem(a,b)     memset(a,b,sizeof(a))
#define all(x)       x.begin(),x.end()
#define sortv(x)     sort(x.begin(),x.end())
#define sortvr(x)    sort()x.rbegin(),x.rend())
#define pb           push_back

int main()
{
	freopen("data.txt", "r", stdin);
    ll n,k;
    cin>>n>>k;

    ll N[n+10];

    for(int i=0;i<n;i++) cin>>N[i];

    sort(N,N+n,greater<int>());

    map<ll,bool>mp;
    int track=0;
    bool flag=0;
    for(int i=0;i<n;i++)
    {
        if(N[i]!=N[i+1])
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        cout<<n<<endl;
        return 0;
    }
    for(int i=1;i<n;i++)
    {
        ll key = N[i];

        for(int j=i-1;j>=0;j--)
        {
            if(mp[N[i]]==1) break;
            if(N[i]<N[j] and N[j]<=key+k)
            {
                //cout<<N[i]<<" "<<N[j]+k<<endl;
                mp[N[i]]=1;
                break;
            }
            else if(N[j]>key+k) break;
        }
    }
    ll c=0;
    for(int i=0;i<n;i++)
    {
        if(mp[N[i]]==1) continue;
        else c++;
    }

    cout<<c<<endl;



}