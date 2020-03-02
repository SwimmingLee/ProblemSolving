#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int anum[10];
int acnt[10];
int a[10];

void comb(int index, int start, int n, int m)
{
	if (index == m) {
		for (int i = 0; i < m; ++i)
			cout << anum[a[i]] << ' ';
		cout << '\n';
		return;/**/
	}
	for (int i = start; i < n; ++i) {
		if (acnt[i] > 0) {
			a[index] = i;
			comb(index+1, i, n, m);
		}
	}
}//comb(0, 0, n, m)


int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> anum[i];
	sort(anum, anum + n);

	acnt[0] = 1;
	for (int i = 1; i < n; ++i) 
		if (anum[i] != anum[i - 1]) 
			acnt[i] = 1;

	comb(0, 0, n, m);

	return 0;
}