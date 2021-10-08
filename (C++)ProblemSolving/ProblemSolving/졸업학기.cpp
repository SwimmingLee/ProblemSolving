#include <iostream>
#include <vector>
using namespace std;


const int INF = 987654321;
#define MAXN 12
int n, k, m, l;
// prerequisite[i]: i��° ������ �������� ����
int prerequisite[MAXN];
// classes[i]: i��° �б⿡ �����Ǵ� ������ ����
int classes[10];
int bitCount(int n);

int graduate(int semester, int taken) {
	if (bitCount(taken) >= k) return 0;
	if (semester == m) return INF;
	
	int ret = INF;
	// ���� �� �ִ� ������ ���ؾ� ��
	int canTake = classes[semester] & ~taken;
	for (int i = 0; i < n; i++) {
		if ((canTake & (1 << i)) && ((prerequisite[i] & taken) != prerequisite[i])) {
			canTake &= ~(1 << i);
		}
	}

	// ���� �� �ִ� �����߿� �ִ� l���� ��� ������
	for (int subset = canTake; subset; subset = (subset - 1) & canTake) {
		if (bitCount(subset) > l) continue;
		ret = min(ret, graduate(semester + 1, taken | subset) + 1);
	}
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}
