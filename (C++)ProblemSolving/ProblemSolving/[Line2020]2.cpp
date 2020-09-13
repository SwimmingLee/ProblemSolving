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
        // 공 빼내기
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
        // 뺴낼 수 없다면 웨이팅에 포함시킴
        else {
            wait[order[i]] = true;
        }

        // 공이 빠졌는데 왼쪾이나 오른쪾에 사용할 수 있따면 
        // 바로 그 공은 제거한다. 
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