#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int a[10];
int acnt[10];
int anum[10];


void comb(int index, int start, int n, int m)
{
	if (index == m) {
		for (int i = 0; i < m; ++i)
			cout << anum[a[i]] << ' ';
		cout << '\n';
	}
	for (int i = start; i < n; ++i) {
		if (acnt[i] > 0) {
			acnt[i] -= 1;
			a[index] = i;
			comb(index + 1, i, n, m);
			acnt[i] += 1;
		}
	}
}//comb(0, 0, n, m);
int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> anum[i];

	sort(anum, anum + n);
	acnt[0] = 1;
	for (int i = 0; i < n; ++i) {
		if (anum[i] != anum[i - 1])
			acnt[i] = 1;
		else {
			acnt[i] = acnt[i - 1] + 1;
			acnt[i - 1] = 0;
		}
	}
		
		
	comb(0, 0, n, m);

	return 0;
}