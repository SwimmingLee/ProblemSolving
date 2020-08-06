#include <iostream>
#include <set>
using namespace std;
int n_train, n_cmd;

int train[100000];

int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> n_train >> n_cmd;
	while (n_cmd--) {
		int cmd, train_idx, seq = 0;
		cin >> cmd >> train_idx;
		if (cmd == 1 || cmd == 2) {
			cin >> seq;
		}
		train_idx -= 1;;
		seq -= 1;

		if (cmd == 1) {
			train[train_idx] |= 1 << seq;
		}
		else if (cmd == 2) {
			train[train_idx] &= ~(1 << seq);
		}
		else if (cmd == 3) {
			train[train_idx] = train[train_idx] << 1;
			train[train_idx] &= ~(1 << 20);
		}
		else {
			train[train_idx] = train[train_idx] >> 1;
		}
	}
	
	set<int> chk;
	int answer = 0;
	for (int i = 0; i < n_train; i++) {
		if (chk.find(train[i]) == chk.end()) {
			chk.insert(train[i]);
			answer++;

		}
	}

	cout << answer;

	return 0;
}