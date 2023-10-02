#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<vector<ll> > matrix;

int N;
ll B;

matrix solve (matrix& m, ll b);

// define * operator
matrix operator * (const matrix& a, const matrix& b) {
	matrix ret(N, vector<ll>(N));

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				ret[i][j] += a[i][k] * b[k][j];
			}
			ret[i][j] %= 1000;
		}
	}
	return ret;
}

int main () {
	// freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> B;

	matrix m(N, vector<ll>(N));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> m[i][j];
		}
	}

	matrix ret = solve(m, B);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << ret[i][j] % 1000 << " ";
		}
		cout << endl;
	}
}

matrix solve (matrix& m, ll b) {
	if (b == 1) {
		return m;
	}

	matrix ret;
	if (b % 2 == 0) {
		matrix mm = m*m;
		ret = solve(mm, b / 2);
	} else {
		matrix mm = m*m;
		ret = solve(mm, b / 2) * m;
	}
	return ret;	
}
