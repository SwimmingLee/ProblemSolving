#include <iostream>
#include <algorithm>
using namespace std;

int seqdata[10];
int a[10];

void comb(int index, int selected, int n, int m)
{
	if (selected == m) {
		for(int i=0; i<m; ++i)
			cout << seqdata[a[i]-1] << ' ';
		cout << '\n';
		return;
	}
	if (index > n) return;
	a[selected] = index;
	comb(index + 1, selected + 1, n, m);
	a[selected] = 0;
	comb(index + 1, selected, n, m);
}


void comb2(int index, int start, int n, int m)
{
	if (index == m){
		//���
		for (int i = 0; i < m; ++i)
			cout << seqdata[a[i]] << ' ';
		cout << '\n';
		return;
	}
	if (last >= n) return;
	for (int i = start; i < n; ++i){
		a[index] = i;/**/
		comb2(index+1, i+1, n, m);
	}
}//comb2(0, 0, n, m)

int main()
{
	int N, M;
	cin >> N >> M;

	int data;
	for (int i = 0; i < N; ++i) {
		cin >> data;
		seqdata[i] = data;
	}
	sort(seqdata, seqdata + N);

	//comb(1, 0, N, M);
	comb2(0, 0, N, M);
	return 0;
}