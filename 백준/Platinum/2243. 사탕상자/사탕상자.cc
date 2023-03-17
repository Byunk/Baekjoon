#include <iostream>
#define MAX 1000000

using namespace std;

int n;
int tree[4 * MAX];

int find(int node, int start, int end, int idx) {
  // find the taste
  if (start == end) {
    return start;
  }

  int mid = (start + end) / 2;
  if (tree[node * 2] < idx) {
    return find(node * 2 + 1, mid + 1, end, idx - tree[node * 2]);
  }
  return find(node * 2, start, mid, idx);
}

void update(int node, int start, int end, int taste, int cnt) {
  // idx out of range
  if (taste < start || end < taste) {
    return;
  }

  tree[node] += cnt;

  if (start == end) {
    return;
  }

  int mid = (start + end) / 2;
  update(node * 2, start, mid, taste, cnt);
  update(node * 2 + 1, mid + 1, end, taste, cnt);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  //freopen("input.txt", "r", stdin);
  cin >> n;
  for (int i = 0; i < n; i++) {
    int a, b, c;
    cin >> a;
    if (a == 1) {
      int taste;
      cin >> b;
      taste = find(1, 1, MAX, b);
      update(1, 1, MAX, taste, -1);
      cout << taste << "\n";
    } else if (a == 2) {
      cin >> b >> c;
      update(1, 1, MAX, b, c);
    }
  }
  return 0;
}
