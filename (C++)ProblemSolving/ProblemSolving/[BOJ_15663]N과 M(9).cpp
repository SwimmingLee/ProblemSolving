#include <iostream>
#include <algorithm>
using namespace std;

int anum[10];
int cnt[10];
int a[10];


void permu(int index, int n, int m)
{
	if (index == m) {
		for (int i = 0; i < m; ++i)
			cout << anum[a[i]] << ' ';
		cout << '\n';
	}
	for (int i = 0; i < n; ++i) {
		if (cnt[i] > 0) {
			cnt[i] -= 1;
			a[index] = i;
			permu(index + 1, n, m);
			cnt[i] += 1;
		}
	}
}
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> anum[i];

	sort(anum, anum + n);

	cnt[0] = 1;
	for (int i = 1; i < n; ++i) {
		if (anum[i] != anum[i - 1]) {
			cnt[i] = 1;
		}
		else {
			cnt[i] = cnt[i - 1] + 1;
			cnt[i - 1] = 0;
		}
	}

	permu(0, n, m);

	return 0;
}