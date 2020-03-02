#include <iostream>
using namespace std;

int a[10];
void overpermu(int index, int n, int m)
{
	if (index == m) {
		for (int i = 0; i < m; ++i)
			cout << a[i] << ' ';
		cout << '\n';
		return;
	}
	for (int i = 1; i <= n; ++i)
	{
		a[index] = i;
		overpermu(index + 1, n, m);
	}
}//overpermu(0, n, m)

int main()
{
	int N, M;
	cin >> N >> M;

	overpermu(0, N, M);

	return 0;
}