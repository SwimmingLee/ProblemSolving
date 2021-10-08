#include <iostream>
#include <string>
using namespace std;

#define CODE(X) ((X)-'A')
int n;
int ncode[26][26][26];
int cnt[11];
string s;
string scode[] = {
	"ZRO",
	"ONE",
	"TWO",
	"THR",
	"FOR",
	"FIV",
	"SIX",
	"SVN",
	"EGT",
	"NIN"
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int TC;
	cin >> TC;
	//ncode[CODE('Z')][CODE('R')][CODE('O')] = 1;
	//ncode[CODE('O')][CODE('N')][CODE('E')] = 2;
	//ncode[CODE('T')][CODE('W')][CODE('O')] = 3;
	//ncode[CODE('T')][CODE('H')][CODE('R')] = 4;
	//ncode[CODE('F')][CODE('O')][CODE('R')] = 5;
	//ncode[CODE('F')][CODE('I')][CODE('V')] = 6;
	//ncode[CODE('S')][CODE('I')][CODE('X')] = 7;
	//ncode[CODE('S')][CODE('V')][CODE('N')] = 8;
	//ncode[CODE('E')][CODE('G')][CODE('T')] = 9;
	//ncode[CODE('N')][CODE('I')][CODE('N')] = 10;
	for (int i = 0; i < 10; ++i) {
		ncode[scode[i][0]][scode[i][1]][scode[i][2]] = i + 1;
	}
 
	string tmp;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		cin >> tmp >> n;
		for (int i = 0; i < n; ++i) {
			cin >> s;
			int num = ncode[CODE(s[0])][CODE(s[1])][CODE(s[2])];
			cnt[num]++;
		}

		cout << '#' << test_case << '\n';
		for (int i = 0; i < 10; ++i) {
			while (cnt[i+1]--) {
				cout << scode[i] << ' ';
			}
			cnt[i+1] += 1;
		}
		cout << '\n';
	}
	return 0;
}