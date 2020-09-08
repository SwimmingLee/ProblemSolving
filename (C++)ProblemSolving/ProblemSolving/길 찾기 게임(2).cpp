#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
	int y, x, v;
	Node* left, *right;
	Node(int y, int x, int v) : y(y), x(x), v(v) {
		left = right = NULL;
	}
	bool operator< (const Node& rts) {
		if (y == rts.y) return x < rts.x;
		else return y > rts.y;
	}
};

void addNode(Node* parent, Node* child) {
	if (child->x < parent->x) {
		if (parent->left == NULL) parent->left = child;
		else addNode(parent->left, child);
	}
	else {
		if (parent->right == NULL) parent->right = child;
		else addNode(parent->right, child);
	}
}
void order(Node* pnode, vector<vector<int>>& ans) {
	ans[0].push_back(pnode->v);
	if (pnode->left) order(pnode->left, ans);
	if (pnode->right) order(pnode->right, ans);
	ans[1].push_back(pnode->v);
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer(2);

	vector<Node> nodes;
	for (int i = 0; i < nodeinfo.size(); i++) {
		nodes.push_back(Node(nodeinfo[i][1], nodeinfo[i][0], i + 1));
	}
	sort(nodes.begin(), nodes.end());
	
	Node* root = &nodes[0];
	for (int i = 1; i < nodes.size(); i++) {
		addNode(root, &nodes[i]);
	}

	order(root, answer);
	return answer;
}