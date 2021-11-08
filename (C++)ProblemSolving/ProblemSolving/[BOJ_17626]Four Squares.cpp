#include <iostream>
using namespace std;

int cache[50001];
// 탑 다운으로 하면 터진다
// 바텀 업으로 해야지만 된다. 

int largrang(int n) {
	//if (n < 0) return 987987987;
	for (int i = 0; i <= 50000; ++i)
		cache[i] = 987987987;

	cache[0] = 0;
	cache[1] = 1;
	for (int j = 0; j <= 50000; ++j) {
		for (int i = 1; j + i * i <= 50000; ++i) {
			cache[j + i*i] = min(cache[j + i*i], cache[j] + 1);
		}
	}

	return cache[n];
}

int main(void) {
	int N;
	cin >> N;
	
	int answer = largrang(N);
	cout << answer << endl;
	return 0;
}