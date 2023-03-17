#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void solve();

int N, K;
long long ans;
vector<pair<int, int>> jewelleries;
vector<int> bags;
priority_queue<int> max_heap;

int main() {
  //freopen("input.txt", "r", stdin);

  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    int m, v;
    cin >> m >> v;
    jewelleries.push_back(make_pair(m, v));
  }

  for (int i = 0; i < K; i++) {
    int c;
    cin >> c;
    bags.push_back(c);
  }

  solve();

  cout << ans << "\n";

  return 0;
}

bool compare(pair<int, int> a, pair<int, int> b) {
  if (a.first < b.first) return true;
  return false;
}

void solve() {
  // sort the jewelleries and bags
  sort(jewelleries.begin(), jewelleries.end(), compare);
  sort(bags.begin(), bags.end());

  // put all available jewelleries into the max heap
  int jpt = 0;
  for (int i = 0; i < K; i++) {
    while (jpt < N && jewelleries[jpt].first <= bags[i]) {
      max_heap.push(jewelleries[jpt++].second);
    }

    if (!max_heap.empty()) {
      ans += max_heap.top();
      max_heap.pop();
    }
  }
}
