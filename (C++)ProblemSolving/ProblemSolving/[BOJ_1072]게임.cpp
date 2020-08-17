#include <iostream>
using namespace std;

int X, Y;
int rate;
void solve() {
	int start, mid, end;
	start = 1;
	end = 1e9;

	int res = -1;
	while(start <= end) {
		mid = start + (end - start) / 2;
		
		int mid_rate = (double)(Y + mid) * 100 / (X + mid);
		if (mid_rate != rate) {
			end = mid - 1;
			if (res == -1 || res > mid)
				res = mid;
		}
		else {
			start = mid + 1;
		}
	}
	cout << res;
}
int main(void) {
	cin >> X >> Y;
	rate = (double)Y * 100 / X;
	//cout << rate << endl;
	solve();
	return 0;
}