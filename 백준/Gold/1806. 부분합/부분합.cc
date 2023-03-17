#include <iostream>
#include <vector>

using namespace std;

void solve();

int N, S;
vector<int> v;
int ans = 100001;

int main () {
    //freopen("input.txt", "r", stdin);

    cin >> N >> S;
    for (int i = 0; i < N; i++) {
        int n;
        cin >> n;
        v.push_back(n);
    }

    solve();

    if (ans == 100001) {
        cout << 0 << "\n";
    } else {
        cout << ans << "\n";
    }
}

void solve() {
    // Sliding Window
    int start, end, sum;
    start = end = 0;
    sum = v[0];

    while (true) {
        if (start == N) {
            break;
        } else if (end == N && sum < S) {
            break;
        }
        
        if (sum >= S) {
            if (end == start) {
                ans = 1;
                return;
            }

            if (end - start + 1 < ans) {
                ans = end - start + 1;
            }
            sum -= v[start];
            start++;
        } else if (sum < S) {
            end++;
            sum += v[end];
        }
    }
}