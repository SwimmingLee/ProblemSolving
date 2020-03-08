#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int num_problem;
int bottom_limit, top_limit, diff_limit;
vector<int> problem;

int GetOutcomes(int cnt, int score, int min_score, int max_score) {
	int ans = 0;
	if (cnt == num_problem) {
		if (max_score - min_score >= diff_limit && score >= bottom_limit && score <= top_limit) return 1;
		else return 0;
	}
	int min_next = min(min_score, problem[cnt]);
	int max_next = max(max_score, problem[cnt]);
	ans += GetOutcomes(cnt + 1, score + problem[cnt], min_next, max_next);
	ans += GetOutcomes(cnt + 1, score, min_score, max_score);
	return ans;
}

int main(void) {
	cin >> num_problem >> bottom_limit >> top_limit >> diff_limit;
	problem.resize(num_problem);
	for (int i = 0; i < num_problem; i++)
		cin >> problem[i];
	cout << GetOutcomes(0, 0, 987987987, 0) << '\n';
	return 0;
}