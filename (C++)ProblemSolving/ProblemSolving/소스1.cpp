//#include <string>
//#include <vector>
//#include <deque>
//#include <iostream>
//using namespace std;
//
//int PLUS, MINU, MULT;
//
//bool compare(char a, char b) {
//	if (a == '+') {
//		a = PLUS;
//	}
//	else if (a == '-') {
//		a = MINU;
//	}
//	else {
//		a = MULT;
//	}
//
//	if (b == '+') {
//		b = PLUS;
//	}
//	else if (b == '-') {
//		b = MINU;
//	}
//	else {
//		b = MULT;
//	}
//
//	return a < b;
//
//}
//long long covert(string expression) {
//	long long num = 0;
//	vector<long long> st;
//	vector<char> op_st;
//
//	for (int i = 0; i < expression.size(); i++) {
//		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
//			st.push_back(num);
//			num = 0;
//			if (op_st.empty()) {
//				op_st.push_back(expression[i]);
//			}
//			else if (compare(op_st.back(), expression[i])) {
//				op_st.push_back(expression[i]);
//			}
//			else {
//				while (!op_st.empty() && !compare(op_st.back(), expression[i])) {
//					long long op_result;
//					long long oprand_two;
//					long long oprand_one;
//					vector<long long> tmp_st;
//					vector<char> tmp_op_st;
//					char cur_op = op_st.back(); op_st.pop_back();
//					while (!op_st.empty() && op_st.back() == cur_op) {
//						long long tmp = st.back(); st.pop_back();
//						tmp_st.push_back(tmp);
//
//						tmp_op_st.push_back(cur_op);
//						cur_op = op_st.back(); op_st.pop_back();
//					}
//
//					oprand_two = st.back(); st.pop_back();
//					oprand_one = st.back(); st.pop_back();
//
//					char op = cur_op;
//					if (op == '+') {
//						op_result = oprand_one + oprand_two;
//					}
//					else if (op == '-') {
//						op_result = oprand_one - oprand_two;
//					}
//					else if (op == '*') {
//						op_result = oprand_one * oprand_two;
//					}
//
//					st.push_back(op_result);
//					while (!tmp_st.empty()) {
//						long long tmp = tmp_st.back(); tmp_st.pop_back();
//						st.push_back(tmp);
//					}
//					while (!tmp_op_st.empty()) {
//						char tmp = tmp_op_st.back(); tmp_op_st.pop_back();
//						op_st.push_back(tmp);
//					}
//				}
//				op_st.push_back(expression[i]);
//			}
//		}
//		else {
//			num = num * 10 + expression[i] - '0';
//		}
//	}
//	st.push_back(num);
//	while (!op_st.empty()) {
//		long long op_result;
//		long long oprand_two;
//		long long oprand_one;
//		vector<long long> tmp_st;
//		vector<char> tmp_op_st;
//		char cur_op = op_st.back(); op_st.pop_back();
//		while (!op_st.empty() && op_st.back() == cur_op) {
//			long long tmp = st.back(); st.pop_back();
//			tmp_st.push_back(tmp);
//
//			tmp_op_st.push_back(cur_op);
//			cur_op = op_st.back(); op_st.pop_back();
//		}
//
//		oprand_two = st.back(); st.pop_back();
//		oprand_one = st.back(); st.pop_back();
//
//		char op = cur_op;
//		if (op == '+') {
//			op_result = oprand_one + oprand_two;
//		}
//		else if (op == '-') {
//			op_result = oprand_one - oprand_two;
//		}
//		else if (op == '*') {
//			op_result = oprand_one * oprand_two;
//		}
//
//		st.push_back(op_result);
//		while (!tmp_st.empty()) {
//			long long tmp = tmp_st.back(); tmp_st.pop_back();
//			st.push_back(tmp);
//		}
//		while (!tmp_op_st.empty()) {
//			char tmp = tmp_op_st.back(); tmp_op_st.pop_back();
//			op_st.push_back(tmp);
//		}
//
//		cout << op_result << endl;
//	}
//	return st.back();
//}
//
//int arr[3];
//long long ans = 0;
//
//void dfs(string expression, int depth, int chk) {
//	if (depth == 3) {
//		PLUS = arr[0];
//		MINU = arr[1];
//		MULT = arr[2];
//
//		long long tmp = abs(covert(expression));
//		if (ans < tmp) {
//			ans = tmp;
//		}
//		return;
//	}
//	for (int i = 0; i < 3; i++) {
//		if (!(chk & (1 << i))) {
//			arr[depth] = i;
//			dfs(expression, depth + 1, chk | (1 << i));
//		}
//	}
//} // dfs(0, 0);
//long long solution(string expression) {
//	long long answer = 0;
//
//	dfs(expression, 0, 0);i
//	answer = ans;
//
//	return answer;
//}
//
////int main() {
////	string test1 = "100-200*300-500+20";//	60420
////	string test2 = "50*6-3*2";	//300
////
////	solution(test1);
////
////
////}