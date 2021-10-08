#include <iostream>
#include <vector>
using namespace std;


const int INF = 987654321;
#define MAXN 12
int n, k, m, l;
// prerequisite[i]: i번째 과목의 선수과목 집합
int prerequisite[MAXN];
// classes[i]: i번째 학기에 개설되는 과목의 집합
int classes[10];
int bitCount(int n);

int graduate(int semester, int taken) {
	if (bitCount(taken) >= k) return 0;
	if (semester == m) return INF;
	
	int ret = INF;
	// 들을 수 있는 과목을 구해야 함
	int canTake = classes[semester] & ~taken;
	for (int i = 0; i < n; i++) {
		if ((canTake & (1 << i)) && ((prerequisite[i] & taken) != prerequisite[i])) {
			canTake &= ~(1 << i);
		}
	}

	// 들을 수 있는 과목중에 최대 l개를 골라 선택함
	for (int subset = canTake; subset; subset = (subset - 1) & canTake) {
		if (bitCount(subset) > l) continue;
		ret = min(ret, graduate(semester + 1, taken | subset) + 1);
	}
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}
