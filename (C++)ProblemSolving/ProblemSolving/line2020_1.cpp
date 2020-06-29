#include <string>
#include <iostream>
#include <vector>

using namespace std;
bool isOpening(const char c) {
	if (c == '(' || c == '{' || c == '[' || c == '<') return true;
	else return false;
}
bool isClosing(const char c) {
	if (c == ')' || c == '}' || c == ']' || c == '>') return true;
	else return false;
}
bool isColseOk(const vector<char>& st, const char c) {
	if (st.empty()) return false;
	if (c == '}' && st.back() == '{') return true;
	else if (c == ')' && st.back() == '(') return true;
	else if (c == ']' && st.back() == '[') return true;
	else if (c == '>' && st.back() == '<') return true;
	else return false;
}
int solution(string inputString) {
	int answer = 0;
	vector<char> st;
	for (char c : inputString) {
		if (isOpening(c)) {
			st.push_back(c);
		}
		else if (isClosing(c)) {
			if (isColseOk(st, c)) {
				answer += 1;
				st.pop_back();
			}
			else {
				answer = -1;
				break;
			}
		}
	}
	if (!st.empty()) answer = -1;

	return answer;
}

int main(void) {
	string inputString;
	inputString = "Hello, world!";
	inputString = "line [plus]";
	inputString = "if (Count of egg is 4.) {Buy milk.}";
	inputString = ">_<";
	cout << solution(inputString) << endl;
}