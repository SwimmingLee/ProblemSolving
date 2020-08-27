#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(string s) {
	int answer = s.size();
	for (int i = 1; i <= s.size(); i++) {
		string stand_s = s.substr(0, i);
		string res_s;
		int cnt = 1;
		for (int j = i; ; j += i) {
			if (j > s.size()) {
				if (cnt != 1) {
					res_s += to_string(cnt) + stand_s + s.substr(j-i);
				}
				else {
					res_s += s.substr(j-i);
				}
				break;
			}

			string cmp_s = s.substr(j, i);
			if (stand_s == cmp_s) {
				cnt++;
			}
			else {
				if (cnt != 1) {
					res_s += to_string(cnt) + stand_s;
					cnt = 1;
				}
				else {
					res_s += stand_s;
				}
				stand_s = cmp_s;
			}

			
		}
		//cout << "[ " << i  << "] " << res_s << endl;
		int tmp = res_s.size();
		if (tmp < answer) answer = tmp;
	}
	return answer;
}