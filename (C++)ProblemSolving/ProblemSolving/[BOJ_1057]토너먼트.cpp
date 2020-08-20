#include <iostream>
using namespace std;

int main(void) {
	int n, u, v;
	cin >> n >> u >> v;
	int round = 0;
	while (u != v) {
		u = (u + 1) / 2;
		v = (v + 1) / 2;
		round++;
	}
	cout << round << endl;
	return 0;
}