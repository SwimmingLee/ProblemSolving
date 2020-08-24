#include <iostream>
#include <cmath>
using namespace std;

int n_operand;
char operand[10];
int answer[10];
bool chk[10];
long long maxium_num = 0;
long long minium_num = -1;

bool isOk(int depth, int num) {
	if (depth == 0) {
		return true;
	}
	else if (operand[depth-1] == '<' && answer[depth - 1] < num) {
		return true;
	}
	else if (operand[depth-1] == '>' && answer[depth - 1] > num) {
		return true;
	}
	return false;
}

void solve(int depth) {
	if (depth > n_operand) {
		long long num = 0;
		for (int i = 0; i <= n_operand; i++) {
			num = num * 10 + answer[i];
		}
		//cout << num << endl;
		if (maxium_num < num) {
			maxium_num = num;
		}
		if (minium_num == -1 || minium_num > num) {
			minium_num = num;
		}
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (!chk[i] && isOk(depth, i)) {
			chk[i] = true;
			answer[depth] = i;
			solve(depth + 1);
			chk[i] = false;
		}
	}
}//solve(0)
int main(void) {
	cin >> n_operand;
	for (int i = 0; i < n_operand; i++) {
		cin >> operand[i];
	}
	solve(0);
	int com = pow(10, n_operand);
	if (maxium_num < com) {
		cout << 0;
	}
	cout << maxium_num << '\n';
	if (minium_num < com) {
		cout << 0;
	}
	cout << minium_num << '\n';
	return 0;
}