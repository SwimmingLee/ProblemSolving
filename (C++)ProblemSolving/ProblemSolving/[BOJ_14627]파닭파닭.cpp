#include <iostream>
using namespace std;

#define PAR_NUM		1000001

int par[PAR_NUM];
int S, C;
int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	int mini = -1;
	cin >> S >> C;
	for (int i = 0; i < S; i++) {
		cin >> par[i];
		if (mini == -1 || mini < par[i]) {
			mini = par[i];
		}
	}
	
	long long answer = -1;
	int start = 1, end = mini, mid;
	while (start <= end) {
		mid = (start + end) / 2;
		int par_part = 0;
		long long par_rest = 0;
		for (int i = 0; i < S; i++) {
			par_part += par[i] / mid;
			par_rest += par[i] % mid;
		}
		if (par_part >= C) {
			par_rest += (par_part - C) * (long long)mid;
			start = mid + 1;
			if (answer == -1 || par_rest < answer) {
				answer = par_rest;
			}
		}
		else {
			end = mid - 1;
		}
	}

	cout << answer;
}