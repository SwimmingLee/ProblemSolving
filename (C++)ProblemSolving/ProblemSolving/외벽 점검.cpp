#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int a[16];
vector<int> weak_;
vector<int> dist_;
int board_sz;

bool permu(int n, int depth, int chk) {
	bool res = false;
	if (depth == n) {
		for (int i = 0; i < weak_.size(); i++) {
			int wall_staus = 0;
			int next = i;
			for (int j = 0; j < n; j++) {
				int start = weak_[next];
				int end = weak_[next] + dist_[a[j]];

				for (int k = 0; k < weak_.size(); k++) {
					if ((start <= weak_[next] && weak_[next] <= end) || (end >= board_sz && weak_[next] <= end - board_sz)) {
						wall_staus |= 1 << next;
						next = (next + 1) % weak_.size();
					}
					else {
						break;
					}
				}
			}
			if (wall_staus == ((1 << (weak_.size())) - 1)) return true;
		}
		return false;
	}
	for (int i = 0; i < n; i++) {
		if (!(chk & (1 << i))) {
			a[depth] = i;
			res = permu(n, depth + 1, chk | (1 << i));
			if (res) return true;
		}
	}
	return false;
}
int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = -1;
	sort(dist.begin(), dist.end(), [](int a, int b) {return a > b; });

	board_sz = n;
	weak_.assign(weak.begin(), weak.end());
	dist_.assign(dist.begin(), dist.end());

	for (int i = 1; i <= dist.size(); i++) {
		bool res = permu(i, 0, 0);
		if (res) {
			answer = i;
			break;
		}
	}
	return answer;
}