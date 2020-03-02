#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> preprocessing(string& pattern) {
	vector<int> fail(pattern.length(), 0);
	int j = 0;
	for (int i = 1; i < pattern.length(); i++) {
		while (j > 0 && pattern[i] != pattern[j]) j = fail[j - 1];
		if (pattern[i] == pattern[j]) {
			fail[i] = j + 1;
			j += 1;
		}
		else {
			fail[i] = 0;
		}
	}
	return fail;
}
int GetMinStrLength(string& str, int board_sz) {
	vector<int> fail = preprocessing(str);
	return board_sz - fail[board_sz - 1];
}

int main(void) {
	int board_sz;
	string str;
	cin >> board_sz >> str;

	cout << GetMinStrLength(str, board_sz) << '\n';
	return 0;
}