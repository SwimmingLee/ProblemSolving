#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	set<string> enter;
	
	cin >> n;
	while (n--) {
		string name, state;
		cin >> name >> state;
		if (state[0] == 'e') {
			enter.insert(name);
		}
		else {
			enter.erase(enter.find(name));
		}
	}
	for (auto it = enter.rbegin(); it != enter.rend(); it++) {
		cout << *it << '\n';
	}
	return 0;
}