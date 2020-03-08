#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

//44ms
int main(void) {
	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);

	//int n, m;
	//string name;
	//set<string> nolook, nolisten;
	//cin >> n >> m;
	//while (n--) {
	//	cin >> name;
	//	nolook.insert(name);
	//}
	//while (m--) {
	//	cin >> name;
	//	if (nolook.count(name))
	//		nolisten.insert(name);
	//}
	//name = "";
	//cout << nolisten.size() << '\n';
	//for (set<string>::iterator it = nolisten.begin(); it != nolisten.end(); it++)
	//	name += *it + '\n';
	//cout << name;
	//return 0;

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	string name;
	set<string> nolook;
	vector<string> ans;
	cin >> n >> m;
	while (n--) {
		cin >> name;
		nolook.insert(name);
	}
	while (m--) {
		cin >> name;
		if (nolook.count(name))
			ans.push_back(name);
	}
	name = "";
	sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (auto& s : ans)
		name += s + '\n';
	cout << name;
	return 0;
}