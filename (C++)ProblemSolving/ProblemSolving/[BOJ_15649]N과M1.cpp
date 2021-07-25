#include <iostream>
using namespace std;

int N, M;
int permu_arr[10];
void permu(int idx, int visited, int *arr) {
;	if (idx >= M) {
		for (int i = 0; i < M; i++) {
			cout << arr[i] << ' ';
		}
		cout << '\n';
		return;
	}
	for (int i = 1; i <= N; i++) {
		if (visited & (1 << i)) continue;
		arr[idx] = i;
		permu(idx + 1, visited | (1 << i), arr);
	}
}

int main(void) {
	cin >> N >> M;
	permu(0, 0, permu_arr);
	return 0;
}