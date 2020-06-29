#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
#define max_element 100000
vector<int> solution(string s) {
    vector<int> answer;
    vector<pair<int, string>> element;
    vector<bool> chk(max_element + 1, false);
    int start, end;
    for (int i = 1; i < (int)s.size()-1; i++) {
        if (s[i] == '{')
            start = i+1;
        if (s[i] == '}') {
            element.push_back({ i - start + 1, s.substr(start, i - start + 1) });
        }
    }
    sort(element.begin(), element.end());

    int n = 0;
    for (auto& ele : element) {
        int n = 0;
        for (char c : ele.second) {
            if (c == ',' || c == '}') {
                if (!chk[n]) {
                    answer.push_back(n);
                    chk[n] = true;
                    break;
                }
                n = 0;
            }
            else {
                n = n * 10 + c - '0';
            }
        }
    }
    return answer;
}

vector<int> solution(string s) {
    vector<int> answer;
    vector<string> tuples;
    vector<bool> chk(100000 + 1, false);
    int start, end;
    for (int i = 1; i < (int)s.size() - 1; i++) {
        if (s[i] == '{') {
            start = i + 1;
        }
        else if (s[i] == '}') {
            int sub_length = i - start + 1;
            tuples.emplace_back(s.substr(start, sub_length));
        }
    }
    sort(tuples.begin(), tuples.end(), \
        [](string& a, string& b) -> bool {return a.size() < b.size(); });
    answer.resize(tuples.size());
    
    for (int i = 0; i < tuples.size(); i++) {
        string& tuple = tuples[i];
        int num = 0;
        for (char c : tuple) {
            if (c == ',' || c == '}') {
                if (!chk[num]) {
                    answer[i] = num;
                    chk[num] = true;
                    break;
                }
                num = 0;
            }
            else {
                num = num * 10 + c - '0';
            }
        }
    }
    return answer;
}