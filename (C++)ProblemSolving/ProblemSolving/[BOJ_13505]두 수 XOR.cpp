#include <iostream>
using namespace std;

#define NUMBERS		2

struct Trie {
	Trie* children[NUMBERS];
	bool valid;
	Trie(): valid(false) {
		for (int i = 0; i < NUMBERS; i++)
			children[i] = NULL;
	}
	void add(int num, int index) {
		if (index == 0) {
			valid = true;
			return;
		}
		int c = (num & (1 << (index - 1))) ? 1 : 0;
		if (children[c] == NULL) {
			children[c] = new Trie();
		}
		children[c]->add(num, index-1);

	}
	void add(int num) {
		add(num, 31);
	}
	int excrusive_search(int num, int index) {
		int res;
		if (index == 0) {
			return 0;
		}
		int c = (num & (1 << (index - 1))) ? 1 : 0;
		c = 1 - c;
		if (children[c] != NULL) {
			res = (~num & (1 << (index - 1)));
			res |= children[c]->excrusive_search(num, index - 1);
		}
		else {
			c = 1 - c;
			res = (num & (1 << (index - 1)));
			res |= children[c]->excrusive_search(num, index - 1);
		}
		return res;
	}
	int excrusive_search(int num) {
		return excrusive_search(num, 31);
	}
};

int main(void) {
	int n;
	int ans = 0;
	Trie* trie = new Trie();
	cin >> n;
	while (n--) {
		int num;
		cin >> num;
		trie->add(num);
		int tmp = trie->excrusive_search(num);
		tmp ^= num;
		if (ans < tmp)
			ans = tmp;
	}
	cout << ans << '\n';
	return 0;
}