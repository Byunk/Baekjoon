#include <iostream>
#include <set>
#include <string>
#include<memory.h>

using namespace std;

int N, B;
char map[4][4];
bool visited[4][4];
set<string> res;
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int score[9] = {0, 0, 0, 1, 1, 2, 3, 5, 11};

struct Trie {
  Trie* children[26];
  bool isLast;

  Trie() {
    memset(children, 0, sizeof(children));
    this->isLast = false;
  }

  ~Trie() {
    for (int i = 0; i < 26; i++) {
      if (children[i]) delete this->children[i];
    }
  }

  void insert(const char* key) {
    if (*key == '\0') {
      isLast = true;
    } else {
      int idx = *key - 'A';
      if (children[idx] == NULL) {
        children[idx] = new Trie();
      }
      children[idx]->insert(key + 1);
    }
  }

  void dfs(int x, int y, string key) {
    if (key.size() > 8) {
      return;
    }

    visited[x][y] = true;
    key += map[x][y];

    Trie* child = this->children[map[x][y] - 'A'];
    if (child == NULL) {
      visited[x][y] = false;
      return;
    }
    if (child->isLast) {
      res.insert(key);
    }

    for (int i = 0; i < 8; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4 || visited[nx][ny]) {
        continue;
      }
      child->dfs(nx, ny, key);
    }
    visited[x][y] = false;
  }
};

int main() {
  //freopen("input.txt", "r", stdin);
  cin >> N;

  Trie* root = new Trie();
  for (int i = 0; i < N; i++) {
    char s[10];
    cin >> s;
    root->insert(s);
  }

  cin >> B;
  for (int i = 0; i < B; i++) {
    res.clear();
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        cin >> map[j][k];
      }
    }

    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        root->dfs(j, k, "");
      }
    }

    string longest = "";
    int total = 0;
    int max = 0;
    for (string item: res) {
      if (item.size() == max) {
        longest = longest < item ? longest : item;
      } else if (item.size() > max) {
        longest = item;
        max = longest.size();
      }
      total += score[item.size()];
    }
    cout << total << " " << longest << " " << res.size() << "\n";
  }
  delete root;
  return 0;
}
