#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(string s) {
	int answer = s.size();
	for (int i = 1; i <= s.size() / 2; i++) {
		string res_str = "";
		string stand_str = s.substr(0, i);
		int cnt = 1;
		for (int j = i; ; j += i) {
			string cmp_str;
			if (j < s.size()) {
				cmp_str = s.substr(j, i);
				if (stand_str == cmp_str) {
					cnt++;
					continue;
				}
			}
			if (cnt > 1) {
				res_str += to_string(cnt);
				cnt = 1;
			}
			res_str += stand_str;
			stand_str = cmp_str;
			if (j >= s.size()) break;
		}

		int tmp = res_str.size();
		if (tmp < answer) answer = tmp;
	}
	return answer;
}