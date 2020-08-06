//#include <iostream>
//#include <queue>
//#include <string>
//#include <algorithm>
//
//using namespace std;
//
//struct Trie {
//	Trie* child[26];
//	Trie* fail;
//	int cnt;
//	bool output;
//
//	Trie() {
//		fill(child, child + 26, nullptr);
//		cnt = 0;
//		output = false;
//	}
//	~Trie() {
//		for (int i = 0; i < 26; i++)
//			if (child[i]) delete child[i];
//	}
//
//	void insert(int depth, string& s) {
//		if (depth == s.size()) {
//			cnt++;
//			output = true;
//			return;
//		}
//		int next = s[depth];
//		if (!child[next]) {
//			child[next] = new Trie;
//		}
//		child[next]->insert(depth + 1, s);
//	}
//	void insert(string& s) {
//		insert(0, s);
//	}
//
//
//};
//
//int n_word;
//Trie* root;
//int countMethod(string& p) {
//	Trie* current = root;
//	bool result = false;
//	for (int i = 0; i < p.size(); i++) {
//		int next = p[i] - 'a';
//		while (current != root && !current->child[next]) {
//			current = current->fail;
//		}
//		if (current->child[next])
//			current = current->child[next];
//		if (current->output) {
//			result = true;
//			break;
//		}
//	}
//
//}
//
//
//int main(void) {
//	root = new Trie;
//
//	cin >> n_word;
//	while (n_word--) {
//		string s;
//		cin >> s;
//		root->insert(s);
//	}
//
//	queue<Trie*> q;
//	root->fail = root;
//	q.push(root);
//	while (!q.empty()) {
//		Trie* current = q.front();
//		q.pop();
//
//		for (int i = 0; i < 26; i++) {
//			Trie* next = current->child[i];
//			if (!next) continue;
//
//			if (current == root) next->fail = root;
//			else {
//				Trie* dest = current->fail;
//				while (dest != root && !dest->child[i]) {
//					dest = dest->fail;
//				}
//				if (dest->child[i]) dest = dest->child[i];
//				next->fail = dest;
//			}
//			if (next->fail->output) next->output = true;
//
//			q.push(next);
//		}
//	}
//	string p;
//	cin >> p;
//	cout << countMethod(p) << "\n";
//
//	return 0;
//}