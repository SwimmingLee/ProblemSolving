//#include <iostream>
//#include <vector>
//#include <string>
//#include <algorithm>
//using namespace std;
//
//int n_problem;
//int n_order;
//bool visited[32001];
////bool adj[32001][32001];
//vector<vector<int>> adj;
//vector<string> ans;
//
//string problemOrdering(int n) {
//	vector<string> str;
//	string seq = "";
//	sort(adj[n].begin(), adj[n].end());
//	for (int i = 0; i < adj[n].size(); i++) {
//		if (!visited[adj[n][i]]) {
//			visited[adj[n][i]] = true;
//			str.push_back(problemOrdering(adj[n][i]));
//		}
//	}
//	sort(str.begin(), str.end());
//	for (int i = 0; i < str.size(); i++) {
//		seq += str[i];
//	}
//	seq.push_back(n + '0');
//	return seq;
//}
//
//void solve() {
//	for (int i = 1; i <= n_problem; i++) {
//		if (!visited[i]) {
//			visited[i] = true;
//			string temp = problemOrdering(i);
//
//			ans.push_back(temp);
//		}
//	}
//	sort(ans.begin(), ans.end());
//	for (int i = 0; i < ans.size(); i++) {
//		//cout << ans[i] << ' ';
//		for (int j = 0; j < ans[i].size(); j++) {
//			cout << ans[i][j] << ' ';
//		}
//	}
//	cout << "\n";
//}
//
//
//int main(void) {
//	cin >> n_problem >> n_order;
//	adj.resize(n_problem + 1);
//
//	for (int i = 0; i < n_order; i++) {
//		int a, b;
//		cin >> a >> b;
//		//adj[b][a] = 1;
//		adj[b].push_back(a);
//	}
//
//	solve();
//	return 0;
//}
//
//5 4
//4 1
//5 1
//2 5
//3 5


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n_problem;
int n_order;
vector<vector<int>> adj;
vector<int> inode;

void solve() {
	priority_queue<int> pq;
	for (int i = 1; i <= n_problem; i++) {
		if (inode[i] == 0) pq.push(i);
	}

	while (!pq.empty()) {
		int cur = pq.top();
		cout << cur << ' ';
		pq.pop();

		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i];
			inode[next]--;

			if (inode[next] == 0) pq.push(next);
		}
	}
}


int main(void) {
	cin >> n_problem >> n_order;
	adj.resize(n_problem+1);
	inode.resize(n_problem+1);
	for (int i = 0; i < n_order; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		inode[a]++;
	}
	solve();
	return 0;
}