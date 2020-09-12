#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int pstage[505];
struct Fail {
	int stage;
	double fail_rate;
	bool operator< (const Fail& rhs) {
		if (fail_rate == rhs.fail_rate) return stage < rhs.stage;
		else return fail_rate > rhs.fail_rate;
	}
};

vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	int n_stage = stages.size();
	// 각 스테이지에 존재하는 사람들 부분합으로 구하기
	// pstage[i] => 현재 i번쨰 스테이지 이하로 있는 사람 숫자
	for (int i = 0; i < n_stage; i++ ) {
		pstage[stages[i]]++;
	}
	for (int i = 1; i <= N+1; i++) {
		pstage[i] += pstage[i - 1];
		cout << pstage[i] << " ";
	}
	cout << endl;
	vector<Fail> fail;
	for (int i = 1; i <= N; i++) {
		int mother = n_stage - pstage[i-1];
		int child = pstage[i] - pstage[i - 1];
		double rate = (mother == 0 ? 0 : (double)child / mother);
		fail.push_back({ i, rate });
		//cout << "[] " << i << " " << child << " " << mother << endl;
	}
	sort(fail.begin(), fail.end());
	for (int i = 0; i < fail.size(); i++) {
		answer.push_back(fail[i].stage);
	}
	return answer;

}