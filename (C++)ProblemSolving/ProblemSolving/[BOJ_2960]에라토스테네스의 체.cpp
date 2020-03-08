#include <iostream>
using namespace std;

#define MAX_PRIME	1000
unsigned int prime[MAX_PRIME/32 + 1];

int main(void) {
	int n, k;
	cin >> n >> k;

	int cnt = 0;
	int ans = 0;
	for (int i = 2; i <= n; i++) {
		if (!(prime[i / 32] & (1 << (i % 32)))) {
			if (++cnt == k) {
				ans = i;
				break;
			}
			for (int j = i * i; j <= n; j+= i) {
				if (!(prime[j / 32] & (1 << (j % 32)))) {
					prime[j / 32] |= (1 << (j % 32));
					if (++cnt == k) {
						ans = j;
						break;
					}

				}
			}
			if (ans != 0) break;
		}
	}
	cout << ans << '\n';
}