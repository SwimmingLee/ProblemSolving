#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int N, M;
int words[10000];
string word;
int alphaSet;
int cache[(1 << 26)];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		cin >> word;
		for (int j = 0; j < word.size(); ++j) {
			words[i] |= (1 << (word[j] - 'a'));
		}
	}
	alphaSet = (1 << 26) - 1;
	memset(cache, -1, (1 << 26) * sizeof(int));
	int op;
	char alpha;
	for (int i = 0; i < M; ++i) {
		cin >> op >> alpha;
		if (op == 1) {
			alphaSet &= ~(1 << (alpha - 'a'));
		}
		else {
			alphaSet |= (1 << (alpha - 'a'));
		}
		int cnt = 0;
		if (cache[alphaSet] == -1) {
			for (int j = 0; j < N; ++j) {
				if ((alphaSet & words[j]) == words[j]) {
					++cnt;
				}
			}
		}
		else {
			cnt = cache[alphaSet];
		}
		cout << cnt << '\n';
	}
	return 0;
}