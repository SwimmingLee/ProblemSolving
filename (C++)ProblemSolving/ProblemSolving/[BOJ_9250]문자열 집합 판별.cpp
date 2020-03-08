#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define ALPHABETS	26
#define ROOT_IDX	0

struct Node {
	int children[ALPHABETS];
	bool valid;
	int pi;
	Node() : valid(false), pi(-1) {
		for (int i = 0; i < ALPHABETS; i++)
			children[i] = -1;
	}
};
vector<Node> trie;
int init() {
	Node x;
	trie.push_back(x);
	return trie.size() - 1;
}
void add(int node, string& str, int index) {
	if (str.size() == index) {
		trie[node].valid = true;
		return;
	}
	int c = str[index] % ALPHABETS;
	if (trie[node].children[c] == -1) {
		int next = init();
		trie[node].children[c] = next;
	}
	add(trie[node].children[c], str, index + 1);
}
void add(string& str) {
	add(ROOT_IDX, str, 0);
}


int main(void) {
	ios_base::sync_with_stdio(false);


	int root = init();
	string str;
	int n, m;
	cin >> n;
	while (n--) {
		cin >> str;
		add(str);
	}
	queue<int> q;
	trie[root].pi = root;
	q.push(root);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < ALPHABETS; i++) {
			int next = trie[cur].children[i];
			if (next == -1) continue;
			if (cur == root) {
				trie[next].pi = root;
			}
			else {
				int x = trie[cur].pi;
				while (x != root && trie[x].children[i] == -1) {
					x = trie[x].pi;
				}
				if (trie[x].children[i] != -1) {
					x = trie[x].children[i];
				}
				trie[next].pi = x;
			}
			int pi = trie[next].pi;
			trie[next].valid |= trie[pi].valid;
			q.push(next);
		}
	}
	cin >> m;
	while (m--) {
		cin >> str;
		int node = root;
		bool ok = false;
		for (int i = 0; i < str.size(); i++) {
			int c = str[i] % ALPHABETS;
			while (node != root && trie[node].children[c] == -1) {
				node = trie[node].pi;
			}
			if (trie[node].children[c] != -1) {
				node = trie[node].children[c];
			}
			if (trie[node].valid) {
				ok = true;
				break;
			}
		}
		cout << (ok ? "YES" : "NO") << '\n';
	}
	return 0;
}