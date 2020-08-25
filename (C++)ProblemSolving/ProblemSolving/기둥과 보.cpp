#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
#define BO	1
#define GI	0
int board[101][101];

int board_sz;
// 1 ���
// 2 �� 
// 3 ��� + �� 
bool isGenOk(int x, int y, int a) {
	//cout << x << " " << y << " " << a << endl;
	if (a == BO) {
		if (x >= board_sz || y == 0) return false;
		// �ؿ� ����� ��ġ�Ǿ� ������ �� ��ġ ����
		if (board[y - 1][x] & 1) return true;
		// ������ �ؿ� ����� ��ġ�Ǿ� ������ �� ��ġ ����
		else if (board[y - 1][x + 1] & 1) return true;
		// �� ������ ���� ��ġ�Ǿ� ������ �� ��ġ ����
		else if (x > 0 && x < board_sz && (board[y][x - 1] & 2) && (board[y][x + 1] & 2)) return true;
	}
	else if (a == GI) {
		if (y == board_sz) return false;
		// �ٴڿ� ������ ��� ��ġ ����
		if (y == 0) return true;
		// ���� ��ġ�� ���� ������ ��� ��ġ ����
		else if (board[y][x] & 2) return true;
		// ���ʿ��� ������ ���� ������ ��� ��ġ ����
		else if (x > 0 && (board[y][x - 1] & 2)) return true;
		// ������� ��տ� �ִ� ���
		else if (board[y-1][x] & 1) return true;
	}
	return false;
}

bool isReOk(int x, int y, int a) {
	if (a == GI) board[y][x] &= ~(1 << GI);
	else if (a == BO) board[y][x] &= ~(1 << BO);

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			int nx = x + i;
			int ny = y + j;

			if (nx < 0 || ny < 0 || nx > board_sz || ny > board_sz) continue;
			if (board[ny][nx] & 1) {
				if (!isGenOk(nx, ny, 0)) {
					if (a == GI) board[y][x] |= (1 << GI);
					else if (a == BO) board[y][x] |= (1 << BO);
					return false;
				}
			}
			if (board[ny][nx] & 2) {
				if (!isGenOk(nx, ny, 1)) {
					if (a == GI) board[y][x] |= (1 << GI);
					else if (a == BO) board[y][x] |= (1 << BO);
					return false;
				}
			}
		}
	}
	return true;
}

bool compare(const vector<int>& a, const vector<int>& b) {
	if (a[0] == b[0]) {
		if (a[1] == b[1]) return a[2] < b[2];
		else return a[1] < b[1];
	}
	else return a[0] < b[0];
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	board_sz = n;
	vector<vector<int>> answer;
	for (int i = 0; i < build_frame.size(); i++) {
		int x, y, a, b;
		x = build_frame[i][0];
		y = build_frame[i][1];
		a = build_frame[i][2];
		b = build_frame[i][3];

		//y = n - y;
		
		if (b == 1) {
			/*cout << "instal;\n";*/
			if (isGenOk(x, y, a)) {
				//cout << "��� ��" << x << " " << y << " " << a << endl;
				//cout << "��ġ�Ϸ�\n";
				board[y][x] |= (1 << a);
				answer.push_back({ x, y, a });
			}
		}
		if (b == 0) {
			if (isReOk(x, y, a)) {
				//cout << "del " << x << " " << y << " " << a << endl;
				int sz = answer.size();
				for (int k = 0; k < sz; k++) {
					if (answer[k][0] == x && answer[k][1] == y && answer[k][2] == a) {
						for (int j = k; j < sz - 1; j++) {
							answer[j][0] = answer[j + 1][0];
							answer[j][1] = answer[j + 1][1];
							answer[j][2] = answer[j + 1][2];
						}
						answer.pop_back();
						break;
					}
				}
			}
		}
		//cout << "[] " << x << " " << y << " " << a << endl;
		//for (int k = 0; k <= n; k++) {
		//	for (int j = 0; j <= n; j++) {
		//		cout << board[n - k][j] << ' ';
		//	}
		//	cout << endl;
		//}
	}
	sort(answer.begin(), answer.end(), compare);
	return answer;
}