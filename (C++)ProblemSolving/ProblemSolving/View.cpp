
#include <iostream>
using namespace std;

int width;
int building[1004];
int max(int a, int b) {
	return a > b ? a : b;
}
void init(int width) {
	for (int i = 0; i < width + 4; ++i) {
		building[i] = 0;
	}
}
int main(void) {
	int T;
	T = 10;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int answer = 0;
		cin >> width;
		init(width);
		for (int i = 2; i < width + 2; ++i) {
			//cout << "! " << i << " " << width << endl;
			cin >> building[i];
		}
		for (int i = 2; i < width + 2; ++i) {
			int left, right, view;

			left = max(building[i - 1], building[i - 2]);
			right = max(building[i + 1], building[i + 2]);
			view = max(left, right);

			int diff = building[i] - view;

			answer += (diff > 0 ? diff: 0);
		}

		cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}