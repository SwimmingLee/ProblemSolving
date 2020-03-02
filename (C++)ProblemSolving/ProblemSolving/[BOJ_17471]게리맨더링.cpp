#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int num_city;
vector<int> pop_city;
vector<vector<int>> city;

int getMinDiff() {
	int min_diff = -1;
	for (int part = 1; part < (1 << num_city - 1); part++) {
		int visited = 0;
		int sum_partA = 0;
		int sum_partB = 0;
		for (int i = 0; i < num_city; i++) {
			if (sum_partA != 0) break;
			if ((part & (1 << i)) != 0) continue;
			queue<int> q;
			q.push(i);
			visited |= (1 << i);
			sum_partA += pop_city[i];
			while (!q.empty()) {
				int here = q.front();
				q.pop();

				for (int j = 0; j < city[here].size(); j++) {
					int next_city = city[here][j] - 1;
					if ((visited & (1 << next_city)) != 0 || (part & (1 << next_city)) != 0) continue;
					visited |= (1 << next_city);
					q.push(next_city);
					sum_partA += pop_city[next_city];
				}

			}
		}

		for (int i = 0; i < num_city; i++) {
			if (sum_partB != 0) break;
			if ((part & (1 << i)) == 0) continue;
			queue<int> q;
			q.push(i);
			visited |= (1 << i);
			sum_partB += pop_city[i];
			while (!q.empty()) {
				int here = q.front();
				q.pop();
				for (int j = 0; j < city[here].size(); j++) {
					int next_city = city[here][j] - 1;
					if ((visited & (1 << next_city)) != 0 || (part & (1 << next_city)) == 0) continue;
					visited |= (1 << next_city);
					q.push(next_city);
					sum_partB += pop_city[next_city];
				}

			}
		}

		if (visited == ((1 << num_city) - 1)) {
			int diff = abs(sum_partA - sum_partB);
			if (min_diff == -1 || min_diff > diff) {
				min_diff = diff;
			}
		}
	}
	return min_diff;
}

int main(void) {
	cin >> num_city;
	pop_city.resize(num_city);
	city.resize(num_city);
	for (int i = 0; i < num_city; i++) {
		cin >> pop_city[i];
	}
	for (int i = 0; i < num_city; i++) {
		int num_connect;
		cin >> num_connect;
		city[i].resize(num_connect);
		for (int j = 0; j < num_connect; j++) {
			cin >> city[i][j];
		}
	}

	cout << getMinDiff() << '\n';
	return 0;
}