#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX_COMPANY 20001

struct disjointSet {
	vector<int> parent;
	vector<int> distance;
	int num_company;
	disjointSet() {
		parent.resize(MAX_COMPANY);
		distance.resize(MAX_COMPANY);
	}
	void init(int num) {
		num_company = num;
		for (int i = 0; i <= num_company; i++) {
			parent[i] = i;
			distance[i] = 0;
		}
	}
	int dist(int u) {
		find(u);
		return distance[u];
	}
	int find(int u) {
		if (parent[u] == u) {
			return u;
		}
		else {
			int v = find(parent[u]);
			if (distance[u] == 0) {
				distance[u] = abs(parent[u] - u) % 1000 + distance[parent[u]];
			}
			else {
				distance[u] += distance[parent[u]];
			}
			parent[u] = v;
			return v;
		}
	}
	void merge(int u, int v) {
		parent[u] = v;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int tc;
	disjointSet company;
	cin >> tc;
	while (tc--) {
		int num_company;
		char command;
		int u, v;

		cin >> num_company;
		company.init(num_company);
		while (true) {
			cin >> command;
			if (command == 'E') {
				cin >> u;
				cout << company.dist(u) << '\n';
			}
			else if (command == 'I') {
				cin >> u >> v;
				company.merge(u, v);
			}
			else {
				break;
			}
		}
	}
	return 0;
}