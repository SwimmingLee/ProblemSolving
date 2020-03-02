#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define VERTICAL	0
#define HORIZON		1
int height, width;
vector<string> board;
int GetMaxScore() {
	int max_score = 0;
	for (int pattern = 0; pattern < (1 << (height * width)); pattern++) {
		int score = 0;
		for (int r = 0; r < height; r++) {
			int tmp = 0;
			for (int c = 0; c < width; c++) {
				if ((pattern & (1 << (width * r + c))) == VERTICAL)
					tmp = tmp * 10 + board[r][c] - '0';
				else
					score += tmp, tmp = 0;
			}
			score += tmp;
		}
		for (int c = 0; c < width; c++) {
			int tmp = 0;
			for (int r = 0; r < height; r++) {
				if ((pattern & (1 << (width * r + c))) != VERTICAL)
					tmp = tmp * 10 + board[r][c] - '0';
				else
					score += tmp, tmp = 0;
			}
			score += tmp;
		}
		if (score > max_score)
			max_score = score;
	}
	return max_score;
}
int main(void) {
	cin >> height >> width;
	board.resize(height);
	for (int i = 0; i < height; i++) {
		cin >> board[i];
	}
	cout << GetMaxScore() << '\n';
}