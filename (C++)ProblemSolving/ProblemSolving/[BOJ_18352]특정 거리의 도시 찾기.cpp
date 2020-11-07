#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> adj[300000];

int main(void) {
	int n_city, n_road, k, start;
	cin >> n_city >> n_road >> k >> start;

	for (int i = 0; i < n_road; i++) {
		int u, v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
	}

	queue<int> q;
	vector<int> been(n_city, -1);
	vector<int> answer;
	q.push(start - 1);
	been[start - 1] = 0;
	
	while (!q.empty()) {
		int cur = q.front();
		int next_cnt = been[cur] + 1;
		q.pop();

		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i];
			if (been[next] != -1) continue;
			
			q.push(next);
			been[next] = next_cnt;
			if (next_cnt == k) {
				answer.push_back(next);
			}
		}
	}

	sort(answer.begin(), answer.end());
	if (answer.size()) {
		for (auto c : answer) {
			cout << c+1 << endl;
		}
	}
	else {
		cout << -1;
	}
	return 0;
}