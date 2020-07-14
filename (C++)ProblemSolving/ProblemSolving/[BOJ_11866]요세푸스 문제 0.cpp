#include <iostream>
#include <queue>
using namespace std;

int main(void) {
	int n, k;
	cin >> n >> k;
	
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		q.push(i);
	}

	cout << '<';
	while (!q.empty()) {
		for (int i = 1; i < k; i++) {
			int u = q.front(); q.pop();
			q.push(u);
		}

		int u = q.front(); q.pop();
		if (q.empty())
			cout << u;
		else
			cout << u << ", ";
	}
	cout << '>';
	return 0;
}