#include <iostream>
using namespace std;
#define MAX_NUM 20*50+1

bool chk[MAX_NUM];

int GetCntNumber(int num_roma) {
	int ans = 0;
	for (int i = 0; i <= num_roma; i++) {
		for (int j = 0; j + i <= num_roma; j++) {
			for (int k = 0; k +j +i <= num_roma; k++) {
				int l = num_roma - (i + j + k);
				int num = i + j * 5 + k * 10 + l * 50;
				if (!chk[num]) {
					chk[num] = true;
					ans += 1;
				}
			}
		}
	}
	
	return ans;
}

int main(void) {
	int num_roma;
	cin >> num_roma;
	int ans = GetCntNumber(num_roma);
	cout << ans << '\n';
	return 0;
}