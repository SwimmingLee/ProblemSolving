#include <iostream>
using namespace std;

int vertax, edge, target1, target2;
int parent[10001];
int tree[10001][2];
int depth[10001];
int nodeSize[10001];

void init() {
	for (int i = 1; i <= vertax; ++i) {
		depth[i] = 0;
		nodeSize[i] = 0;
		tree[i][0] = tree[i][1] = 0;
	}
}
void calcDepth(int cur) {
	for (int i = 0; i < 2; ++i) {
		int next = tree[cur][i];
		if (next == 0) break;
		depth[next] = depth[cur] + 1;
		calcDepth(next);
		nodeSize[cur] += nodeSize[next] + 1;
	}
}
int findLCA(int u, int v) {
	if (depth[u] < depth[v])
		swap(u, v);

	//cout << depth[u] << "  " << depth[v] << endl;
	while (depth[u] != depth[v]) {
		u = parent[u];
		//cout << u << "\n";
	}
	while (u != v) {
		u = parent[u];
		v = parent[v];
	}
	return u;
}
int main(void) {
	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		cin >> vertax >> edge >> target1 >> target2;
		init();
		for (int i = 0; i < edge; ++i) {
			int u, v;
			cin >> u >> v;
			parent[v] = u;
			if (tree[u][0] == 0) tree[u][0] = v;
			else tree[u][1] = v;
		}
		calcDepth(1);
		int lca = findLCA(target1, target2);
		cout << '#' << test_case << ' ' << lca << ' ' << nodeSize[lca]+1 << '\n';
	}
	return 0;
}