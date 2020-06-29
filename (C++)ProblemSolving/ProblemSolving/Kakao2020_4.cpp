#include <vector>
#include <iostream>
#include <map>
using namespace std;
map<long long, long long> parent;
long long find(long long u) {
	if (parent.find(u) == parent.end()) return u;
	else return parent[u] = find(parent[u]);
}
void merge(long long u) {
	u = find(u);
	long long v = find(u + 1);
	parent[u] = v;
}
vector<long long> solution(long long k, vector<long long> room_number) {
	vector<long long> answer;
	//for (long long i = 0; i <= k; i++) parent[i] = i
	for (auto room : room_number) {
		long long u = find(room);
		merge(room);
		answer.push_back(u);
	}
	return answer;
}


int main() {
	vector<long long> ans;
	long long k = 10;
	vector<long long> room_number;

	room_number.push_back(1LL);
	room_number.push_back(3LL);
	room_number.push_back(4LL);
	room_number.push_back(1LL);
	room_number.push_back(3LL);
	room_number.push_back(1LL);

	ans = solution(k, room_number);
	for (auto c : ans)
		cout << c << ' ';
	cout << endl;
	return 0;
}