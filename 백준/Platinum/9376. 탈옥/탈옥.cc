#include <iostream>
#include <utility>
#include <vector>
#include <queue>
	
using namespace std;

typedef pair<int, int> pos;

int N, H, W;

// (0, *), (H+1, *), (*, 0), (*, W+1) are outside of the prison
char map[102][102];

int dh[4] = {-1, 0, 1, 0};
int dw[4] = {0, 1, 0, -1};

int solve(vector<pos> prisoners);
vector<vector<int> > BFS(pos start);
void mergeMap(vector<vector<int> >& a, vector<vector<int> >& b);

void print_map(vector<vector<int> >& map) {
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[0].size(); ++j) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

struct Position {
	pos p;
	int cnt; // the number of opening doors
	
	Position(pos p, int cnt): p(p), cnt(cnt) {}
};

int main() {
	// freopen("input.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> H >> W;

		vector<pos> prisoners;
		for (int h = 0; h <= H+1; ++h) {
			for (int w = 0; w <= W+1; ++w) {
				if (h == 0 || h == H+1 || w == 0 || w == W+1) {
					map[h][w] = '.';
					continue;
				}

				cin >> map[h][w];
				if (map[h][w] == '$') {
					prisoners.push_back(make_pair(h, w));
				}
			}
		}

		cout << solve(prisoners) << endl;
	}
}

int solve(vector<pos> prisoners) {
	vector<vector<int> > cMap(H+2, vector<int>(W+2, 0));

	for (int i = 0; i < 3; ++i) {
		if (i == 2) {
			vector<vector<int> > m = BFS(make_pair(0, 0));
			mergeMap(cMap, m);
		} else {
			vector<vector<int> > m = BFS(prisoners[i]);
			mergeMap(cMap, m);
		}
	}

	int minCnt = 10000;
	for (int h = 0; h < H+2; ++h) {
		for (int w = 0; w < W+2; ++w) {
			if (map[h][w] == '#') {
				cMap[h][w] -= 2;
			}
			if (cMap[h][w] < minCnt) {
				minCnt = cMap[h][w];
			}
		}
	}
	return minCnt;
}

vector<vector<int> > BFS(pos start) {
	vector<vector<int> > cMap(H+2, vector<int>(W+2, 10000));

	queue<Position> pq;
	pq.push(Position(start, 0));
	cMap[start.first][start.second] = 0;

	while (!pq.empty()) {
		Position pos = pq.front();
		pq.pop();

		for (int i = 0; i < 4; ++i) {
			int nh = pos.p.first + dh[i];
			int nw = pos.p.second + dw[i];

			if (nh < 0 || nh >= H+2 || nw < 0 || nw >= W+2) {
				continue;
			}

			if (map[nh][nw] == '*') {
				continue;
			}

			int cnt = cMap[pos.p.first][pos.p.second];
			if (map[nh][nw] == '#') {
				cnt += 1;
			}

			if (cnt < cMap[nh][nw]) {
				pq.push(Position(make_pair(nh, nw), cnt));
				cMap[nh][nw] = cnt;
			}
		}
	}
	return cMap;
}

void mergeMap(vector<vector<int> >& a, vector<vector<int> >& b) {
	for (int h = 0; h < H+2; ++h) {
		for (int w = 0; w < W+2; ++w) {
			a[h][w] += b[h][w];
		}
	}
}
