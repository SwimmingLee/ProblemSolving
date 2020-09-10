#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n_home;
int k, l;
bool checkKey(int h, int w, vector<vector<int>>& key, vector<vector<int>>& lock) {
	int home = 0;
	for (int n = 0; n < k; n++) {
		for (int m = 0; m < k; m++) {
			int lock_y = h + n - (k - 1);
			int lock_x = w + m - (k - 1);
			if (lock_y < 0 || lock_y >= l || lock_x < 0 || lock_x >= l) continue;

			if (key[n][m] == lock[lock_y][lock_x]) return false;
			else if (lock[lock_y][lock_x] == 0) home++;
		}
	}

	if (home == n_home) return true;
	else return false;
}

vector<vector<int>> rotation(vector<vector<int>> key) {
	vector<vector<int>> new_key(k, vector<int>(k));

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			new_key[j][k - 1 - i] = key[i][j];
		}
	}
	return new_key;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	k = key.size();
	l = lock.size();
	// lock의 홈 수 체크하기
	for (int h = 0; h < l; h++) {
		for (int w = 0; w < l; w++) {
			if (lock[h][w] == 0) n_home++;
		}
	}

	vector<vector<int>> rot_key[4];
	rot_key[0] = key;
	// key 회전해서 4개의 키 만들기
	for (int i = 0; i < 3; i++) {
		rot_key[i + 1] = rotation(rot_key[i]);
	}

	// key가 시작할 위치를 부여하기 
	for (int i = 0; i < l + k - 1; i++) {
		for (int j = 0; j < l + k - 1; j++) {
			for (int rot = 0; rot < 4; rot++) {
				if (checkKey(i, j, rot_key[rot], lock)) return true;
			}
		}
	}
	// key가 시작되는 위치에서 검사해보기
	return false;
}