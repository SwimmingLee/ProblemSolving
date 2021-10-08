#include <iostream>
#include <algorithm>
using namespace std;

struct Magnetic {
	int pos;
	int mass;
};

int n;
Magnetic material[10];

void input() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> material[i].pos;
	}
	for (int i = 0; i < n; ++i) {
		cin >> material[i].mass;
	}
}

long double magenticPower(int m, long double d) {
	return (long double)m / (d * d);
}

long double balancePos(long double left, long double right) {
	long double mid;
	long double leftPower;
	long double rightPower;

	mid = -1;
	leftPower = 10;
	rightPower = 1;
	while (abs(leftPower - rightPower) > 1e-13) { 
		/*12로 하면 틀림- 오차가 있으니까 맞는다... 
		floating point는 오차가 있는데 그래서 이걸 줄이기 위해서는 더 줄어야 한다. */
		mid = (long double)(left + right) / 2;
		leftPower = rightPower = 0;
		for (int i = 0; i < n; ++i) {
			if (material[i].pos < mid) {
				leftPower += magenticPower(material[i].mass, (long double)material[i].pos - mid);
			}
			else {
				rightPower += magenticPower(material[i].mass, (long double)material[i].pos - mid);
			}
		}

		if (leftPower < rightPower) {
			right = mid;
		}
		else {
			left = mid;
		}
	}
	return mid;
}

int main(void) {
	cout << fixed;
	cout.precision(10);
	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		input();
		sort(material, material + n, [](const Magnetic& a, const Magnetic& b) { return a.pos < b.pos; });
		cout << '#' << test_case << ' '; 
		for (int i = 1; i < n; ++i) {
			long double answer = balancePos(material[i - 1].pos, material[i].pos); /*long double!!!*/
			cout << answer << ' ';
		}
		cout << '\n';
	}
	return 0;
}