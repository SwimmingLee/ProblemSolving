#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_STICK 100000

int num_stick;
int stick[MAX_STICK];

long long GetMaxRectangle() {
	stack<int> st;
	long long area = 0;
	st.push(0);
	for (int i = 1; i < num_stick; i++) {
		while (!st.empty() && stick[st.top()] > stick[i]) {
			int height = stick[st.top()];
			st.pop();	
			int right = i;
			int left = st.empty() ? 0 : st.top() + 1;
			area = max(area, (long long)(right - left) * height);
		}
		st.push(i);
	}
	while (!st.empty()) {
		int height = stick[st.top()];
		st.pop();
		int right = num_stick;
		int left = st.empty() ? 0 : st.top() + 1;
		area = max(area, (long long)(right - left) * height);
	}
	return area;
}
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while (true) {
		cin >> num_stick;
		if (num_stick == 0) break;
		for (int i = 0; i < num_stick; i++)
			cin >> stick[i];
		cout << GetMaxRectangle() << '\n';
	}

	return 0;
}