#include <string>
#include <vector>
#include <iostream>
using namespace std;

string removeDot(string& s) {
    string res = "";
    int start_idx = 0;
    int end_idx = (int)s.size() - 1;

    if (s[start_idx] == '.') start_idx += 1;
    if (s[end_idx] == '.') end_idx -= 1;
    res = s.substr(start_idx, end_idx - start_idx + 1);
    
    return res;
}

string solution(string new_id) {
    string answer = "";
    // 1 단계
    for (int i = 0; i < new_id.size(); i++) {
        if ('A' <= new_id[i] && new_id[i] <= 'Z')
            new_id[i] = new_id[i] - 'A' + 'a';
    }
    cout << "[1] " << new_id << endl;
    // 2 단계
    string s2 = "";
    for (int i = 0; i < new_id.size(); i++) {
        if (('a' <= new_id[i] && new_id[i] <= 'z') || \
            ('0' <= new_id[i] && new_id[i] <= '9') || \
            new_id[i] == '-' || \
            new_id[i] == '_' || \
            new_id[i] == '.') {
            s2.push_back(new_id[i]);
        }
    }
    cout << "[2] " << s2 << endl;
    // 3 단계
    string s3 = "";
    int dot_cnt = 0;
    for (int i = 0; i < s2.size(); i++) {
        if (s2[i] == '.') {
            dot_cnt++;
        }
        else {
            dot_cnt = 0;
        }

        if (dot_cnt <= 1) {
            s3.push_back(s2[i]);
        }
    }
    cout << "[3] " << s3 << endl;
    // 4 단계
    string s4 = removeDot(s3);
    cout << "[4] " << s4 << endl;

    // 5단계
    if (s4 == "") {
        s4.push_back('a');
    }
    cout << "[5] " << s4 << endl;

    // 6 단계
    if (s4.size() >= 16) {
        if (s4[14] == '.')
            s4 = s4.substr(0, 14);
        else
            s4 = s4.substr(0, 15);
    }
    cout << "[6] " << s4 << endl;
    // 7 단계
    while (s4.size() <= 2) {
        int idx = (int)s4.size() - 1;
        s4.push_back(s4[idx]);
    }
    cout << "[7] " << s4 << endl;
    
    answer = s4;
    return answer;
}