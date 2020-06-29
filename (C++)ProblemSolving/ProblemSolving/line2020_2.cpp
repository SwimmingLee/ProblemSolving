#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(string answer_sheet, vector<string> sheets) {
	int answer = 0;
	for (int i = 0; i < sheets.size(); i++) {
		for (int j = i + 1; j < sheets.size(); j++) {
			if (sheets[i].size() != sheets[j].size()) continue;
			int cnt = 0;
			int max_cnt = 0;
			int score = 0;
			for (int k = 0; k < sheets[i].size(); k++) {
				if (sheets[i][k] == sheets[j][k] && \
					sheets[i][k] != answer_sheet[k]) {
					cnt += 1;
					score += 1;
					max_cnt = max(max_cnt, cnt);
				}
				else {
					cnt = 0;
				}
			}
			answer = max(answer, score + max_cnt * max_cnt);
		}
	}
	return answer;
}

int main(void) {
	string answer_sheet;
	vector<string> sheets;

	answer_sheet = "24551";
	sheets.push_back("14523");
	sheets.push_back("14523");
	cout << solution(answer_sheet, sheets);
}