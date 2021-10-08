#include <iostream>
#include <string>
using namespace std;

int n;
int tree[1001][2];
char treeOp[1001];

string op = "-+*/";
void input() {
	cin.ignore();
	string s;
	int no;
	for (int i = 0; i < n; ++i) {
		getline(cin, s);
		
		bool isOp = false;
		if (op.find(s) != string::npos)
			isOp = true;
	
		if (isOp) {
			int left, right;
			cin >> left >> right;
			tree[no][0] = left;
			tree[no][1] = right;
			treeOp[no] = s[0];
		}
		else {
			treeOp[no] = 0;
		}
	}
}
double verifyTree(int i) {
	if (treeOp[i] == 0) {
		
	}
	else {
		double ret;
		double leftVal, rightVal;
		leftVal = verifyTree(tree[i][0]);
		rightVal = verifyTree(tree[i][1]);

		if (treeOp[i] == '+')
			ret = leftVal + rightVal;
		else if (treeOp[i] == '-')
			ret = leftVal - rightVal;
		else if (treeOp[i] == '*')
			ret = leftVal * rightVal;
		else /*(treeOp[i] == '/')*/
			ret = leftVal / rightVal;

		return ret;
	}
}
int main(void) {
	int TC = 10;
	for (int test_case = 1; test_case <= TC; ++test_case) {
		cin >> n;
		input();
		cout << '#' << test_case << ' ';
		verifyTree(1);
	}
}