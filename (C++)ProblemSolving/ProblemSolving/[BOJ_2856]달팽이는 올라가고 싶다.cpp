#include <iostream>
using namespace std;

int main(void) {
	int a, b, v;
	cin >> a >> b >> v;
	int c = (v - b) % (a - b) ? 1 : 0;

	if (a == v) cout << 1;
	else cout << (v - b) / (a - b) + c;
	return 0;
}