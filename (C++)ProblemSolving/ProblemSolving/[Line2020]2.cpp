#include <string>
#include <vector>
#include <iostream>
using namespace std;
bool wait[1000001];
bool chk[1000001];
vector<int> solution(vector<int> ball, vector<int> order) {
    vector<int> answer;
    int left, right;

    left = 0;
    right = ball.size() - 1;
    for (int i = 0; i < order.size(); i++) {
        // �� ������
        if (order[i] == ball[left]) {
            answer.push_back(ball[left]);
            chk[ball[left]] = true;
            left += 1;
        }
        else if (order[i] == ball[right]) {
            answer.push_back(ball[right]);
            chk[ball[right]] = true;
            right -= 1;
        }
        // ���� �� ���ٸ� �����ÿ� ���Խ�Ŵ
        else {
            wait[order[i]] = true;
        }

        // ���� �����µ� �ަU�̳� �����U�� ����� �� �ֵ��� 
        // �ٷ� �� ���� �����Ѵ�. 
        while ((!chk[ball[left]] && wait[ball[left]]) || \
            (!chk[ball[right]] && wait[ball[right]])) {

            if (!chk[ball[left]] && wait[ball[left]]) {
                chk[ball[left]] = true;
                answer.push_back(ball[left]);
                left += 1;
            }
            if (!chk[ball[right]] && wait[ball[right]]) {
                chk[ball[right]] = true;
                answer.push_back(ball[right]);
                right -= 1;
            }
        }

        cout << left << " " << right << endl;
    }
    return answer;
}