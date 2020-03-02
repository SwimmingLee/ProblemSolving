#include <iostream>
#include <algorithm>
using namespace std;

int a[10];
int seqdata[10];

void overpermu(int index, int n, int m)
{
	if (index == m) {
		//���
		for (int i = 0; i < m; ++i)
			cout << seqdata[a[i]] << ' ';
		cout << '\n';
		return;
	}
	for (int i = 0; i < n; ++i){
		a[index] = i;
		overpermu(index + 1, n, m);
	}
}

int main()
{
	int N, M;
	cin >> N >> M;
	int data;
	for (int i = 0; i < N; ++i){
		cin >> data;
		seqdata[i] = data;
	}
	sort(seqdata, seqdata + N);
	overpermu(0, N, M);
	return 0;
}