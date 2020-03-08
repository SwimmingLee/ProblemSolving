#include <iostream>
#include <string>
using namespace std;

#define ALPHABETS	26
struct Trie {
	Trie* children[ALPHABETS];
	bool valid;
	Trie() : valid(false) {
		for (int i = 0; i < ALPHABETS; i++)
			children[i] = NULL;
	}
	~Trie() {
		for (int i = 0; i < ALPHABETS; i++)
			delete children[i];
	}
	void add(string& str, int index) {
		if (str.size() == index) {
			valid = true;
			return;
		}
		int c = str[index] % ALPHABETS;
		if (children[c] == NULL) {
			children[c] = new Trie();
		}
		children[c]->add(str, index + 1);
	}
	int search(string& str, int index) {
		if (str.size() == index) {
			return 1;
		}
		int c = str[index] % ALPHABETS;
		if (children[c] == NULL) {
			return 0;
		}
		return children[c]->search(str, index + 1);
	}
};

int main(void) {
	int n, m;
	int ans = 0;
	Trie* trie;
	trie = new Trie();
	cin >> n >> m;
	while (n--) {
		string s;
		cin >> s;
		trie->add(s, 0);
	}
	while (m--) {
		string s;
		cin >> s;
		ans += trie->search(s, 0);
	}
	cout << ans << '\n';
	return 0;
}