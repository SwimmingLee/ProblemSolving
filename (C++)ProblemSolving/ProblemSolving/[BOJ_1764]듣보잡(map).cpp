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
	// map�� ó�� ���� 0�̶�� ���� �����ϳ��� 
	while (n--) {
		cin >> name;
		nolook[name] |= 1;
	}
	while (m--) {
		cin >> name;
		nolook[name] |= 2;
	}
	//it &, ������ ���� �ӵ� ��
	int size = 0;
	for (map<string, int>::iterator it = nolook.begin(); it != nolook.end(); it++)
		if (it->second == 3) { ans += it->first + '\n'; size++; }
	cout << size << '\n';
	cout << ans;
	return 0;
}