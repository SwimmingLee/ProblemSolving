#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int N;
string cache[251];

string sum(const string& a, const string& b) {
	string ret;
	int n = 0;
	int i = 0;
	do {
		if (i < a.size())
			n += a[i] - '0';
		if (i < b.size())
			n += b[i] - '0';
		i += 1;
		ret.push_back(n % 10 + '0');
		n /= 10;
	} while (i < a.size() || i < b.size() || n != 0);
	return ret;
}

string gop(const string& a, int n) {
	string ret;
	int num = 0;
	int i = 0;
	do {
		if (i < a.size())
			num += (a[i] - '0') * 2;
		i += 1;
		ret.push_back(num % 10 + '0');
		num /= 10;
	} while (i < a.size() || num != 0);

	return ret;
}

void tiling() {
	cache[0] = to_string(0);
	cache[1] = to_string(1);
	cache[2] = to_string(3);
	for (int i = 3; i <= 250; ++i) {
		cache[i] = sum(cache[i - 1], gop(cache[i - 2],2));
	}

	for (int i = 3; i <= 250; ++i) {
		int len = cache[i].size();
		for (int j = 0; j < len/2; ++j) {
			swap(cache[i][j], cache[i][len-1-j]);
		}
	}

}
int main(void) {
	int T;
	cin >> T;
	tiling();
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N;
		cout << '#' << tc << ' ' << cache[N] << '\n';
	}
	return 0;
}