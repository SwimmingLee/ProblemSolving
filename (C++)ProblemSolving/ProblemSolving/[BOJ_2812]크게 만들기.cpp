/*
그리디하게 앞에서부터 숫자를 판단해야 된다고 생각했다. 
그래서 숫자로 입력을 받지 않고 문자열로 입력을 받았다.
확신은 들지 않았지만, 앞자리에 있는 숫자가 뒷자리에 있는 숫자보다 작다면
추출해야 한다고 판단이 들었다. 귀납적으로 생각했을 때, 앞 자리 숫자가 작을때는 쳐내는데서 예외는 없었다.

다시 귀납적으로 생각하지않고 일반화해도 되는 문제인데,왜 귀납적으로만 생각하려고 했을까?
앞으로 이런 문제는 최대한 귀납적으로 풀려고 노력하자 

특징
1. 가장 자릿수가 높은 부분부터 차례대로 검사할 필요가 있기에 문자열로 입력 받음
2. 문자열을 스택처럼 사용하여 숫자를 보관하였음.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int n, k;
	string s;
	cin >> n >> k >> s;
	
	string answer;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		while (!answer.empty() && cnt < k && answer.back() < s[i]) {
			answer.pop_back();
			cnt++;
		}
		answer.push_back(s[i]);
	}
	while (cnt < k) {
		answer.pop_back();
		cnt++;
	} /*끝처리*/
	cout << answer;
	return 0;
}