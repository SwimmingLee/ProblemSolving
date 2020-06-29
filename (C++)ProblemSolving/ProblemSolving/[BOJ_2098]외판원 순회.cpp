//#include <iostream>
//#include <string>
//#include <vector>
//#include <queue>
//using namespace std;
//
//#define MAX_SIZE	8
//#define ALPHABETS	26
//
//struct Trie {
//	Trie* children[ALPHABETS];
//	int valid;
//	Trie* pi;
//	Trie(): valid(0), pi(NULL) {
//		for (int i = 0; i < ALPHABETS; i++) {
//			children[i] = NULL;
//		}
//	}
//	~Trie() {
//		for (int i = 0; i < ALPHABETS; i++) {
//			delete children[i];
//		}
//	}
//	void add(int index, string p) {
//		if (p.size() == index) {
//			valid = 1;
//			return;
//		}
//		int c = p[index] % ALPHABETS;
//		if (children[c] == NULL) {
//			children[c] = new Trie();
//		}
//		children[c]->add(index + 1, p);
//	}
//	void add(string p) {
//		add(0, p);
//	}
//};
//int path[8];
//Trie* trie;
//void dfs(int index, int n, int visited, string& pattern) {
//	if (index == n) {
//		string p(n, 0);
//		for (int i = 0; i < n; i++) {
//			p[i] = pattern[path[i]];
//		}
//		trie->add(p);
//		return;
//	}
//	for (int i = 0; i < n; i++) {
//		if (!(visited & (1 << i))) {
//			path[index] = i;
//			dfs(index + 1, n, visited | (1 << i), pattern);
//		}
//	}
//} //dfs(0, n, m, 0);
//
//int solution(string s, string p) {
//	int answer = 0;
//	trie = new Trie();
//	dfs(0, (int)p.size(), 0, p);
//
//	queue<Trie*> q;
//	trie->pi = trie;
//	q.push(trie);
//	while (!q.empty()) {
//		//cout << "AA " << endl;
//		Trie* cur = q.front();
//		q.pop();
//		for (int i = 0; i < ALPHABETS; i++) {
//			Trie* next = cur->children[i];
//			if (next == NULL) continue;
//			if (cur == trie) {
//				next->pi = trie;
//			}
//			else {
//				Trie* x = cur->pi;
//				while (x != trie && x->children[i] == NULL) {
//					x = x->pi;
//				}
//				if (x->children[i] != NULL) {
//					x = x->children[i];
//				}
//				next->pi = x;
//			}
//			Trie* pi = next->pi;
//			next->valid += pi->valid;
//			q.push(next);
//		}
//	}
//
//	Trie* node = trie;
//	for (int i = 0; i < s.size(); i++) {
//		int c = s[i] % ALPHABETS;
//		while (node != trie && node->children[c] == NULL) {
//			node = node->pi;
//		}
//		if (node->children[c] != NULL) {
//			node = node->children[c];
//		}
//		answer += node->valid;
//	}
//	delete trie;
//	return answer;
//}
//
//
//int main(void) {
//	string s, p;
//	cin >> s >> p;
//	cout << solution(s, p) << endl;
//	return 0;
//}