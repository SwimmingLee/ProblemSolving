#include <iostream>
#include <queue>
using namespace std;

long long A, B;

int main(void) {
	cin >> A >> B;
	queue<pair<long long, int>> Q;
	Q.push({ A, 1 });

	int answer = -1;
	while (!Q.empty()) {
		pair<long long, int> cur = Q.front();
		Q.pop();

		if (cur.first > B) continue;
		else if (cur.first == B) {
			answer = cur.second;
			break;
		}
		else {
			Q.push({ cur.first * 2, cur.second + 1 });
			Q.push({ cur.first * 10 + 1, cur.second + 1 });
		}
	}
	cout << answer;
	return 0;
}