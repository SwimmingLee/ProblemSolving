#include <string>
#include <vector>
#include <algorithm>
#define INT_MAX 210000000
using namespace std;
int solution(vector<int> stones, int k) {
	int answer = INT_MAX;
	vector<int> st;
	stones.push_back(INT_MAX);
	for (int i = 0; i < stones.size(); i++) {
		while (!st.empty() && stones[st.back()] <= stones[i]) {
			int right = i;
			int cur = st.back(); st.pop_back();
			int left = st.empty() ? -1 : st.back();

			if (right - left - 1 >= k) {
				answer = min(answer, stones[cur]);
			}
		}
		st.push_back(i);
	}

	cout << endl;
	return answer;
}