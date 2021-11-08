#include <iostream>
#include <string>
using namespace std;

int shape[26];
int card[4][15];
int numCard[15];
int shapeCard[4];

void init() {
	for (int n = 1; n <= 14; ++n) {
		numCard[n] = 0;
	}
	for (int s = 0; s < 4; ++s) {
		shapeCard[s] = 0;
	}

	for (int s = 0; s < 4; ++s) {
		for (int n = 1; n <= 14; ++n) {
			card[s][n] = 0;
		}
	}
}

string poker() {
	// Straight Flush 판별 
	for (int s : {'S', 'D', 'C', 'H'}) {
		int cnt = 1;
		for (int n = 2; n <= 14; ++n) {
			if (card[shape[s - 'A']][n] && card[shape[s - 'A']][n - 1]) {
				cnt++;
			}
			else {
				cnt = 1;
			}

			if (cnt >= 5)
				return "Straight Flush";
		}
	}

	int pairCnt = 0;
	int tripleCnt = 0;
	// 4 Card 판별 - Full House(1Pair, 2Pair, Triple) 조사
	for (int n = 1; n <= 13; ++n) { /**/
		if (numCard[n] >= 4)
			return "4 Card";
		else if (numCard[n] == 3) {
			tripleCnt++;
		}
		else if (numCard[n] == 2) {
			pairCnt++;
		}
	}

	if ((pairCnt > 0 && tripleCnt > 0) || tripleCnt >= 2) /**/
		return "Full House";
	
	// Flush 판별
	for (int s = 0; s < 4; ++s) {
		if (shapeCard[s] >= 5)
			return "Flush";
	}

	// Straight 판별
	int cnt = 1;
	for (int n = 2; n <= 14; ++n) {
		if (numCard[n] > 0 && numCard[n - 1] > 0) {
			cnt++;
		}
		else {
			cnt = 1;
		}

		if (cnt >= 5) {
			return "Straight";
		}
	}


	if (tripleCnt > 0)
		return "Triple";
	else if (pairCnt > 1)
		return "2 Pair";
	else if (pairCnt == 1)
		return "1 Pair";
	else
		return "Top";
}

int main(void) {
	int T;
	cin >> T;
	shape['S' - 'A'] = 0;
	shape['D' - 'A'] = 1;
	shape['C' - 'A'] = 2;
	shape['H' - 'A'] = 3;

	for (int tc = 1; tc <= T; ++tc) {
		init();
		for (int i = 0; i < 7; ++i) {
			char s;
			int num;
			cin >> s >> num;
			
			if (num == 1) {
				card[shape[s - 'A']][14]++;
				numCard[14]++;
			}

			card[shape[s - 'A']][num]++;
			shapeCard[shape[s - 'A']]++;
			numCard[num]++;
		}

		cout << '#' << tc << ' ' << poker() << '\n';
	}
	return 0;
}