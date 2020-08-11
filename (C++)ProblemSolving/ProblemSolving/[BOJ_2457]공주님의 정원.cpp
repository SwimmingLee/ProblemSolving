#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
int mon_day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int total_day[13] = { 0 };

struct Flower {
	int s_day;
	int e_day;
	bool operator< (const Flower& rhs) const {
		return this->s_day < rhs.s_day;
	}
};

vector<Flower> flower;
void init() {
	for (int i = 1; i <= 12; i++) {
		total_day[i] = total_day[i - 1] + mon_day[i];
	}
}

void solve() {
	// 일수 계산 
	// m, d => total_day[m-1] + d
	int N = flower.size();
	int answer = 0;
	int line = total_day[2] + 1;
	int index = 0;

	int pline = line;
	sort(flower.begin(), flower.end());
	while (line <= total_day[10] + 30) {
		while (index < N && flower[index].s_day <= line) {
			pline = max(pline, flower[index].e_day);
			index++;
		}
		if (line == pline) {
			answer = 0;
			break;
		}
		line = pline;
		answer += 1;
	}
	cout << answer << '\n';
}


int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	init();
	int N;
	cin >> N;
	flower.resize(N);
	int s_mon, s_day, e_mon, e_day;
	for (int i = 0; i < N; i++) {
		cin >> s_mon >> s_day >> e_mon >> e_day;
		flower[i] = { total_day[s_mon - 1] + s_day, total_day[e_mon - 1] + e_day };
	}
	
	solve();
	return 0;
}