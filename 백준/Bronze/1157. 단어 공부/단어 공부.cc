#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

int main() {
	// freopen("input.txt", "r", stdin);

	string s;
	cin >> s;

	map<char, int> dict;

	for (auto c : s) {
		c = toupper(c);
		if (dict.find(c) == dict.end()) {
			dict[c] = 1;
		} else {
			++dict[c];
		}
	}

	char mx = dict.begin()->first;
	int mc = dict.begin()->second;
	int cnt = 1;
	for (auto i = ++dict.begin(); i != dict.end(); ++i) {
		if (i->second > mc) {
			mx = i->first;
			mc = i->second;
			cnt = 1;
		} else if (i->second == mc) {
			++cnt;
		}
	}

	if (cnt > 1) {
		cout << '?' << endl;
	} else {
		cout << mx << endl;
	}
}