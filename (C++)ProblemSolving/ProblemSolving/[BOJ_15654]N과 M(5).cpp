#include <iostream>
#include <algorithm>
using namespace std;

int seq[10];
int a[10];
bool bvisited[10];

void permu(int index, int n, int m)
{
	if (index == m)
	{
		for (int i = 0; i < m; ++i)
			cout << seq[a[i]] << ' ';
		cout << '\n';
	}
	for (int i = 0; i < n; ++i) {
		if (!bvisited[i]) {
			a[index] = i;
			bvisited[i] = true;
			permu(index + 1, n, m);
			bvisited[i] = false;
		}
	}
}//permu(0, n, m)


int main()
{
	int N, M;
	cin >> N >> M;

	int data;
	for (int i = 0; i < N; ++i) {
		cin >> data;
		seq[i] = data;
	}

	sort(seq, seq + N);
	
	permu(0, N, M);
}