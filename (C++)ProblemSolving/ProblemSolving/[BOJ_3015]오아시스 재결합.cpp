#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int num_line;
vector<int> line;

long long GetMeetPeople() {
	long long ans = 0;
	stack<pair<int, int>> s;
	for (int i = 0; i < num_line; i++) {
		pair<int, int> p = { line[i], 1 };
		while (!s.empty()) {
			if (s.top().first <= line[i]) {
				ans += (long long)s.top().second;
				if (s.top().first == line[i]) {
					p.second += s.top().second;
				}
				s.pop(); 
			}
			else {
				break;
			}
		}
		if (!s.empty()) ans += 1LL;
		s.push(p);
	}
	return ans;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> num_line;
	line.resize(num_line);
	for (int i = 0; i < num_line; i++)
		cin >> line[i];
	cout << GetMeetPeople() << '\n';
	return 0;
}