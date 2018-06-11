/*input
4 5
10101
01000
00111
10000
*/
#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) begin(v), end(v)
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll, ll> pll;

// using namespace std;
typedef std::vector<int> vec;
typedef std::vector<vec> mat;

void display_vec(const vec& v) {
	for (int x : v) printf("%d ", x);
	printf("\n");
}

void display_mat(const mat& m) {
	for (auto& v : m) display_vec(v);
}

void rref(mat& A) {
	display_mat(A);
		printf("\n");
	// R is number of rows, C is number of columns.
	// printf("rref with A:\n");
	// display_mat(A);
	// printf("\n");
	int R = sz(A), C = sz(A[0]);
	// printf("R = %d, C = %d\n", R, C);
	for (int c = 0, r = 0; c < C; ++c) {
		int p = r;
		// printf("c = %d\n", c);
		while (p < R && !A[p][c]) ++p;
		// printf("p = %d\n", p);
		if (p < R) {
			swap(A[r], A[p]);
			for (int q = 0; q < R; ++q) {
				if (q != r && A[q][c]) {
					for (int d = c; d < C; ++d) {
						A[q][d]^=A[r][d];
					}
				}
			}
			++r;
		}
		printf("c = %d\n", c);
		display_mat(A);
		printf("\n");
	}
	// printf("finished rref\n");
}

bool solve(vec& v, mat& A) {
	rref(A);
	int n = sz(A[0])-1, m = sz(A);
	vec d;
	for (int i = 0, j = 0; i < m; ++i) {
		while (j <= n && !A[i][j]) ++j;
		if (j < n) d.push_back(j);
		else if (j == n) return false;
		else break;
	}
	// there is at least one solution
	v.resize(n, 0);
	for (int i = 0; i < sz(d); ++i) v[d[i]] = A[i][n];
	return true;
}

char buff[10];
int n, m; mat A; vec ans;

int readint(int &i) {
	int ans = 0;
	while ('0' <= buff[i] && buff[i] <= '9') ans = 10 * ans + (buff[i++]-'0');
	return ans;
}

int tmp[2005][2005];

int main() {
	cin >> n >> m;
	A.resize(m, vec(n+1));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char c;
			scanf(" %c", &c);
			// tmp[i][j] = c-'0';
			A[j][i] = c-'0';
			// scanf("%d", &A[i][j]);
		}
	}
	for (int r = 0; r < n; ++r) {
		A[r][n] = 1;
	}
	vec sol;
	solve(sol, A);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m+1; ++j) {
			// scanf("%d", &A[i][j]);
			cout << A[i][j] << " ";
		}
		cout << endl;
		// A[i][m] = 1;
	}
	// freopen("data.txt", "r", stdin);
}
