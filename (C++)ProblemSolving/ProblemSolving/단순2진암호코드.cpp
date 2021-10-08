#include <iostream>
#include <string>
using namespace std;


string pattern[50];
int height, width;
int keys[10] = { 0x0D, 0x19, 0x13, 0x3D, 0x23,
			0x31, 0x2F, 0x3B, 0x37, 0x0B };
void input() {
	cin >> height >> width;
	for (int i = 0; i < height; ++i) {
		cin >> pattern[i];
	}
}

int passwordRow() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (pattern[i][j] != '0') return i;
		}
	}
	return -1;
}

int transKey(int n) {
	for (int i = 0; i < 10; i++) {
		if (keys[i] == n) return i;
	}
	return -1;
}

int password[8] = { 0, 0,};


int isPassword(int r, int offset) {
	if (offset + 56 >= width) return -1;

	int odd, even, sum;
	bool correct = true;
	sum = odd = even = 0;
	if (offset == 0) {
		for (int i = 0; i < 8; ++i) {
			password[i] = 0;
			for (int j = 0; j < 7; ++j) {
				password[i] <<= 1;
				password[i] |= ((pattern[r][(i * 7) + j] == '0') ? 0 : 1);
			}

			int key = transKey(password[i]);
			if (key == -1) correct = false;

			sum += key;
			if (i != 7) {
				if (i & 1) {
					odd += key;
				}
				else {
					even += key;
				}
			}
		}
	}
	else {
		for (int i = 0; i < 8; ++i) {
			password[i] <<= 1;
			password[i] &= ~(1 << 7);
			password[i] |= (pattern[r][((i+1) * 7) - 1 + offset] == '0' ? 0 : 1);

			int key = transKey(password[i]);
			if (key == -1) correct = false;

			sum += key;
			if (i != 7) {
				if (i & 1) {
					odd += key;
				}
				else {
					even += key;
				}
			}
		}
	}

	if (!correct) {
		return -1;
	}
	// 암호 발견
	if ((even * 3 + odd + transKey(password[7])) % 10 == 0) {
		return sum;
	}
}

void print(int n) {
	for (int i = 7; i >= 0; i--) {
		cout << ((n & (1 << i)) ? 1 : 0);
	}
	cout << ' ';
}

int decodePattern() {
	int r = passwordRow();
	if (r == -1 || width < 55) return 0;
	
	int answer = 0;
	for (int i = 0; i < width; i++) {
		answer = isPassword(r, i);
		
		if (answer != -1) return answer;

	}

	return 0;
}

int main() {
	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		input();
		int answer = decodePattern();
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}