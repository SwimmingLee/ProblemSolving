#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int numbering[1 << 10];
int cnt;
int convert(int n) {
    if (numbering[n] == 0) {
        numbering[n] = ++cnt;
        return numbering[n];
    }
    else {
        return numbering[n];
    }
}
vector<int> dev_set[200];
vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    for (int i = 0; i < info.size(); i++) {
        int f_idx = 0;
        int seq = 0;
        info[i].push_back(' ');
        int a, b, c, d;
        a = b = c = d = 0;
        int score = 0;
        for (int j = 0; j < info[i].size(); j++) {
            if (info[i][j] == ' ') {
                string tmp = info[i].substr(f_idx, j - f_idx);

                if (seq == 0) {
                    if (tmp[0] == 'c') {
                        a = 1 << 0;
                    }
                    else if (tmp[0] == 'j') {
                        a = 1 << 1;
                    }
                    else {
                        a = 1 << 2;
                    }
                }
                else if (seq == 1) {
                    if (tmp[0] == 'b') {
                        b = 1 << 3;
                    }
                    else {
                        b = 1 << 4;
                    }
                }
                else if (seq == 2) {
                    if (tmp[0] == 'j') {
                        c = 1 << 5;
                    } else {
                        c = 1 << 6;
                    }
                }
                else if (seq == 3) {
                    if (tmp[0] == 'c') {
                        d = 1 << 7;
                    }
                    else {
                        d = 1 << 8;
                    }
                }
                else {
                    for (int k = 0; k < tmp.size(); k++) {
                        score = score * 10 + tmp[k] - '0';
                    }
                }
                f_idx = j + 1;              
                seq++;
            }
        } // 한사람 분석 끝!
        //cout << a << " " << b << " " << c << " " << d << " " << score << endl;
        int idx = convert(0);
        dev_set[idx].push_back(score);
        
        idx = convert(a | b | c | d);
        dev_set[idx].push_back(score);

        idx = convert(a | b | c);
        dev_set[idx].push_back(score);

        idx = convert(a | b | d);
        dev_set[idx].push_back(score);

        idx = convert(a | c | d);
        dev_set[idx].push_back(score);

        idx = convert(b | c | d);
        dev_set[idx].push_back(score);

        idx = convert(a | b);
        dev_set[idx].push_back(score);

        idx = convert(a | c);
        dev_set[idx].push_back(score);

        idx = convert(a | d);
        dev_set[idx].push_back(score);

        idx = convert(b | c);
        dev_set[idx].push_back(score);

        idx = convert(b | d);
        dev_set[idx].push_back(score);

        idx = convert(c | d);
        dev_set[idx].push_back(score);

        idx = convert(a);
        dev_set[idx].push_back(score);

        idx = convert(b);
        dev_set[idx].push_back(score);

        idx = convert(c);
        dev_set[idx].push_back(score);

        idx = convert(d);
        dev_set[idx].push_back(score);
    }

    for (int i = 0; i < 200; i++) {
        sort(dev_set[i].begin(), dev_set[i].end());
    }

    //cout << cnt << endl;
    for (int i = 0; i < query.size(); i++) {
        int f_idx = 0;
        int seq = 0;
        query[i].push_back(' ');
        int a, b, c, d;
        a = b = c = d = 0;
        int score = 0;
        for (int j = 0; j < query[i].size(); j++) {
            if (query[i][j] == ' ') {
                string tmp = query[i].substr(f_idx, j - f_idx);

                f_idx = j + 1;
                if (tmp == "and") {
                    continue;
                }
                
                if (seq == 0) {
                   // cout << tmp << endl;
                    if (tmp[0] == 'c') {
                        a = 1 << 0;
                    }
                    else if (tmp[0] == 'j') {
                        a = 1 << 1;
                    }
                    else if (tmp[0] == 'p'){
                        a = 1 << 2;
                    }
                }
                else if (seq == 1) {
                    if (tmp[0] == 'b') {
                        b = 1 << 3;
                    }
                    else if (tmp[0] == 'f'){
                        b = 1 << 4;
                    }
                }
                else if (seq == 2) {
                    if (tmp[0] == 'j') {
                        c = 1 << 5;
                    }
                    else if (tmp[0] == 's'){
                        c = 1 << 6;
                    }
                }
                else if (seq == 3) {
                    if (tmp[0] == 'c') {
                        d = 1 << 7;
                    }
                    else if (tmp[0] == 'p'){
                        d = 1 << 8;
                    }
                }
                else {
                    for (int k = 0; k < tmp.size(); k++) {
                        score = score * 10 + tmp[k] - '0';
                    }
                }               
                seq++;
                
            }
           
        } // 하나 분석 끝!
        //cout << a << " " << b << " " << c << " " << d << " " << score << endl;
        //cout << (a | b | c | d) << endl;
        int idx = convert((a | b | c | d));
        int p_cnt = 0;
        //cout << "[] " << idx << endl;

        for (int i = 0; i < dev_set[idx].size(); i++) {
            //cout << dev_set[idx][i] << endl;
            if (dev_set[idx][i] >= score) p_cnt++;
        }
        answer.push_back(p_cnt);
    }
    return answer;
}