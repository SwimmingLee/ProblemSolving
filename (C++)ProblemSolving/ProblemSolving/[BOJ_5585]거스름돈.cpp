#include <iostream>
using namespace std;

int money_block[] = { 500, 100, 50, 10, 5, 1 };
int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int money;
	cin >> money;
	
	money = 1000 - money;
	int answer = 0;
	for (int i = 0; i < 6; i++) {
		answer += money / money_block[i];
		money %= money_block[i];
	}

	cout << answer;
}