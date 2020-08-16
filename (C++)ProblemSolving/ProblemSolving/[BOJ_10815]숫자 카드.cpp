#include <iostream>
#include <algorithm>
using namespace std;

int N;
int M;
int card[500000];

bool bsearch(int var) {
	int start, mid, end;
	start = 0;
	end = N - 1;
	while (start <= end) {
		mid = (start + end) / 2;
		if (card[mid] == var) return true;

		if (card[mid] < var) {
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	return false;
}
int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> card[i];
	}
	sort(card, card + N);
	cin >> M;
	int var;
	for (int i = 0; i < M; i++) {
		cin >> var;
		cout << bsearch(var) << ' ';
	}
	return 0;
}