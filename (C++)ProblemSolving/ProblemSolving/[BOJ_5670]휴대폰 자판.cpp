#include <iostream>
#include <string>
using namespace std;

#define ALPHABETS 26
struct trie {
	trie* children[ALPHABETS];
	bool valid;
	int num_children;
	trie() : valid(false), num_children(0) {
		for (int i = 0; i < ALPHABETS; i++)
			children[i] = NULL;
	}
	~trie() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i]) delete children[i];
	}
	void add(string& str, int index) {
		if (str.size() == index) {
			valid = true;
			return;
		}
		int c = str[index] % ALPHABETS;
		if (children[c] == NULL) {
			children[c] = new trie();
			num_children++;
		}
		children[c]->add(str, index + 1);
	}
	void add(string& str) {
		add(str, 0);
	}
	int fingerCnt(int cnt) {
		int cur = 0;
		for (int i = 0; i < ALPHABETS; i++) {
			if (children[i] != NULL)
				if (num_children > 1 || valid)
					cur += children[i]->fingerCnt(cnt+1);
				else
					cur += children[i]->fingerCnt(cnt);
		}
		if (valid)
			return cur + cnt;
		else
			return cur;
	}
	int fingerCnt() {
		return fingerCnt(0);
	}
};
int main(void) {
	cout.setf(ios::fixed);
	cout.precision(2);


	int num_str;
	while (cin >> num_str){
		trie* Trie = new trie();
		Trie->num_children++;
		for (int i = 0; i < num_str; i++) {
			string word;
			cin >> word;
			Trie->add(word);
		}
		cout << (float)Trie->fingerCnt() / num_str << '\n';
		delete Trie;
	}
	return 0;
}