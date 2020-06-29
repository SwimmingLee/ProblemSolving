#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int solution(string road, int n) {
	int answer = -1;
	int length = road.size();
	int left = 0, right = 0;
	int cnt = 0;
	while (right < length) {
		if (road[right] == '0') {
			cnt += 1;
			right += 1;
			if (cnt > n) {
				while (road[left] == '1') {
					left += 1;
				}
				left += 1;
				cnt -= 1;
			}
		}
		else {
			right += 1;
		}
		answer = max(answer, right - left);
		cout << left << " " << right << endl;
	}
	return answer;
}

int main(void) {
	string road;
	int n;


	road = "111011110011111011111100011111";
	n = 3;
	road = "001100";
	n = 5;
	road = "000";
	n = 0;
	road = "001";
	n = 1;
	cout << solution(road, n) << endl;
	return 0;
}