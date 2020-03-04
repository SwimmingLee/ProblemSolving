#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define ALPHABETS (127-32+1)

int num_tree;
struct trie {
	trie* children[ALPHABETS];
	bool valid;
	int priority;
	trie(): valid(false), priority(0) {
		for (int i = 0; i < ALPHABETS; i++)
			children[i] = NULL;
	}
	void add(string& str, int index) {
		if (str.size() == index) {
			valid = true;
			priority++;
			return;
		}
		int c = (str[index] - ' ');//% ALPHABETS;
		if (children[c] == NULL) {
			children[c] = new trie();
		}
		children[c]->add(str, index + 1);
	}
	void add(string& str) {
		add(str, 0);
	}
	void print(string& tree) {
		if (valid) {
			cout << tree << ' ';
			cout << (double)priority / num_tree * 100 << '\n';
		}
		for (int i = 0; i < ALPHABETS; i++) {
			if (children[i] != NULL) {
				tree.push_back(i + ' ');
				children[i]->print(tree);
				tree.pop_back();
			}
		}
	}
	void print() {
		string tree;
		print(tree);
	}
};

int main(void) {
	cout.setf(ios::fixed);
	cout.precision(4);

	string tree;
	trie* Trie = new trie();
	while (getline(cin, tree)) {
		Trie->add(tree);
		num_tree++;
	}
	Trie->print();
	return 0;
}