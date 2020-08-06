//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//
//vector<int> preprocess(string& p) {
//	int p_sz = p.length();
//	vector<int> fail(p_sz, 0);
//	int j = 0;
//	for (int i = 1; i < p_sz; i++) {
//		while (j > 0 && p[i] != p[j]) j = fail[j - 1];
//		if (p[i] == p[j]) {
//			fail[i] = j + 1;
//			j += 1;
//		}
//		else {
//			fail[i] = 0;
//		}
//	}
//}
//
//int match(string& s, string& p) {
//	vector<int> matchArr;
//	vector<int> fail = preprocess(p);
//
//	int s_sz = s.length();
//	int p_sz = p.length();
//
//	int j = 0;
//	for (int i = 0; i < s_sz; i++) {
//		while (j > 0 && s[i] != p[j]) j = fail[j - 1];
//		if (s[i] == p[j]) {
//			j += 1;
//			if (j == p_sz) {
//				matchArr.push_back(i - j + 2);
//				j = fail[j - 1];
//			}
//		}
//	}
//}
//
//int main(void) {
//
//	return 0;
//}