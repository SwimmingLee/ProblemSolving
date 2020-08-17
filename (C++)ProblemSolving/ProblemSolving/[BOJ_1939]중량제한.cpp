#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
int N, M;
int factoryA, factoryB;
vector<vector<pii>> adj;

bool linkIsland(int u, int v, int limit) {
	queue<int> q;
	vector<bool> chk(N+1, false);

	q.push(u);
	chk[u] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		//cout << "[] " << cur << endl;
		for (int i = 0; i < adj[cur].size(); i++) {
			pii next_bridge = adj[cur][i];
			if (!chk[next_bridge.first] && next_bridge.second >= limit) {
				if (next_bridge.first == v) return true;
				chk[next_bridge.first] = true;
				q.push(next_bridge.first);
			}
		}
	}
	return false;
}

void solve() {
	int start, mid, end;
	start = 1;
	end = 1e9;
	int res = 0;
	while (start <= end) {
		mid = start + (end - start) / 2;
		//cout << mid;
		bool ok = linkIsland(factoryA, factoryB, mid);
		//cout << " " << ok << endl;
		if (ok) {
			start = mid + 1;
			if (res < mid) {
				res = mid;
			}
		}
		else {
			end = mid - 1;
		}
	}
	cout << res;
}

int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> N >> M;
	adj.resize(N+1);
	for (int i = 0; i < M; i++) {
		int u, v, limit;
		cin >> u >> v >> limit;
		adj[u].push_back({ v, limit });
		adj[v].push_back({ u, limit });
	}
	cin >> factoryA >> factoryB;
	solve();
	return 0;
}