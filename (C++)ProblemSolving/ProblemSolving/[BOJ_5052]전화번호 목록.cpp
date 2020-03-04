#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define ALPHABETS 10
bool state;
struct trie {
	trie* children[ALPHABETS];
	int valid;
	trie(): valid(0) {
		for (int i = 0; i < ALPHABETS; i++)
			children[i] = NULL;
	}
	~trie() {
		for (int i = 0; i < ALPHABETS; i++) {
			if (children[i]) delete children[i];
		}
	}
	void add(string& str, int index) {
		if (str.size() == index) {
			valid = true;
			for (int i = 0; i < ALPHABETS; i++)
				if (children[i]) state = false;
			return;
		}
		if (valid) {
			state = false;
			return;
		}
		int c = str[index] % ALPHABETS;
		if (children[c] == NULL) {
			children[c] = new trie();
		}
		children[c]->add(str, index + 1);
	}
	void add(string& str) {
		add(str, 0);
	}
};

int main() {
	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		trie* Trie = new trie();
		string phone_number;
		
		cin >> n;
		state = true;
		while (n--) {
			cin >> phone_number;
			if (state) Trie->add(phone_number);
		}
		if (state) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}