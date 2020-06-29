//#include <string>
//#include <vector>
//#include <deque>
//#include <iostream>
//using namespace std;
//
//bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
//	bool answer = true;
//	vector<vector<int>> adj(n);
//	vector<bool> seen(n, false);
//	vector<bool> order_chk(order.size(), false);
//
//	for (auto p : path) {
//		int u = p[0];
//		int v = p[1];
//
//		adj[u].push_back(v);
//		adj[v].push_back(u);
//	}
//
//	deque<int> q;
//	int node = 0;
//	q.push_back(node);
//	seen[node] = true;
//	while (!q.empty()) {
//		int cur = q.front(); q.pop_front();
//		cout << cur << endl;
//		bool chk = true;
//		for (int i = 0; i < adj[cur].size(); i++) {
//			int next = adj[cur][i];
//			bool ok = true;
//			for (int j = 0; j < order.size(); j++) {
//				if (next == order[j][0]) {
//					order_chk[j] = true;
//					break;
//				}
//
//				if (!order_chk[j] && next == order[j][1]) {
//					chk = false;
//					ok = false;
//					break;
//				}
//			}
//			
//			if (ok && !seen[next]) {
//				q.push_front(next);
//				seen[next] = true;
//			}
//		}
//		if (!chk) {
//			q.push_back(cur);
//		}
//	}
//
//	return answer;
//}
//
//void pushData(vector<vector<int>>& v, int a, int b) {
//	vector<int> tmp;
//	tmp.push_back(a);
//	tmp.push_back(b);
//	v.push_back(tmp);
//}
//int main(void) {
//	int n = 9;
//	vector<vector<int>> path;
//	vector<vector<int>> order;
//
//	pushData(path, 0, 1);
//	pushData(path, 0, 3);
//	pushData(path, 0, 7);
//
//	pushData(path, 8, 1);
//	pushData(path, 3, 6);
//	pushData(path, 1, 2);
//	pushData(path, 4, 7);
//	pushData(path, 7, 5);
//
//	pushData(order, 8, 5);
//	pushData(order, 6, 7);
//	pushData(order, 4, 1);
//
//
//	bool res = solution(n, path, order);
//	cout << res << endl;
//}