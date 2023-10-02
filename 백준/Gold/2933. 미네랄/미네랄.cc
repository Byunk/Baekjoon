#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>
	
using namespace std;

typedef pair<int, int> pos;

char cage[101][101];
bool visit[101][101];
int R, C, N;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

void solve(vector<int>& heights);
pos throw_stick(int height, bool isLeft);
vector<pos> find_cluster(pos mineral);
bool isFly(vector<pos>& cluster, pos node);
void falldown(vector<pos>& cluster);

bool compare(const pos& a, const pos& b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	return a.first < b.first;
}

void print_cage() {
	for (int i = R; i >= 1; --i) {
		for (int j = 1; j <= C; ++j) {
			cout << cage[i][j];
		}
		cout << endl;
	}	
}

void print_pos_vector(vector<pos>& v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i].first << " " << v[i].second << endl;
	}
}

int main() {
	// freopen("input.txt", "r", stdin);

	cin >> R >> C;
	for (int i = R; i >= 1; --i) {
		for (int j = 1; j <= C; ++j) {
			cin >> cage[i][j];
		}
	}
	cin >> N;
	vector<int> heights(N);
	for (int i = 0; i < N; ++i) {
		cin >> heights[i];
	}

	solve(heights);
	print_cage();
}

void solve(vector<int>& heights) {
	bool isLeft = true;
	for (int i = 0; i < N; ++i) {
		pos mineral = throw_stick(heights[i], isLeft);
		isLeft = !isLeft;
		if (mineral.second == -1) {
			continue;
		}

		vector<pos> cluster = find_cluster(mineral);
		falldown(cluster);
	}
}

// destroy mineral and return its position
pos throw_stick(int height, bool isLeft) {
	// find first mineral's position
	int mr = height, mc = -1;
	for (int i = 1; i <= C; ++i) {
		int x = isLeft ? i : C-i+1;
		if (cage[mr][x] == 'x') {
			mc = x;

			// destroy mineral
			cage[mr][mc] = '.';

			return make_pair(mr, mc);
		}
	}
	return make_pair(mr, mc);
}

vector<pos> find_cluster(pos mineral) {
	vector<pos> cluster;

	for (int i = 0; i < 4; ++i) {
		// initialize visit array
		for (int j = 1; j <= R; ++j) {
			for (int k = 1; k <= C; ++k) {
				visit[j][k] = false;
			}
		}
		visit[mineral.first][mineral.second] = true;

		int nx = mineral.first + dx[i];
		int ny = mineral.second + dy[i];

		if (nx < 1 || nx > R || ny < 1 || ny > C || visit[nx][ny]) {
			continue;
		}
		
		if (cage[nx][ny] == 'x') {
			vector<pos> v;
			if (isFly(v, make_pair(nx, ny))) {
				cluster = v;
				break;
			}
		}
	}
	return cluster;
}

bool isFly(vector<pos>& cluster, pos node) {
	// if cluster's node is attached to ground, then return false
	if (node.first == 1) {
		return false;
	}
	visit[node.first][node.second] = true;
	cluster.push_back(make_pair(node.first, node.second));

	for (int i = 0; i < 4; ++i) {
		int nx = node.first + dx[i];
		int ny = node.second + dy[i];

		if (nx < 1 || nx > R || ny < 1 || ny > C || visit[nx][ny]) {
			continue;
		}

		if (cage[nx][ny] == 'x') {
			if (!isFly(cluster, make_pair(nx, ny))) {
				return false;
			}
		}
	}

	return true;
}

void falldown(vector<pos>& cluster) {
	sort(cluster.begin(), cluster.end(), compare);

	vector<int> minDist(101, 1000);
	for (auto mineral : cluster) {
		// given minearl is not the lowest one
		if (minDist[mineral.second] != 1000) {
			continue;
		}
		int md = 0;
		int r = mineral.first - 1;
		while (r >= 1) {
			if (cage[r][mineral.second] == 'x') {
				break;
			}
			++md;
			--r;
		}

		minDist[mineral.second] = md;
	}

	int minD = *min_element(minDist.begin(), minDist.end());
	// falldown
	for (auto mineral: cluster) {
		swap(cage[mineral.first][mineral.second], cage[mineral.first-minD][mineral.second]);
	}
}
