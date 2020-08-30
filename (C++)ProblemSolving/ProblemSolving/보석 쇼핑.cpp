#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

int chk[100000];
vector<int> solution(vector<string> gems) {
    vector<int> answer;
    map<string, int> m;
    int n_gem = 0;
    for (int i = 0; i < gems.size(); i++) {
        if (m.find(gems[i]) == m.end()) {
            m[gems[i]] = n_gem++;
        }
    }
    int left, right, cnt;
    int prev_left, prev_right;
    left = -1;
    prev_left = 0;
    while(true) {
        for (int i = 0; i < n_gem; i++) {
            chk[i] = false;
        }
        left = right = prev_left;
        cnt = 0;
        for (int i = prev_left; i < gems.size(); i++) {
            
            int number_gem = m[gems[i]];
            if (!chk[number_gem]) {
                //cout << "[] " << number_gem << " " << i << endl;

                chk[number_gem] = true;
                cnt += 1;
                if (cnt == n_gem) {
                    right = i;
                    break;
                }
            }
            else {
                if (m[gems[left]] == number_gem) {
                    left++;
                }
            }
        }
        if (prev_left == left) break;
        prev_left = left;
        prev_right = right;
    }
    //cout << left+1 << " " << right+1 << endl;
    //cout << " " << n_gem << endl;
    answer.push_back(left + 1);
    answer.push_back(right + 1);
    return answer;
}