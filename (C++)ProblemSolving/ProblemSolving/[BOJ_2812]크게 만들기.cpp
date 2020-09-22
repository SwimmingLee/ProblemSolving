/*
�׸����ϰ� �տ������� ���ڸ� �Ǵ��ؾ� �ȴٰ� �����ߴ�. 
�׷��� ���ڷ� �Է��� ���� �ʰ� ���ڿ��� �Է��� �޾Ҵ�.
Ȯ���� ���� �ʾ�����, ���ڸ��� �ִ� ���ڰ� ���ڸ��� �ִ� ���ں��� �۴ٸ�
�����ؾ� �Ѵٰ� �Ǵ��� �����. �ͳ������� �������� ��, �� �ڸ� ���ڰ� �������� �ĳ��µ��� ���ܴ� ������.

�ٽ� �ͳ������� ���������ʰ� �Ϲ�ȭ�ص� �Ǵ� �����ε�,�� �ͳ������θ� �����Ϸ��� ������?
������ �̷� ������ �ִ��� �ͳ������� Ǯ���� ������� 

Ư¡
1. ���� �ڸ����� ���� �κк��� ���ʴ�� �˻��� �ʿ䰡 �ֱ⿡ ���ڿ��� �Է� ����
2. ���ڿ��� ����ó�� ����Ͽ� ���ڸ� �����Ͽ���.
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
	} /*��ó��*/
	cout << answer;
	return 0;
}