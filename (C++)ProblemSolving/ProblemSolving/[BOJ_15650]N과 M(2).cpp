#include <iostream>
using namespace std;

int a[10];
bool bvisited[10];

void comb(int index, int start, int n, int m)
{
	if (index == m){
		for (int i = 0; i < m; ++i)
			cout << a[i] << ' ';
		cout << '\n';
		return;
	}
	if (start > n) return;
	for (int i = start; i <= n; ++i) {
		a[index] = i;
		comb(index + 1, i + 1, n, m);
	}
}

void comb2(int index, int selected, int n, int m)
{
	if (selected == m) {
		for (int i = 0; i < m; ++i)
			cout << a[i] << ' ';
		cout << '\n';
		return;
	}
	if (index > n) return;
	a[selected] = index;
	comb2(index + 1, selected + 1, n, m);
	a[selected] = 0;
	comb2(index + 1, selected, n, m);
}//comb2(1, 0, n, m)

int main()
{
	int N, M;
	cin >> N >> M;

	comb(0, 1, N, M);
	comb2(1, 0, N, M);
	return 0;
}