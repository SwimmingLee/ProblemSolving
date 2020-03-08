#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
//28ms
bool binary_search(vector<string>& words, string& word) {
	int start, end, mid;
	start = 0;
	end = words.size() - 1;

	while (start <= end) {
		mid = (start + end) / 2;
		int cmp = words[mid].compare(word);

		if (cmp < 0) {
			start = mid + 1;
		}
		else if (cmp > 0) {
			end = mid - 1;
		}
		else {
			return true;
		}
	}
	return false;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	string word;
	vector<string> words, llwords;
	cin >> n >> m;
	words.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> words[i];
	}
	sort(words.begin(), words.end());
	for (int j = 0; j < m; j++) {
		cin >> word;
		if (binary_search(words, word)) {
			llwords.push_back(word);
		}
	}
	sort(llwords.begin(), llwords.end());
	cout << llwords.size() << '\n';
	string ans;
	for (int i = 0; i < llwords.size(); i++) {
		ans += llwords[i] + '\n';
	}
	cout << ans;
	return 0;
}