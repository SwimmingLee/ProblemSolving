#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define ACIDS		4
#define ROOT_IDX	0
int dna_sz, marker_sz;
string dna, marker;

struct Node {
	int children[ACIDS];
	int	cnt;
	int pi;
	Node() : cnt(0), pi(-1) {
		for (int i = 0; i < ACIDS; i++)
			children[i] = -1;
	}
};
int convert(char c) {
	if (c == 'A') return 0;
	else if (c == 'T') return 1;
	else if (c == 'G') return 2;
	else return 3;
}
vector<Node> trie;
int init() {
	Node x;
	trie.push_back(x);
	return (int)trie.size() - 1;
}
void add(int node, string& str, int index) {
	if (index == str.size()) {
		trie[node].cnt = 1;
		return;
	}
	int c = convert(str[index]);
	if (trie[node].children[c] == -1) {
		int next = init(); 
		trie[node].children[c] = next;
		//trie[node].children[c] = init();
	}
	add(trie[node].children[c], str, index + 1);
}

void add(string& str) {
	add(ROOT_IDX, str, 0);
}

int ApearMarker() {
	trie.clear();
	int root = init();
	vector<string> markers;
	for (int i = 0; i < marker_sz; i++) {
		for (int j = i; j < marker_sz; j++) {
			string new_marker = marker;
			reverse(new_marker.begin() + i, new_marker.begin() + j + 1);
			markers.push_back(new_marker);
		}
	}
	sort(markers.begin(), markers.end());
	markers.erase(unique(markers.begin(), markers.end()), markers.end());
	for (string& s : markers) {
		add(root, s, 0);
	}
	queue<int> q;
	trie[root].pi = root;
	q.push(root);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < ACIDS; i++) {
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
			trie[next].cnt += trie[pi].cnt;
			q.push(next);
		}
	}

	int ans = 0;
	int node = root;
	for (int i = 0; i < dna.size(); i++) {
		int c = convert(dna[i]);
		while (node != root && trie[node].children[c] == -1) {
			node = trie[node].pi;
		}
		if (trie[node].children[c] != -1) {
			node = trie[node].children[c];
		}
		ans += trie[node].cnt;
	}
	return ans;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int tc;
	cin >> tc;
	while (tc--) {
		cin >> dna_sz >> marker_sz >> dna >> marker;
		cout << ApearMarker() << '\n';
	}
	return 0;
}
