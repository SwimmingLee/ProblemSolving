#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


vector<string> s;
vector<pair<string, int>> sorted_s;
int M, N;


int bsearch(string& s) {
	int start, mid, end;
	start = 0;
	end = N - 1;
	while (start <= end) {
		mid = (start + end) / 2;

		if (sorted_s[mid].first == s) return sorted_s[mid].second;

		if (sorted_s[mid].first < s) {
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	return -1;
}

int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> N >> M;
	s.resize(N);
	sorted_s.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> s[i];
		sorted_s[i] = { s[i], i };
	}
	sort(sorted_s.begin(), sorted_s.end());
	for (int i = 0; i < M; i++) {
		string in;
		cin >> in;
		if ('0' <= in[0] && in[0] <= '9') {
			int num = 0;
			for (int j = 0; j < in.size(); j++) {
				num = num * 10 + (in[j] - '0');
			}
			cout << s[num - 1] << endl;
		}
		else {
			cout << bsearch(in) + 1 << endl;
		}

	}
	return 0;
}