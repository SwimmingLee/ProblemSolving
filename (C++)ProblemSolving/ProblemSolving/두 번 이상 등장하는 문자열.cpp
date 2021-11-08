#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int L;
string haystack;
vector<pair<unsigned long long, int>> hashDummy;

bool cmpString(int i, int j, int n) {
	for (int k = 0; k < n; ++k) {
		if (haystack[i + k] != haystack[j + k])
			return false;
	}
	return true;
}

bool hasTwoSubString(int n) {
	hashDummy.clear();
	const int base = 37;
	unsigned long long hash = 0;
	unsigned long long power = 1;

	for (int i = 0; i < haystack.size(); ++i) {
		if (i < n) {
			hash = (hash * base) + (haystack[i] - 'a');
			power = power * base;
			if (i == n - 1)
				hashDummy.push_back({ hash, i - (n - 1)});
		}
		else {
			hash = (hash * base) + (haystack[i] - 'a') - power * (haystack[i - n] - 'a');
			hashDummy.push_back({ hash, i - (n - 1) });
		}
	}

	sort(hashDummy.begin(), hashDummy.end());
	int prevIdx = 0;
	for (int i = 1; i < hashDummy.size(); ++i) {
		if (hashDummy[i].first != hashDummy[i - 1].first) {

			for (int j = prevIdx; j < i - 1; ++j) {
				for (int k = j + 1; k < i; ++k) {
					if (cmpString(hashDummy[j].second, hashDummy[k].second, n))
						return true;
				}
			}
			prevIdx = i;
		}
	}
	for (int j = prevIdx; j < hashDummy.size() - 1; ++j) {
		for (int k = j + 1; k < hashDummy.size(); ++k) {
			if (cmpString(hashDummy[j].second, hashDummy[k].second, n))
				return true;
		}
	}
	return false;

}

int twoSubString(int first, int last) {
	int ret = 0;

	int mid;
	while (first <= last) {
		mid = (first + last) / 2;
		if (hasTwoSubString(mid)) {
			first = mid + 1;
			
			if (mid > ret) {
				ret = mid;
			}
		}
		else {
			last = mid - 1;
		}
	}
	if (ret == 1) ret = 0;

	return ret;
}


int main(void) {
	/*ios::sync_with_stdio(false);
	cin.tie(NULL);*/
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> L >> haystack;
		int answer = twoSubString(0, L-1);
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}