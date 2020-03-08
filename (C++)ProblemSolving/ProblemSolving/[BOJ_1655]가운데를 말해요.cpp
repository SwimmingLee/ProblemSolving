	#include <iostream>
	#include <queue>
	using namespace std;

	priority_queue<int> max_pq, min_pq;

	int SpeakCenter(int num) {
		if (max_pq.empty() || min_pq.empty()) {
			max_pq.push(num);
		}
		else {
			if (max_pq.top() <= num) {
				min_pq.push(-num);
			}
			else if (-min_pq.top() >= num) {
				max_pq.push(num);
			}
		}

		if (max_pq.size() > min_pq.size() + 1) {
			min_pq.push(-max_pq.top());
			max_pq.pop();
		}
		else if (max_pq.size() < min_pq.size()) {
			max_pq.push(-min_pq.top());
			min_pq.pop();
		}

		return max_pq.top();
	}

	int main(void) {
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		int N, num;
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> num;
			cout << SpeakCenter(num) << '\n';
		}
		return 0;
	}