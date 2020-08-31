#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int n_row, n_col;
int a[10];
vector<vector<string>> rel;
vector<int> answers;
void permu(int m, int start, int depth) {
	if (depth == m) {
		vector<string> tmp;
		int t = 0;
		for (int i = 0; i < m; i++) {
			t |= (1 << a[i]);
		}
		for (int j = 0; j < n_row; j++) {
			string s;
			for (int i = 0; i < m; i++) {
				s += rel[j][a[i]];
			}
			tmp.push_back(s);
		}

		bool ok = true;
		for (int i = 0; i < tmp.size(); i++) {
			// if (t == 2) cout << tmp[i] << endl;
			for (int j = i + 1; j < tmp.size(); j++) {

				if (tmp[i] == tmp[j]) {
					ok = false;
					break;
				}
			}
		}
		if (ok) {
			answers.push_back(t);
		}
		return;
	}
	for (int i = start; i < n_col; i++) {
		a[depth] = i;
		permu(m, i + 1, depth + 1);
	}
}// permu(m, 0, 0);

int solution(vector<vector<string>> relation) {
	int answer = 0;
	n_row = relation.size();
	n_col = relation[0].size();

	rel.clear();
	rel.assign(relation.begin(), relation.end());

	for (int i = 1; i <= n_col; i++) {
		permu(i, 0, 0);
	}

	sort(answers.begin(), answers.end());
	int sz = answers.size();
	for (int i = 0; i < sz; i++) {
		for (int j = i + 1; j < sz; j++) {
			if ((answers[i] & answers[j]) == answers[i]) {
				// cout << " [] " << answers[j] << endl;
				for (int k = j; k < sz - 1; k++) {
					answers[k] = answers[k + 1];
				}
				sz -= 1;
				j--;
			}
		}
	}
	for (int i = 0; i < sz; i++) {
		cout << answers[i] << endl;
	}
	answer = sz;
	return answer;
}