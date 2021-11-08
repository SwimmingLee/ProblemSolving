#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int N;
string board[1000];
int acc0vertical[1000][1000];
int acc0horizon[1000][1000];
int cache[1000][1000];
/*
* 나는 정말 이상하게 문제를 풀었구나...
* 누적합 + DP 짬뽕해서 풀었다.. 하하 
*/
void init() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cache[i][j] = -1;
		}
	}
}

int largeSquare(int r, int c) {
	if (r >= N || c >= N)
		return 0;

	int& ret = cache[r][c];
	if (ret != -1)
		return ret;

	ret = acc0vertical[r][c];
	ret = min(ret, acc0horizon[r][c]);
	ret = min(ret, largeSquare(r + 1, c + 1)+1);

	return ret;
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N;
		init();
		for (int i = 0; i < N; ++i) {
			cin >> board[i];
		}

		int acc = 0;
		for (int c = 0; c < N; ++c) {
			for (int r = N - 1; r >= 0; --r) {
				if (board[r][c] == '0') {
					acc++;
				}
				else {
					acc = 0;
				}
				acc0vertical[r][c] = acc;
			}
		}

		acc = 0;
		for (int r = 0; r < N; ++r) {
			for (int c = N - 1; c >= 0; --c) {
				if (board[r][c] == '0') {
					acc++;
				}
				else {
					acc = 0;
				}
				acc0horizon[r][c] = acc;
			}
		}
		
		int answer = 0;
		for (int r = 0; r < N; ++r) {
			for (int c = 0; c < N; ++c) {
				if (board[r][c] == '0') {
					answer = max(answer, largeSquare(r, c));
				}
			}
		}
		cout << '#' << tc << ' ' << answer << '\n';
	}
	
	return 0;
}