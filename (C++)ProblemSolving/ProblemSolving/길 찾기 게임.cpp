#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
	int y, x, v;
};
struct Tree {
	int value;
	Tree* child[2];
};	


bool cmp(const Node& u, const Node& v) {
	if (u.y == v.y) return u.x < v.x;
	else return u.v > v.y;
}

int findLeftChild(int start, int y, int x) {
	int cy = -1, cx = -1;
	int idx = -1;
	for (int i = start; i < nodes.size(); i++) {
		if (nodes[i].y < y && cy < nodes[i].y && nodes[i].x > x && nodes[i].x > cx) {
			cy = nodes[i].y;
			cx = nodes[i].x;
			idx = i;
		}
	}
	cout << "idx : " << idx << endl;
	return idx;
}
int findRightChild(int start, int y, int x) {
	int cy = -1, cx = 100001;
	int idx = -1;
	for (int i = start; i < nodes.size(); i++) {
		if (nodes[i].y < y && cy < nodes[i].y && nodes[i].x < x && nodes[i].x < cx) {
			cy = nodes[i].y;
			cx = nodes[i].x;
			idx = i;
		}
	}
}
void preoder(Tree* v, vector<vector<int>>& ans) {
	ans[0].push_back(v->value);
	for (int i = 0; i < 2; i++) {
		if (v->child[i] != NULL) {
			cout << "AA\n";
			preoder(v->child[i], ans);
		}
	}
	ans[1].push_back(v->value);
}
//void postorder(Tree* v, vector<vector<int>>& ans) {
//}
vector<Node> sorted_nodes;
vector<vector<Node>> layered_nodes;
// 인덱스는 위에서부터 아래로 왼쪽에서 오른쪽으로 정렬한 노드의 번호
Tree ntree[10001];
void attachChild(int depth, int sx, int ex) {
	ntree[depth].child[0] = attachChild(depth + 1, );
	ntree[depth].child[1] = attachChild(depth + 1, );
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer(2);
	for (int i = 0; i < nodeinfo.size(); i++) {
		sorted_nodes.push_back({nodeinfo[i][1], nodeinfo[i][0], i });
	}
	sort(sorted_nodes.begin(), sorted_nodes.end(), cmp);
	
	int layer = sorted_nodes[0].y;
	vector<Node> nodes;
	for (int i = 0; i < sorted_nodes.size(); i++) {
		if (layer != sorted_nodes[i].y) {
			layer = sorted_nodes[i].y;
			layered_nodes.push_back(nodes);
			nodes.clear();
		}
		nodes.push_back(sorted_nodes[i]);
	}

	
	attachChild(0, 0, 10000);

	return answer;
}