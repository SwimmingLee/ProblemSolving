#include <iostream>
#include <string>
using namespace std;

string solve(int n) {
	if (n == 1) return string("666");

	string res;
	int cur, prev = 0, decimal;
	int add_dec;
	cur = decimal = 1;
	while (cur < n) {
		int tmp = decimal;
		add_dec = 1;

		while (tmp--) add_dec *= 10;
		prev = cur;
		cur = cur * 8 + add_dec;
		decimal++;
	}
	cout << "cur" << cur << endl;
	cout << prev << endl;
	n -= prev;
	if (n <= prev * 5) {
		int add = n % prev == 0 ? 0 : 1;
		int x = (n / prev) + add;
		res.push_back(x + '0');
		return res + solve(n % prev + 1);
	}
	else if (n <= prev * 5 + add_dec) {
		n -= prev * 5 + 1;
		cout <<"d" << n << endl;
		int div = 1;
		for (int i = 1; i < decimal; i++) {
			int t = (n / div) % 10;
			cout << "t" << t << endl;
			res.push_back(t + '0');
			div *= 10;
		}
		reverse(res.begin(), res.end());
		return string("666") + res;
	}
	else {
		cout << "S";
		int add = (n - add_dec) % prev == 0 ? 1 : 2;
		int x = ((n - add_dec)/ prev) + add;
		res.push_back(x + '0');
		return res + solve(n % prev + 1);
	}
	
}
int main(void) {
	int n;
	cin >> n;
	
	cout << solve(n);

	return 0;
}