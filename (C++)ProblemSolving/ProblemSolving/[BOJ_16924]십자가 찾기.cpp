#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct star {
	int x;
	int y;
	int size;
};
int height, width, num_star;
vector<string> board;
vector<vector<int>> pboard;
vector<bool> visited;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };
void BoardSearch(int si, int sj, int di, int limi, int limj, int stat) {
	for (int i = si; i < limi && i >= 0; i+=di) {
		int star_sz = 0;
		for (int j = sj; j < limj && j >= 0; j+=di) {
			if (stat == 0) {
				if (board[i][j] == '*') star_sz++;
				else star_sz = 0;
				if (pboard[i][j] == -1 || star_sz < pboard[i][j])
					pboard[i][j] = star_sz;
			}
			else {
				if (board[j][i] == '*') star_sz++;
				else star_sz = 0;
				if (pboard[j][i] == -1 || star_sz < pboard[j][i])
					pboard[j][i] = star_sz;
			}
		}
	}
}

void GetPlus() {
	BoardSearch(0, 0, 1, height, width, 0);
	BoardSearch(height - 1, width - 1, -1, height, width, 0);
	BoardSearch(0, 0, 1, width, height, 1);
	BoardSearch(width - 1, height - 1, -1, width, height, 1);

	vector<star> Star;
	int tmp = 0;
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
				int star_sz = pboard[r][c];
				if (star_sz <= 1) continue;
				Star.push_back({ r + 1, c + 1, star_sz - 1 });
				if (!visited[r * width + c]) {
					visited[r * width + c] = true;
					tmp++;
				}
				for (int i = -(star_sz - 1); i <= star_sz -1; i++) {
					if (!visited[(r + i)* width + c]) {
						visited[(r + i) * width + c] = true;
						tmp++;
					}
					if (!visited[r * width + (c + i)]) {
						visited[r * width + (c + i)] = true;
						tmp++;
					}
				}
			
		}
	}
	if (tmp > 0 && tmp == num_star) {
		cout << Star.size() << '\n';
		for (auto s : Star) {
			cout << s.x << ' ' << s.y << ' ' << s.size << '\n';
		}
	}
	else {
		cout << -1;
	}

	
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> height >> width;
	board.resize(height);
	pboard.resize(height, vector<int>(width, -1));
	visited.resize(height * width, false);
	for (int i = 0; i < height; i++) {
		cin >> board[i];
		for (int j = 0; j < width; j++) {
			if (board[i][j] == '*')
				num_star++;
		}
	}
	GetPlus();
	return 0;
}