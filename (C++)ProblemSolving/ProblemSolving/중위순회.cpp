#include <iostream>
#include <string>
using namespace std;

int n;
int tree[101][2];
int childCnt[101];
char treeAlpha[101];

void init() {
	for (int i = 0; i < n; ++i) {
		childCnt[i] = 0;
	}
}
void input() {
	cin.ignore();
	for (int i = 0; i < n; ++i) {
		string s;
		getline(cin, s, '\n');
		//cout << "[] " << i << s << endl;
		int progress = 0;
		int num = 0;
		int no = 0;
		for (char c : s) {
			if (c == ' ') {
				if (progress == 0) {
					no = num;
				}
				else if (progress != 1){
					tree[no][childCnt[no]++] = num;
				}
				progress++;
				num = 0;
			}
			else if (progress != 1) {
				num = num * 10 + c - '0';
			}
			else {
				treeAlpha[no] = c;
			}
		}
		if (num != 0 && progress != 1) {
			tree[no][childCnt[no]++] = num;
		}
	}
}

void inorder(int idx) {
	if (childCnt[idx] > 0) inorder(tree[idx][0]);
	cout << treeAlpha[idx];
	if (childCnt[idx] > 1) inorder(tree[idx][1]);
}

int main(void) {
	int TC = 10;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		cin >> n;
		init();
		input();
		cout << '#' << test_case << ' ';
		inorder(1);
		cout << '\n';
	}
	
	return 0;
}