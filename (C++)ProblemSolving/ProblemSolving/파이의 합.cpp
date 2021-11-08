#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define MAX_NODE	1000000

//bool isPrime[MAX_NODE + 1];
int phi[MAX_NODE + 1];
long long psum[MAX_NODE + 1];
//vector<int> prime;
void eratosthenes() {
	for (int i = 2; i <= MAX_NODE; ++i)
		phi[i] = i;

	phi[0] = 0;
	phi[1] = 1;
	for (int i = 2; i <= MAX_NODE; ++i) {
		if (phi[i] == i) {
			for (int j = i; j <= MAX_NODE; j += i) {
				phi[j] /= i;
				phi[j] *= (i - 1);
			}
		}
	}

	for (int i = 1; i <= MAX_NODE; ++i) {
		psum[i] = psum[i - 1] + phi[i];
	}

}

//void calcPhi() {
//	phi[1] = 1;
//	
//	for (int i = 2; i <= MAX_NODE; ++i) {
//		if (isPrime[i]) continue;
//
//		int n = i;
//		for (int p: prime) {
//			int cnt = 0;
//			while ((n % p) == 0) {
//				n /= p;
//				cnt++;
//			}
//
//			if (cnt) {
//				phi[i] = pow(p, cnt) - pow(p, cnt - 1);
//				phi[i] *= phi[n];
//				break;
//			}
//		}
//	}
//	for (int i = 1; i <= MAX_NODE; ++i) {
//		psum[i] = psum[i - 1] + phi[i];
//	}
//}

int main(void) {
	int T;
	cin >> T;
	eratosthenes();
	//calcPhi();
	for (int tc = 1; tc <= T; ++tc) {
		int a, b;
		cin >> a >> b;
		long long answer = 0;
		answer = psum[b] - psum[a-1];
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}