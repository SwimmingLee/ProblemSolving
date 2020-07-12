#include <iostream>
using namespace std;

int n_shape;
int shape_len;
int shape[100][50];
int base_shape[2][50];

int n_same = 0;

bool issame() {
	for (int i = 0; i < shape_len; i++) {
		bool ok = true;
		for (int j = 0; j < shape_len; j++) {
			if (base_shape[0][(j+i)%shape_len] != shape[n_same][j]) {
				ok = false;
				break;
			}
		}
		if (ok) return true;
	}


	for (int i = 0; i < shape_len; i++) {
		bool ok = true;
		for (int j = 0; j < shape_len; j++) {
			if (base_shape[1][(j + i) % shape_len] != shape[n_same][j]) {
				ok = false;
				break;
			}
		}
		if (ok) return true;
	}

	return false;
}

int main(void) {
	cin >> shape_len;
	for (int i = 0; i < shape_len; i++) {
		int dir;
		cin >> dir;
		base_shape[0][i] = dir;
		base_shape[1][shape_len - 1 - i] = dir <= 2 ? dir + 2: (dir+2)%4;
	}
	cin >> n_shape;
	for (int i = 0; i < n_shape; i++) {
		for (int j = 0; j < shape_len; j++) {
			cin >> shape[n_same][j];
		}
		if (issame()) n_same++;
	}

	cout << n_same << '\n';
	for (int i = 0; i < n_same; i++) {
		for (int j = 0; j < shape_len; j++) {
			cout << shape[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}