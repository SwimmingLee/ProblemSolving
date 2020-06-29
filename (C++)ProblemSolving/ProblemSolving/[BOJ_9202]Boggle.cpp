//#include <iostream>
//#include <string>
//#include <vector>
//#include <queue>
//using namespace std;
//
//#define ALPHABETS	26
//#define BOARD_SZ	4
//int dy[] = { 0, 0, 1, -1 };
//int dx[] = { 1, -1, 0, 0 };
//
//vector<string> board;
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
//			if (children[i] != NULL)
//				delete children[i];
//		}
//	}
//	void add(string& s, int index, int snum) {
//		if (s.size() == index) {
//			valid = 1 << snum;
//			return;
//		}
//		int c = s[index] % ALPHABETS;
//		if (children[c] == NULL) {
//			children[c] = new Trie();
//		}
//	}
//};
//
//Trie* trie;
//
//void search(int y, int x, Trie* node, int cnt) {
//	for (int i = 0; i < 4; i++) {
//		int ny = y + dy[i];
//		int nx = x + dx[i];
//
//		if (ny < 0 || nx < 0 || ny >= BOARD_SZ || nx >= BOARD_SZ) continue;
//		int c = board[ny][nx] % ALPHABETS;
//		Trie* next = node;
//		while (next != trie && next->children[c] == NULL) next = next->pi;
//		if (next->children[c] != NULL) {
//			if (cnt != 0 && next == trie) continue;
//			if (next->valid) {
//				// 문자열 찾았다. no return
//			}
//			search(ny, nx, next->children[c], cnt+1);
//		}
//
//	}
//}
//
//void boggle() {
//	queue<Trie*> q;
//	q.push(trie);
//	trie->pi = trie;
//	while (!q.empty()) {
//		Trie* cur = q.front();
//		q.pop();
//
//		for (int i = 0; i < ALPHABETS; i++) {
//			Trie* next = cur->children[i];
//			if (next == NULL) continue;
//			if (next == trie) {
//				next->children[i] = trie;
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
//			pi->valid |= next->valid;
//			q.push(next);
//		}
//	}
//
//	for (int i = 0; i < BOARD_SZ; i++) {
//		for (int j = 0; j < BOARD_SZ; j++) {
//			board[i][j];
//		}
//	}
//}
//
//int main(void) {
//	int n;
//	trie = new Trie();
//	board.resize(BOARD_SZ);
//	cin >> n;
//	for (int i = 0; i < n; i++) {
//		string s;
//		cin >> s;
//		trie->add(s, 0, i);
//	}
//	
//	int m;
//	cin >> m;
//	while (m--) {
//		for (int i = 0; i < BOARD_SZ; i++) {
//			cin >> board[i];
//		}
//		boggle();
//	}
//	return 0;
//}