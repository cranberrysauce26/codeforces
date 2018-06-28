#include<bits/stdc++.h>
using namespace std;
int main()
{
    freopen("data.txt", "r", stdin);
    int n;
    cin>>n;
    vector<string>v,v1;
    for(int i=1;i<=n;i++)
    {	string st;
    	cin>>st;
    	v.push_back(st);
	}
	vector<string>::iterator it;
	for(int i=1;i<=n;i++)
	{	string st;
		cin>>st;
		it=find(v.begin(),v.end(),st);
		if(it==v.end())
			v1.push_back(st);
		else 
			v.erase(it);	
	}
	cout<<v1.size();
	return 0;
}