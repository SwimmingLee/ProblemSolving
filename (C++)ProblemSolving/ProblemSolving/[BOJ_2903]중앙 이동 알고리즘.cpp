#include <iostream>
using namespace std;

int main(void) {
	int step;
	int width = 2;
	cin >> step;
	while (step--) {
		width = width + (width - 1);
	}
	cout << width * width << '\n';
	return 0;
}