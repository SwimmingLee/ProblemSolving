#include <string>
#include <vector>
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
	bool operator< (const Node& rts) {
		if (y == rts.y) return x < rts.x;
		else return y > rts.y;
	}
};


vector<vector<Node>> layered_nodes;
void attachChild(Node** node, int start_x, int end_x, int depth) {
	//cout << "[][] " << layered_nodes.size() << " " << depth << endl;
	if (depth >= layered_nodes.size()) return;


	bool isOk = false;
	for (int i = 0; i < layered_nodes[depth].size(); i++) {
		if (start_x < layered_nodes[depth][i].x && layered_nodes[depth][i].x < end_x) {
			*node = &layered_nodes[depth][i];
			isOk = true;
			break;
		}
	}
	if (!isOk) {
		//cout << start_x << " " << end_x << "ASD\n";
		return;
	}
	//cout << (*node)->v << endl;
	attachChild(&((*node)->child[0]), start_x, (*node)->x, depth + 1);
	attachChild(&((*node)->child[1]), (*node)->x, end_x, depth + 1);
}

void order(Node* node, vector<vector<int>>& ans) {
	ans[0].push_back(node->v);
	//cout << node->v << ' ';
	//cout << node->child[0] << endl;
	if (node->child[0]) order(node->child[0], ans);
	if (node->child[1]) order(node->child[1], ans);
	ans[1].push_back(node->v);
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer(2);

	vector<Node> nodes;
	for (int i = 0; i < nodeinfo.size(); i++) {
		nodes.push_back(Node(nodeinfo[i][1], nodeinfo[i][0], i + 1));
	}
	sort(nodes.begin(), nodes.end());

	int layer = nodes[0].y;
	vector<Node> trip_nodes;
	for (int i = 0; i < nodes.size(); i++) {
		if (layer != nodes[i].y) {
			layer = nodes[i].y;
			layered_nodes.push_back(trip_nodes);
			trip_nodes.clear();
		}
		trip_nodes.push_back(nodes[i]);
	}
	layered_nodes.push_back(trip_nodes);
	Node* pnode = &layered_nodes[0][0];
	attachChild(&pnode, -1, 100000000, 0);

	//cout << layered_nodes[0][0].v << endl;
	order(pnode, answer);
	return answer;
}