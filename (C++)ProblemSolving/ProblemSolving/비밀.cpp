#include <iostream>
using namespace std;

#define MAX_NODE 11

int N, K;
bool adj[MAX_NODE][MAX_NODE];
bool visited[MAX_NODE];

void init() {
	for (int i = 1; i <= N; ++i) {
		visited[i] = false;
		for (int j = 1; j <= N; ++j) {
			adj[i][j] = false;
		}
	}
}

int longest(int n) {
	int ret = 0;

	visited[n] = true;
	for (int next = 1; next <= N; ++next) {
		if (adj[n][next] && !visited[next]) {
			ret = max(ret, longest(next));
		}
	}
	visited[n] = false;
	return ret + 1;
	
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> K;
		init();
		for (int i = 0; i < K; ++i) {
			int n;
			cin >> n;

			int prev = -1;
			for (int j = 0; j < n; ++j) {
				int u;
				cin >> u;

				if (prev != -1) {
					adj[prev][u] = true;
				}
				prev = u;
			}
		}

		cout << '#' << tc << ' ';
		for (int i = 1; i <= N; ++i) {
			int friends = 0;
			for (int j = 1; j <= N; ++j) {
				if (adj[i][j] != 0)
					friends++;
			}
			cout << friends << ' ';
		}

		int answer = 0;
		for (int i = 1; i <= N; ++i)
			if (!visited[i])
				answer = max(answer, longest(i));
		cout << answer << '\n';
	}
}