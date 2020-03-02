#include <iostream>
using namespace std;

int a[10];
bool bvisited[10];

void permu(int index, int n, int m)
{
	if (index == m) {
		for (int i = 0; i < m; ++i)
			cout << a[i] << ' ';
		cout << endl;
		return;
	}
	for (int i = 1; i <= n; ++i) {
		if (!bvisited[i]) {
			a[index] = i;
			bvisited[i] = true;
			permu(index + 1, n, m);
			bvisited[i] = false;
		}
	}
}


int main()
{
	int N, M;

	cin >> N >> M;

	permu(0, N, M);
	return 0;
}