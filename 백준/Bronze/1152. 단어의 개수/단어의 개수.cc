#include <iostream>
#include <string>

using namespace std;

int main() {
	// freopen("input.txt", "r", stdin);

	string s;
	int cnt = 0;
	while (cin >> s) {
		++cnt;
	}

	cout << cnt << endl;
}