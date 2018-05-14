/*input
6
4 7 7 12 31 61
*/
#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long ll;
const int LOG = 62;
int n;
vector<pair<ll,int>> b;
ll x = 0;

queue<int> wait[LOG];

queue<ll> order;

void add(int idx) {
	x ^= b[idx].first;
	order.push(b[idx].first);
	for (int k = 0; k < b[idx].second; ++k) {
		if (!wait[k].empty() && (x&(1LL<<k))==0) {
			add(wait[k].front());
			wait[k].pop();
		}
	}
}

bool works(queue<int> q) {
	ll val = 0;
	for (;!q.empty(); q.pop()) {
		ll newval = val^q.front();
		if (newval <= val) return false;
		val = newval;
	}
	return true;
}

int main() {
	cin >> n;
	b.resize(n, {0,0});
	for (int i = 0; i < n; ++i) {
		cin >> b[i].first;
		while ( (1LL<< (b[i].second+1)) <= b[i].first) ++b[i].second;
	}
	sort(all(b));
	for (int i = 0; i < n; ++i) {
		if ((x&(1LL << b[i].second))==0) add(i);
		else wait[b[i].second].push(i);
	}
	for (int i = 0; i < LOG; ++i) {
		if (!wait[i].empty()) {
			cout << "No\n";
			return 0;
		}
	}
	if (works(order)) {
		// printf("WORKS\n");
	} else {
		printf("NOT WOrKS\n");
	}
	cout << "Yes\n";
	for (;!order.empty(); order.pop()) cout << order.front() << " ";
	cout << "\n";
}