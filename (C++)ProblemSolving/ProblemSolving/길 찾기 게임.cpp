#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
	int y, x, v;
	Node* child[2];
	Node(int y, int x, int v) : y(y), x(x), v(v) {
		child[0] = NULL;
		child[1] = NULL;
	}
};
struct Tree {
	int value;
	Tree* child[2];
};	


bool cmp(const Node& u, const Node& v) {
	if (u.y == v.y) return u.x < v.x;
	else return u.v > v.y;
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
Node* attachChild(int depth, Node* u) {
	if (depth == layered_nodes[depth].size()) {
		return NULL;
	}
	
	u->child[0] = attachChild(depth + 1, sx, u.x);
	u->child[1] = attachChild(depth + 1, u.x, ex);

	return ntree
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer(2);
	for (int i = 0; i < nodeinfo.size(); i++) {
		sorted_nodes.push_back(Node(nodeinfo[i][1], nodeinfo[i][0], i ));
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
	int start_x = 0;
	int end_x = 
	attachChild(start_x, end_x, layer, node);

	return answer;
}