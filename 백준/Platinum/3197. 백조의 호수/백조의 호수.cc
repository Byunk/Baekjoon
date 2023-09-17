#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int R, C;
char map[1500][1500];
int visited[1500][1500]; // 0: not visited, 1: visited by water, 2: visited by swan

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

vector<pair<int, int> > swans;
vector<pair<int, int> > ices;
queue<pair<int, int> > q; // queue for swans

int solve();
bool bfs_swan(pair<int, int> target);
void flood();

int main() {
	// freopen("input.txt", "r", stdin);

	cin >> R >> C;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			cin >> map[i][j];
			if (map[i][j] == 'L') {
				swans.push_back(make_pair(i, j));
			}
		}
	}

	cout << solve() << endl;
}

int solve() {
	int cnt = 0;
	pair<int, int> swan1 = swans[0];
	pair<int, int> swan2 = swans[1];
	
	q.push(swan1);

	// initialize ices
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (map[i][j] == '.' || map[i][j] == 'L') {
				for (int k = 0; k < 4; ++k) {
					int nx = i + dx[k];
					int ny = j + dy[k];

					if (nx < 0 || nx >= R || ny < 0 || ny >= C || visited[nx][ny] >= 1) {
						continue;
					}
					if (map[nx][ny] == 'X') {
						ices.push_back(make_pair(nx, ny));
						++visited[nx][ny];
					}
				}
			}
		}
	}

	while (bfs_swan(swan2) == false) {
		flood();
		++cnt;
	}
	return cnt;
}

bool bfs_swan(pair<int, int> target) {
	queue<pair<int, int> > buffer;

	while (!q.empty()) {
		pair<int, int> node = q.front();
		q.pop();
		
		for (int i = 0; i < 4; ++i) {
			int nx = node.first + dx[i];
			int ny = node.second + dy[i];

			if (nx < 0 || nx >= R || ny < 0 || ny >= C || visited[nx][ny] == 2) {
				continue;
			}

			if (map[nx][ny] == 'X') {
				++visited[nx][ny];
				buffer.push(make_pair(nx, ny));
				continue;
			}

			if (nx == target.first && ny == target.second) {
				return true;
			}

			if (map[nx][ny] == '.') {
				q.push(make_pair(nx, ny));
				++visited[nx][ny];
			}
		}
	}

	q = buffer;
	return false;
}

void flood() {
	vector<pair<int, int> > buffer;

	for (auto ice : ices) {
		for (int i = 0; i < 4; ++i) {
			int nx = ice.first + dx[i];
			int ny = ice.second + dy[i];

			if (nx < 0 || nx >= R || ny < 0 || ny >= C || visited[nx][ny] >= 1) {
				continue;
			}

			if (map[nx][ny] == 'X') {
				buffer.push_back(make_pair(nx, ny));
				++visited[nx][ny];
			}
		}
	}

	for (auto ice: ices) {
		map[ice.first][ice.second] = '.';
	}
	
	ices = buffer;
}