#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

//60ms
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	string name;
	map<string, int> nolook;
	string ans;
	cin >> n >> m;
	// map은 처음 값이 0이라는 것을 보장하나봄 
	while (n--) {
		cin >> name;
		nolook[name] |= 1;
	}
	while (m--) {
		cin >> name;
		nolook[name] |= 2;
	}
	//it &, 유무에 따른 속도 비교
	int size = 0;
	for (map<string, int>::iterator it = nolook.begin(); it != nolook.end(); it++)
		if (it->second == 3) { ans += it->first + '\n'; size++; }
	cout << size << '\n';
	cout << ans;
	return 0;
}