#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;
int N;
ll heights[100000];

ll largest(int start, int end) {
	if (start == end) return heights[start];

	int mid = (start+end)/2;
	ll A1 = max(largest(start, mid), largest(mid+1, end));
	
	int l = mid, r = mid;
	ll minH = heights[l];
	ll area = (r-l+1) * minH;
	while (l > start || r < end) {
		if (l == start) {
			minH = min(minH, heights[++r]);
		} else if (r == end) {
			minH = min(minH, heights[--l]);
		} else if (heights[l-1] >= heights[r+1]) {
			minH = min(minH, heights[--l]);
		} else {
			minH = min(minH, heights[++r]);
		}
		area = max(area, (r-l+1) * minH);
	}

	return max(A1, area);
}

void solve () {
	while (true) {
		cin >> N;
		if (N == 0) break;
		for (int i = 0; i < N; ++i) {
			cin >> heights[i];
		}
		cout << largest(0, N-1) << endl;
	}
}

int main () {
	// freopen("input.txt", "r", stdin);
	solve();
}
