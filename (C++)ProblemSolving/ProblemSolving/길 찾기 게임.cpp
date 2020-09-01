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
// 인덱스는 위에서부터 아래로 왼쪽에서 오른쪽으로 정렬한 노드의 번호
Tree ntree[10001];
vector<Node> nodes;
bool cmp(const Node& u, const Node& v) {
	if (u.y == v.y) return u.x < v.x;
	else return u.v > v.y;
}

int findLeftChild(int start, int y, int x) {
	int cy = -1, cx = -1;
	int idx = -1;
	for (int i = start; i < nodes.size(); i++) {
		if (nodes[i].y < y && cy < nodes[i].y && nodes[i].x < x && nodes[i].x > cx) {
			cy = nodes[i].y;
			cx = nodes[i].x;
			idx = i;
		}
	}

	return idx;
}
int findRightChild(int start, int y, int x) {
	int cy = -1, cx = 100001;
	int idx = -1;
	for (int i = start; i < nodes.size(); i++) {
		if (nodes[i].y < y && cy < nodes[i].y && nodes[i].x > x && nodes[i].x < cx) {
			cy = nodes[i].y;
			cx = nodes[i].x;
			idx = i;
		}
	}
}
void preoder(Tree* v, vector<vector<int>>& ans) {
	ans[0].push_back(v->value);
	for (int i = 0; i < 2; i++) {
		if (v->child[0] != NULL) {
			preoder(v->child[0], ans);
		}
	}
}
void 
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer;
	for (int i = 0; i < nodeinfo.size(); i++) {
		nodes.push_back({nodeinfo[i][1], nodeinfo[i][0], i });
	}
	sort(nodes.begin(), nodes.end(), cmp);
	int upper_idx, cur_sidx;
	int layer = nodes[0].y;
	for (int i = 0; i < nodes.size(); i++) {
		Node parent = nodes[i];
		ntree[i].value = parent.v;
		int left_child = findLeftChild(i + 1, parent.y, parent.x);
		int right_child = findRightChild(i + 1, parent.y, parent.x);
		ntree[i].child[0] = ((left_child != -1) ? &ntree[left_child] : NULL);
		ntree[i].child[1] = ((right_child != -1) ? &ntree[right_child] : NULL);
	}

	preoder(0);
	frexoder(0);

	return answer;
}