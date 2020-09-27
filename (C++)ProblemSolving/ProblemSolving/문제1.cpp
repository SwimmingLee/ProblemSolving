#include <string>
#include <vector>

using namespace std;

string solution(string m, string k) {
	string answer = "";
	int key_idx = 0;
	for (int i = 0; i < m.size(); i++) {
		if (m[i] == k[key_idx]) {
			key_idx++;
		}
		else {
			answer.push_back(m[i]);
		}
	}
	return 0;
}