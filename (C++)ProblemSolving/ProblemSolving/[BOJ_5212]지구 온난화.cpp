#include <iostream>
#include <string>
#include <vector>
using namespace std;

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int main(void) {
	int height, width;
	vector<string> board;
	cin >> height >> width;
	board.resize(height);

	for (int r = 0; r < height; r++) {
		cin >> board[r];
	}
	vector<pair<int, int>> st;

	int minx = -1, miny = -1, maxx = 0, maxy = 0;
	// 모든 함수를 다 찾음. 그리고 최소x,y갱신 - 최대 x,y갱신하면됨
	for (int r = 0; r < height; r++) {
		for (int w = 0; w < width; w++) {
			if (board[r][w] != 'X') continue;

			int cnt = 0;
			for (int i = 0; i < 4; i++) {
				int ny = r + dy[i];
				int nx = w + dx[i];
				if (ny >= 0 && nx >= 0 && ny < height && nx < width && board[ny][nx] == 'X') continue;
				
				cnt += 1;
			}
			if (cnt >= 3) {
				st.push_back({ r, w });
				//board[r][w] = '.';
			}
			else {
				if (minx == -1 || minx > w) minx = w;
				if (miny == -1 || miny > r) miny = r;
				if (maxx < w) maxx = w;
				if (maxy < r) maxy = r;
			}
		}
	}
	while (!st.empty()) {
		pair<int, int> cur = st.back(); st.pop_back();
		board[cur.first][cur.second] = '.';
	}
	//cout << "ANS " << minx << miny << maxx << maxy << "\n";
	for (int r = miny; r <= maxy; r++) {
		for (int w = minx; w <= maxx; w++) {
			cout << board[r][w];
		}
		cout << '\n';
	}
	return 0;
}