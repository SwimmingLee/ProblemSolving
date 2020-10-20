#include <iostream>
using namespace std;

int main(void) {
	int a = 1 << 31;
	for (int i = 0; i < 10; i++) {
		cout << a - i << endl;
	}
	return 0;
}