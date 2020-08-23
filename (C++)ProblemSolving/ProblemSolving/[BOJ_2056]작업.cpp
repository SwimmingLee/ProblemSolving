#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n_task;
vector<int> ind;
vector<int> task_time;
vector<int> total_time;
vector<vector<int>> adj;


int topological_sort() {
	queue<int> q;
	int res = 0;
	for (int i = 0; i < n_task; i++) {
		if (!ind[i]) {
			q.push(i);
			total_time[i] = task_time[i];
		}
	}

	while (!q.empty()) {
		int cur = q.front(); q.pop();
		//cout << "[ ] "<< cur <<  total_time[cur] << endl;
		if (res < total_time[cur]) {
			res = total_time[cur];
		}

		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i];
			int next_time = task_time[next] + total_time[cur];
			if (next_time > total_time[next]) total_time[next] = next_time;
			ind[next]--;
			
			if (!ind[next]) q.push(next);
		}
	}

	return res;
}

int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> n_task;
	ind.resize(n_task);
	adj.resize(n_task);
	task_time.resize(n_task);
	total_time.resize(n_task, 0);

	for (int i = 0; i < n_task; i++) {
		int time, n_sub;
		cin >> time >> n_sub;
		task_time[i] = time;
		ind[i] = n_sub;
		for (int j = 0; j < n_sub; j++) {
			int sub;
			cin >> sub;
			adj[sub - 1].push_back(i);
		}
	}

	cout << topological_sort() << '\n';
	return 0;
}