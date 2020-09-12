#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int alpha = 0;
struct Food {
    int cnt;
    string course;
    bool operator< (const Food& rhs) {
        return cnt > rhs.cnt;
    }
};
vector<Food> food;
void combi(int idx, int limit, int start, int visited, vector<int>& orders) {
    if (limit == idx) {
        int cnt = 0;
        for (int i = 0; i < orders.size(); i++) {
            if ((orders[i] & visited) == visited) {
                cnt++;
            }
        }
        if (cnt >= 2) {
            string tmp = "";
            for (int i = 0; i < 26; i++) {
                if ((visited & (1 << i)))
                    tmp.push_back('A' + i);
            }
            //cout << endl;
            food.push_back({ cnt, tmp });
        }
        return;
    }
    for (int i = start; i < 26; i++) {
        if (!(alpha & (1 << i))) continue;
        combi(idx + 1, limit, i + 1, visited | (1 << i), orders);
    }
} // combi(0, limit, 0, 0, orders);

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    // 각 식단을 비트마스크로 구현해 놓자
    vector<int> orders_bit(orders.size(), 0);
    for (int i = 0; i < orders.size(); i++) {
        for (int j = 0; j < orders[i].size(); j++) {
            alpha |= (1 << (orders[i][j] - 'A'));
            orders_bit[i] |= (1 << (orders[i][j] - 'A'));
        }
    }

    // 일단 셋트 개수 순으로 조합을 구해야 함
    for (int i = 0; i < course.size(); i++) {      
        combi(0, course[i], 0, 0,  orders_bit);
        if (food.size() <= 0) continue;
        sort(food.begin(), food.end());
        int cnt = food[0].cnt;
        for (int i = 0; i < food.size(); i++) {
            if (cnt != food[i].cnt) {
                break;
            }
            answer.push_back(food[i].course);
        }
        food.clear();
    }
    sort(answer.begin(), answer.end());
    return answer;
}