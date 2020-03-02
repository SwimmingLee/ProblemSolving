#include <iostream>
#include <string>
using namespace std;

int getcarnumber(string& p) {
	int ans = 1;
	int pre_c = 0;
	for (char c : p) {
		if (c == 'd') {
			if (pre_c == 'd')
				ans *= 9;
			else
				ans *= 10;
		}
		else if (c == 'c') {
			if (pre_c == 'c')
				ans *= 25;
			else
				ans *= 26;
		}
		pre_c = c;
	}
	return ans;
}
int main(void) {
	string pattern;
	cin >> pattern;

	cout << getcarnumber(pattern) << '\n';
	return 0;
}