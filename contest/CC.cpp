#include <bits/stdc++.h>
using namespace std;

#define pb  push_back
#define mp  make_pair
#define int long long
#define itr ::iterator 

typedef pair<int,int>  pii;

const int MAX=5e5;

vector<pii> vec;

int N,X,Y,cnt,res[MAX];

signed main()
{
    freopen("data.txt", "r", stdin);
	ios_base::sync_with_stdio(false);


	cin>>N;
	for(int A=1;A<=N;A++)
	{
		cin>>X>>Y;
		if(X>Y)
			swap(X,Y);
		vec.pb(mp(X,0));
		vec.pb(mp(Y,1));
	}
	sort(vec.begin(),vec.end());
	for(int A=0;A<vec.size();A++)
	{
		if(vec[A].second==0)
			cnt++;
		else
		{
			cnt--;
			if(A==vec.size()-1)
				continue;
			if(vec[A+1].first>vec[A].first and vec[A+1].second==1)
			{	
				res[cnt]+=vec[A+1].first-vec[A].first;
			}
			else if(vec[A+1].first-vec[A].first-1>=1 and vec[A+1].second==0)
			{
				res[cnt]+=vec[A+1].first-vec[A].first-1;
			}
			continue;
		}
		if(A<vec.size()-1 and vec[A].first==vec[A+1].first and vec[A+1].second==0)
			continue;
		res[cnt]++;
		if(vec[A+1].first-vec[A].first-1>=1 and vec[A+1].second==0)
		{
			res[cnt]+=vec[A+1].first-vec[A].first-1;
		}
		else if(vec[A+1].first>vec[A].first and vec[A+1].second==1)
			res[cnt]+=vec[A+1].first-vec[A].first;
	}
	for(int A=1;A<=N;A++)
		cout<<res[A]<<" ";
	return 0;
}