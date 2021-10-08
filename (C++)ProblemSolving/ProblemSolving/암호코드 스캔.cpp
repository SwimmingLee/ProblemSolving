#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string pattern[2000];
int height, width;
//int scode

/* 이 친구도 룩업 테이블로 교체할 수 있다. */
string makeBinaryStr(const string& w) {
	string res;
	for (int i = 0; i < w.size(); ++i) {
		if ('0' <= w[i] && w[i] <= '9') {
			int num = w[i] - '0';
			for (int j = 3; j >= 0; --j) {
				res.push_back((num & (1 << j)) ? '1' : '0');
			}
		}
		else {
			res.push_back('1');
			int num = w[i] - 'A' + 2;
			for (int j = 2; j >= 0; --j) {
				res.push_back((num & (1 << j)) ? '1' : '0');
			}
		}
	}
	return res;
}

void input() {
	ifstream in("C:\\Users\\swimm\\Downloads\\sample_input (1).txt");
	in >> height >> width;
	for (int i = 0; i < height; ++i) {
		string w;
		in >> w;
		pattern[i] = makeBinaryStr(w);
	}
	width <<= 2;
}



int transKey(int r, int start, int key_width) {
	if (pattern[r][start] == '1') return -1;

	int n[4] = { 1, 1, 1, 1 };
	int seq = 0;

	for (int i = 1; i < key_width * 7; ++i) {
		if (pattern[r][start + i] == pattern[r][start + i - 1]) {
			n[seq]++;
		}
		else {
			seq++;
			if (seq >= 4) return -1;
		}
	}
	
	if (seq != 3) return -1;

	int min_n = min(min(min(n[0], n[1]), n[2]), n[3]);
	for (int i = 0; i < 4; i++) {
		if (n[i] % min_n != 0) return -1;
		n[i] /= min_n;
	}
	
	//cout << "[]" << endl << start << endl;;
	//key = scode[n[0]][n[1]][n[2]]; 이런식으로 대체할 수 있다. 
	int key = -1;
	if (n[0] == 1) {
		if (n[1] == 1) {
			if (n[2] == 3 && n[3] == 2) key = 4;
			else if (n[2] == 1 && n[3] == 4) key = 6;
		}
		else if (n[1] == 2) {
			if (n[2] == 3 && n[3] == 1) key = 5;
			else if (n[2] == 1 && n[3] == 3) key = 8;
		}
		else if (n[1] == 3) {
			if (n[2] == 1 && n[3] == 2) key = 7;
		}
		else if (n[1] == 4) {
			if (n[2] == 1 && n[3] == 1) key = 3;
		}
	}
	else if (n[0] == 2) {
		if (n[1] == 2 && n[2] == 2 && n[3] == 1) key = 1;
		else if (n[1] == 1 && n[2] == 2 && n[3] == 2) key = 2;
	}
	else if (n[0] == 3) {
		if (n[1] == 2 && n[2] == 1 && n[3] == 1) key = 0;
		else if (n[1] == 1 && n[2] == 1 && n[3] == 2) key = 9;
	}
	return key;
}



int isPassword(int r, int offset, int key_width) {
	if (offset + 56 * key_width >= width) return 0;

	int odd, even, sum;
	int code;
	sum = odd = even = 0;

	for (int i = 0; i < 8; ++i) {
		int n = transKey(r, offset + i * (key_width * 7), key_width);
		if (n == -1) return 0;
		//cout << n << ' '<< offset << " " << offset + i * key_width * 7 << endl;
		sum += n;
		if (i != 7) {
			if (i & 1) odd += n;
			else even += n;
		}
		else {
			code = n;
		}
	}
	//cout << "[끝까지 순회]" << r << " " << offset << " " << key_width << " " << sum << endl;
	// 암호 발견
	if ((even * 3 + odd + code) % 10 == 0) {
		//cout << "[]" << endl;
		return sum;
	}
	else return 0;
}

void print(int n) {
	for (int i = 7; i >= 0; i--) {
		cout << ((n & (1 << i)) ? 1 : 0);
	}
	cout << ' ';
}

int decodePattern(int r) {
	int key_width = width / 56;
	int sum_password = 0;
	//cout << "{}???" << key_width << endl;
	for (int i = 0; i < width; ++i) {
		for (int j = 1; j <= key_width; ++j) {
			sum_password += isPassword(r, i, j);
			
 		}
	}
	return sum_password;
}

int solve() {
	int r_cnt = 1;
	int answer = 0;
	for (int i = 1; i < height; ++i) {
		if (pattern[i - 1] == pattern[i]) {
			r_cnt++;
		}
		else {
			if (r_cnt >= 5) {
				//cout << pattern[i - 1] << endl;
				bool isGo = false;
				for (int j = 0; j < width; ++j) {
					if (pattern[i - 1][j] != '0') isGo = true;
				}
				if (isGo)
					answer += decodePattern(i - 1);
			}
			r_cnt = 1;
		}
	}

	if (r_cnt >= 5) {
		bool isGo = false;
		for (int j = 0; j < width; ++j) {
			if (pattern[height - 1][j] != '0') answer += decodePattern(height - 1);
		}
		if (isGo)
			answer += decodePattern(height - 1);
	}
	return answer;
}

int main() {
	ifstream in("C:\\Users\\swimm\\Downloads\\sample_input (1).txt");
	int TC;
	in >> TC;
	int tt[20];
	
	for (int test_case = 1; test_case <= TC; ++test_case) {
		//input();
		in >> height >> width;
		for (int i = 0; i < height; ++i) {
			string w;
			in >> w;
			pattern[i] = makeBinaryStr(w);
		}
		width <<= 2;
		int answer = solve();
		tt[test_case - 1] = answer;
		cout << '#' << test_case << ' ' << answer << '\n';
	}
	for (int i = 0; i < TC; ++i) {
		cout << i << " " << tt[i] << endl;
	}
	return 0;
}


//int n = 10;
//void selectionSort(int A[], int idx) {
//	if (idx == n - 1) return;
//
//	int mini = idx;
//	for (int i = idx+1; i < n; ++i) {
//		if (A[mini] > A[i])  mini = i;
//	}
//	swap(A[idx], A[mini]);
//	selectionSort(A, idx + 1);
//}