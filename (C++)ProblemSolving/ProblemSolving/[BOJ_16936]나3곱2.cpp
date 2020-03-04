#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int num;
vector<int> arr;
vector<int> ans;
vector<pair<int, int>> m;

int binary_search(int start, int end, int value) {
	while (start <= end) {
		int mid = (start + end) / 2;
		if (m[mid].first > value) 
			end = mid - 1;
		else if (m[mid].first < value)
			start = mid + 1;
		else 
			return mid;
	}
	return -1;
}

bool dfs(int here, int depth) {
	if (depth == num - 1) {
		for (int i = 0; i < num; i++) {
			cout << ans[i] << ' ';
		}
		cout << '\n';
		return true;
	};

	int next = here * 2;
	int next_idx;

	if ((next_idx = binary_search(0, m.size()-1, next)) >= 0 ) {
		if (m[next_idx].second > 0) {
			m[next_idx].second--;
			ans.push_back(next);
			if (dfs(next, depth + 1))
				return true;
			ans.pop_back();
			m[next_idx].second++;
		}
	}

	if (here % 3 != 0) return false;
	next = here / 3;
	if ((next_idx = binary_search(0, m.size() - 1, next)) >= 0) {
		if (m[next_idx].second > 0) {
			m[next_idx].second--;
			ans.push_back(next);
			if (dfs(next, depth + 1))
				return true;
			ans.pop_back();
			m[next_idx].second++;
		}
	}
	return false;
}
int main(void) {
	cin >> num;
	arr.resize(num);
	
	for (int i = 0; i < num; i++)
		cin >> arr[i];
	sort(arr.begin(), arr.end());
	int j = 0;
	m.push_back({arr[0], 1 });
	for (int i = 1; i < num; i++) {
		if (m[j].first == arr[i]) {
			m[j].second++;
		}
		else {
			m.push_back({ arr[i], 1 });
			j++;
		}
	}
	for (int i = 0; i < m.size(); i++) {
		ans.push_back(m[i].first);
		m[i].second--;
		if (dfs(m[i].first, 0))
			break;
		m[i].second++;
		ans.pop_back();
	}
	return 0;
}