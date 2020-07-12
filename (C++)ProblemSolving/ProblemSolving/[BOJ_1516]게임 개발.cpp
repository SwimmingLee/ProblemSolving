#include <iostream>
#include <vector>
using namespace std;

int n_building;
int build_time[500];
int pre_time[500];

vector<vector<int>> adj;


void build(int node, int time) {
	if (pre_time[node] > time) return;
	pre_time[node] = time;

	for (int i = 0; i < adj[node].size(); i++) {
		build(adj[node][i], pre_time[node] + build_time[node]);
	}
}

int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> n_building;
	adj.resize(n_building);
	for (int i = 0; i < n_building; i++) {
		int time;
		cin >> time;
		build_time[i] = time;

		int pre_building;
		while (true) {
			cin >> pre_building;
			if (pre_building == -1) break;
			adj[pre_building-1].push_back(i);
		}
	}

	for (int i = 0; i < n_building; i++) {
		build(i, 0);
	}

	for (int i = 0; i < n_building; i++) {
		cout << pre_time[i] + build_time[i] << '\n';
	}
	return 0;
}