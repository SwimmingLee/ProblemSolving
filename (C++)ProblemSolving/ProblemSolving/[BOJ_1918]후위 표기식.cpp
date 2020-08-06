#include <iostream>
#include <vector>
#include <string>

using namespace std;

int isSign(char c) {
	if (c == '(') return 1;
	else if (c == ')') return 1;
	else if (c == '+') return 3;
	else if (c == '-') return 3;
	else if (c == '/') return 5;
	else if (c == '*') return 5;

	return false;
}

void solve(string& s) {
	string answer;
	vector<string> operand;
	vector<char> sign;

	for (int i = 0; i < s.size(); i++) {
		char c = s[i];
		if (isSign(c) > 0) {
			if (sign.empty() || c == '(') {
				sign.push_back(c);
				continue;
			}
			if (c == ')') {
				while (!sign.empty() && sign.back() != '(') {
					string a, b;
					b = operand.back(); operand.pop_back();
					a = operand.back(); operand.pop_back();
					char op = sign.back(); sign.pop_back();
					string t = a + b;
					t.push_back(op);

					operand.push_back(t);
				}
				sign.pop_back();
			}
			else {
				while (!sign.empty() && isSign(c) <= isSign(sign.back())) {
					string a, b;
					b = operand.back(); operand.pop_back();
					a = operand.back(); operand.pop_back();
					string t = a + b;
					char op = sign.back(); sign.pop_back();
					t.push_back(op);
					operand.push_back(t);
				}
				sign.push_back(c);
			}
		}
		else {
			string tmp;
			tmp.push_back(c);
			operand.push_back(tmp);
		}
	}
	
	while (!sign.empty()) {
		string a, b;
		b = operand.back(); operand.pop_back();
		a = operand.back(); operand.pop_back();
		char op = sign.back(); sign.pop_back();
		string t = a + b;
		t.push_back(op);
		operand.push_back(t);
	}

	cout << operand.back() << '\n';
}
int main(void) {
	string s;
	cin >> s;
	solve(s);
	return 0;
}