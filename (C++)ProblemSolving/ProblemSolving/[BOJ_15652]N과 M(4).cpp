#include <iostream>
using namespace std;

int a[10];


void overcomb(int index, int start, int n, int m)
{
	if (index == m)
	{
		for (int i = 0; i < m; ++i)
			cout << a[i] << ' ';
		cout << '\n';
		return;
	}
	for (int i = start; i <= n; ++i)
	{
		a[index] = i;
		overcomb(index + 1, i, n, m);
	}
}//overcomb(0, 1, n, m);

int cnt[10];
void overcomb2(int index, int selected, int n, int m)
{
	if (selected == m) {
		for (int i = 0; i < n; ++i){
			for (int j = 1; j <= cnt[i]; ++j)
				cout << i + 1 << ' ';
		}
		cout << '\n';
		return;
	}
	if (index >= n) return;
	for (int i = m - selected; i >= 1; i--) {
		cnt[index] = i;
		overcomb2(index + 1, selected + i, n, m);
	}
	cnt[index] = 0;
	overcomb2(index + 1, selected, n, m);
}
int main()
{
	int N, M;
	cin >> N >> M;

	overcomb(0, 1, N, M);
	overcomb2(0, 0, N, M);
	return 0;
}