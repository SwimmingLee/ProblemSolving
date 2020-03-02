#include <iostream>
using namespace std;
int board_sz;
int LDia_chk[30];
int RDia_chk[30];
int Row_chk[15];
int Col_chk[15];

int nqueen(int y) {
	int ans = 0;

	if (y == board_sz - 1) return 1;
	int ny = y + 1;

	for (int nx = 0; nx < board_sz; nx++) {
		if (LDia_chk[nx + ny] || RDia_chk[board_sz - ny + nx - 1] || Row_chk[ny] || Col_chk[nx]) continue;
		LDia_chk[nx + ny] = 1;
		RDia_chk[board_sz - ny + nx - 1] = 1;
		Row_chk[ny] = 1;
		Col_chk[nx] = 1;
		ans += nqueen(ny);
		LDia_chk[nx + ny] = 0;
		RDia_chk[board_sz - ny + nx - 1] = 0;
		Row_chk[ny] = 0;
		Col_chk[nx] = 0;
	}
	return ans;
} // nqueen(0, 0, 0, 0, 0)

int main(void) {
	cin >> board_sz;
	cout << nqueen(-1) << endl;
	return 0;
}