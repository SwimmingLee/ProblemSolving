#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
struct Task {
	int start;
	int end;
	int cost;
} task[500];
int cache[500];

void init() {
	for (int i = 0; i < N; ++i) {
		cache[i] = 0;
	}
}

int nextSchedule(int i) {
	int ret = N;

	int val = task[i].end;
	int start, end, mid;
	start = 0; end = N-1;
	while (start <= end) {
		mid = (start + end) / 2;
		// 현재 스케쥴을 끝나고 나서 시작할 수 있는 스케쥴
		if (task[mid].start > val) {
			if (ret > mid) {
				ret = mid;
			}
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}
	}
	return ret;
}


int calcMaxCost(int i) {
	if (i >= N) return 0; // base condition없는 DP가 있나..? 흑

	int& ret = cache[i];
	if (ret != 0)
		return ret;

	ret = max(calcMaxCost(i + 1), calcMaxCost(nextSchedule(i)) + task[i].cost);
	return ret;
}


int main(void) {
	int T;
	cin >> T;
	for (int tc=1; tc <= T; ++tc){
		cin >> N >> M;
		init(); // DP초기화는 당연한것인데...
		for (int i = 0; i < N; ++i) {
			cin >> task[i].start >> task[i].end >> task[i].cost;
		}
		sort(task, task + N, [](const Task& lhs, const Task& rhs) {return lhs.start < rhs.start; });
		int answer = calcMaxCost(0);
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}