#include <iostream>
#include <algorithm>
using namespace std;

int anum[10];
int acnt[10];
int a[10];

void permu(int index, int n, int m)
{
	if (index == m) {
		for (int i = 0; i < m; ++i)
			cout << anum[a[i]] << ' ';
		cout << '\n';
		return;
	}
	for (int i = 0; i < n; ++i) {
		if (!acnt[i]) continue;
		a[index] = i;
		permu(index + 1, n, m);
	}
}

int main()
{
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; ++i)
		cin >> anum[i];

	sort(anum, anum + n);

	acnt[0] = 1;
	for (int i = 1; i < n; ++i) {
		if (anum[i] != anum[i - 1]) {
			acnt[i] = 1;
		}
	}

	permu(0, n, m);
	return 0;
}