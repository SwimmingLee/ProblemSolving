#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAX_STRING	1000000

int fail[MAX_STRING];
string haystack;

int powerString() {
	int L = haystack.size();
	int j = 0;
	for (int i = 1; i < L; ++i) {
		while (j > 0 && haystack[i] != haystack[j]) {
			j = fail[j - 1];
		}
		if (haystack[i] == haystack[j]) {
			fail[i] = ++j;
		}
		else {
			fail[i] = 0;
		}
	}

	// fail[L-1]는 powerLength 이상이기만 하면 됨!
	
	//answer = (len % (len - table[len - 1]));
	//answer = answer == 0 ? (len / (len - table[len - 1])) : 1;


	int powerLength = 1;
	for (int i = 1; i < L; ++i) {
		if ((L % i) != 0) continue;

		bool isPowerLength = true;
		for (int j = 2; i*j - 1 < L; ++j) {
			if (fail[i * j - 1] < i) {
				isPowerLength = false;
				break;
			}
		}

		if (isPowerLength) {
			powerLength = L/i;
			break;
		}
	}

	return powerLength;
}

int main(void) {
	int T;
	//ifstream cin("C:\\Users\\swimm\\Downloads\\sample_input (8).txt");
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> haystack;
		int answer = powerString();
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}