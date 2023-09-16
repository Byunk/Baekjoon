#include <iostream>
#include <algorithm>

using namespace std;

int weights[101];
int values[101];
int DP[101][100001];

int N, K;

int solve();

int main() {
	// freopen("input.txt", "r", stdin);

	cin >> N >> K;
	
	for (int i = 1; i <= N; ++i) {
		cin >> weights[i] >> values[i];
	}

	int ret = solve();
	cout << ret << endl;
}

int solve() {
	// knapsack algorithm
	// DP[i][j] = max(DP[i-1][j], DP[i-1][j-W[i]] + V[i])
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= K; ++j) {
			if (j-weights[i] >= 0) {
				DP[i][j] = max(DP[i-1][j], DP[i-1][j-weights[i]] + values[i]);
			} else {
				DP[i][j] = DP[i-1][j];
			}
		}
	}
	return DP[N][K];
}
