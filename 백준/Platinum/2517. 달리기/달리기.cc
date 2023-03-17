#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define MAX 10000000

using namespace std;

void solve();
bool compare(pair<int, int> a, pair<int, int> b);

int N;
vector<pair<int, int> > v;
vector<int> ans;

int indexedTree[MAX];

int main() {
    //freopen("input.txt", "r", stdin);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int n;
        cin >> n;
        v.push_back(make_pair(i, n));
        ans.push_back(0);
    }

    solve();

    for (int i = 0; i < N; i++) {
        cout << ans[i] << "\n";
    }
}

void solve() {
    // 실력 순으로 정렬 (내림차순)
    sort(v.begin(), v.end(), compare);

    // 트리의 Depth
    int K = 1;
    while (pow(2, K) < N) {
        K++;
    }

    // 실력 순서대로 indexed tree에 삽입하면서 부분합 계산
    for (int i = 0; i < N; i++) {
        long long idx = pow(2, K) + v[i].first;

        // 삽입 & 갱신
        indexedTree[idx] = 1;
        for (long long j = idx / 2; j > 0; j = j/2) {
            indexedTree[j] = indexedTree[2*j] + indexedTree[2*j+1];
        }

        // 합계산 (순위)
        long long start = pow(2, K) + 0;
        long long end = pow(2, K) + v[i].first;
        long long sum = 0;
        while (start <= end) {
            if (start%2 == 1) {
                sum += indexedTree[start];
            }
            if (end%2 == 0) {
                sum += indexedTree[end];
            }
            start = (start + 1) / 2;
            end = (end - 1) / 2;
        }
        ans[v[i].first] = sum;
    }

}

bool compare(pair<int, int> a, pair<int, int> b) {
    if (a.second > b.second) {
        return true;
    } else {
        return false;
    }
}
