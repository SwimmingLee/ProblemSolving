#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int a[16];
int b[16];
int cache_cw[15][15];
int cache_ccw[15][15];
vector<int> weak_;
vector<int> dist_;
int board_sz;

int cw(int weak_idx, int dist_idx) {
	int& res = cache_cw[weak_idx][dist_idx];
	if (res != 0) return res;
	int sz = dist_.size();
	// weak[idx]에서 시계방향으로 dist[sz - i - 1]만큼 이동하면서 취약점 확인
	int start = weak_[weak_idx];
	int end = weak_[weak_idx] + dist_[dist_idx];

	for (int j = 0; j < weak_.size(); j++) {
		if ((start <= weak_[j] && weak_[j] <= end) || (end >= board_sz && weak_[j] <= end - board_sz)) {
			res |= 1 << j;
		}
	}
	return res;
}

int ccw(int weak_idx, int dist_idx) {
	int& res = cache_ccw[weak_idx][dist_idx];
	if (res != 0) return res;

	int sz = dist_.size();
	// weak[idx]에서 반시계방향으로 dist[sz - i - 1]만큼 이동하면서 취약점 확인
	int end = weak_[weak_idx];
	int start = weak_[weak_idx] - dist_[sz - dist_idx - 1];

	for (int j = 0; j < weak_.size(); j++) {
		if ((start <= weak_[j] && weak_[j] <= end) || (start < 0 && weak_[j] >= board_sz - start)) {
			res |= 1 << j;
		}
	}
	return res;
}

bool permu2(int n, int depth) {
	bool res = false;
	if (depth == n) {
		int res = 0;
		for (int i = 0; i < n; i++) {
			if (b[i] == 0) {
				res |= cw(a[i], i);
			}
			else {
				res |= ccw(a[i], i);
			}
		}
		if (res == ((1 << weak_.size()) - 1)) return true;
		return false;
	}
	for (int i = 0; i < 2; i++) {
		b[depth] = i;
		res = permu2(n, depth + 1);
		if (res) return true;
	}
	return false;
}

int upperBound(int key) {
	int start, mid, end;
	int res = weak_.size();
	start = 0;
	end = res - 1;
	while (start <= end) {
		mid = start + (end - start) / 2;
		if (key < weak_[mid]) {
			end = mid - 1;
			if (res == -1 || res > mid) {
				res = mid;
			}
		}
		else {
			start = mid + 1;
		}
	}
	return res;
}

bool permu(int n, int depth, int chk) {
	bool res = false;
	if (depth == n) {
		//int chk_idx = 0;
		//int wall_chk = 0;
		cout << "[] ";
		for (int i = 0; i < n; i++)
			cout << a[i] << ' ';
		cout << endl;
		for (int i = 0; i < weak_.size(); i++) {
			int wall_staus = 0;
			int next = i;
			for (int j = 0; j < n; j++) {
				cout << "next: " << next << endl;
				int start = weak_[next];
				int end = weak_[next] + dist_[a[j]];

				for (int k = 0; k < weak_.size(); k++) {
					next = (next + k) % weak_.size();
					if ((start <= weak_[next] && weak_[next] <= end) || (end >= board_sz && weak_[next] <= end - board_sz)) {
						wall_staus |= 1 << next;
					}
					else {
						break;
					}
				}
			}
			cout << wall_staus << endl;
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