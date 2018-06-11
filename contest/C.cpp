/*input

*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;
const int MAXN = 3e5+5;
int n;
string expr[MAXN];

int leftv[MAXN], rightv[MAXN];

int compute_left(const string& str) {
	stack<char> s;
	for (int i = 0; i < sz(str); ++i) {
		if (str[i]=='(') {
			s.push(str[i]);
		} else {
			if (s.empty()) {
				return -1;
			} else {
				if (s.top() == '(') {
					s.pop();
				} else {
					return -1;
				}
			}
		}
	}
	return sz(s);
}

inline char other(char c) {
	if (c=='(') return ')';
	else return '(';
}

int compute_right(const string& str) {
	string str2 = "";
	for (int i = 0; i < sz(str); ++i) {
		str2 += other(str[sz(str)-i-1]);
	}
	return compute_left(str2);
}

map<int,ll> open, close;

int main() {
	freopen("data.txt", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> expr[i];
		leftv[i] = compute_left(expr[i]);
		rightv[i] = compute_right(expr[i]);
		printf("i = %d, left = %d, right = %d\n", i, leftv[i], rightv[i]);
		if (leftv[i]!=-1) {
			open[leftv[i]]++;
		}
		if (rightv[i]!=-1) {
			close[rightv[i]]++;
		}
	}
	ll cnt = 0;
	for (auto p : open) {
		if (close.find(p.first)!=close.end()) {
			auto it = close.find(p.first);
			cnt += p.second * (it->second);
		}
	}
	cout << cnt << "\n";
	return 0;
}
