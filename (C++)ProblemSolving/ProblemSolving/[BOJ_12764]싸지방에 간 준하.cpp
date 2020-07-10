#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int n_person;
int max_computer_cnt;
int computer[100000];
int use[100000];

struct Task {
	int start_t;
	int end_t;
	int computer_no;
};

struct TaskCompare {
	bool operator()(const Task& lhs, const Task& rhs) {
		return lhs.end_t > rhs.end_t;
	}
};

vector<Task> task;

void solve() {
	sort(task.begin(), task.end(), [](Task& l, Task& r)->bool {return l.start_t < r.start_t; });
	priority_queue<Task, vector<Task>, TaskCompare> pq;
	priority_queue<int> usedComPQ;

	int com_sz = 0;
	for (int i = 0; i < task.size(); i++) {
		while (!pq.empty() && pq.top().end_t < task[i].start_t) {
			//use[pq.top().computer_no] = 0;
			usedComPQ.push(-pq.top().computer_no);
			pq.pop();
		}
		
		int computer_no;
		if (usedComPQ.empty()) {
			computer_no = com_sz;
			com_sz += 1;
		}
		else {
			computer_no = -usedComPQ.top();
			usedComPQ.pop();
		}
		//while (use[computer_no] != 0) {
		//	computer_no++;
		//}

		//use[computer_no] = 1;
		computer[computer_no]++;
		pq.push({ task[i].start_t, task[i].end_t, computer_no });

		//int q_sz = pq.size();
		//if (max_computer_cnt < q_sz) {
		//	max_computer_cnt = q_sz;
		//}
	}

	cout << com_sz << '\n';
	for (int i = 0; i < com_sz; i++) {
		cout << computer[i] << ' ';
	}
	cout << '\n';
}

int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> n_person;
	for (int i = 0; i < n_person; i++) {
		int st, et;
		cin >> st >> et;
		task.push_back({ st, et, 0 });
	}
	solve();
	return 0;
}