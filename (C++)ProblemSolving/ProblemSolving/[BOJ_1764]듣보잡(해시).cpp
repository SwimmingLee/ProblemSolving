#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_TABLE	(599999)
//해쉬는 해쉬테이블 크기에 따라 속도 차이가 현저하게 난다.
// 600000  40ms
// 700000  44ms
// 800000  44ms
// 1000000 52ms

typedef struct {
	string key;
	int data;
} Hash;

Hash tb[MAX_TABLE];

vector<string> ll;

unsigned long hashFunc(string& str) {
	unsigned long hash = (unsigned long)tb;
	int c;
	const char* tmp = str.c_str();

	while (c = *(tmp++)) {
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

int add(string& key, int data) {
	unsigned long h = hashFunc(key);

	while (tb[h].key != "") {
		/*if (tb[h].key.compare(key) == 0) {
			return;
		}*/
		h = (h + 1) % MAX_TABLE;
	}

	tb[h].key = key;
	tb[h].data = data;
	return 1;
}

void find(string& key) {
	unsigned long h = hashFunc(key);

	while (tb[h].key != "") {
		if (tb[h].key.compare(key) == 0) {
			ll.push_back(key);
			return;
		}
		h = (h + 1) % MAX_TABLE;
	}
}
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int nLook, nListen;
	string str;
	cin >> nListen >> nLook;

	for (int i = 0; i < nListen; i++) {
		cin >> str;
		add(str, 0);
	}
	for (int i = 0; i < nLook; i++) {
		cin >> str;
		find(str);
	}

	sort(ll.begin(), ll.end());

	cout << ll.size() << '\n';

	string ans = "";
	for (auto it : ll) {
		ans += it + '\n';
	}
	cout << ans;

	return 0;
}