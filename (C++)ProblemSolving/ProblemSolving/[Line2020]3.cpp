#include <string>
#include <vector>
#include <iostream>
using namespace std;
struct op {
    int cnt;
    int res;
    op(int cnt, int res) : cnt(cnt), res(res) {

    }
};

op dfs(int n, int cnt) {
    op res(999, -1);
    string s = to_string(n);
    if (s.size() == 1) return op(cnt, n);

    for (int i = 1; i < (int)s.size(); i++) {
        string pre, post;
        pre = s.substr(0, i);
        post = s.substr(i);
        if (post[0] == '0') continue;
        //cout << pre << " " << post << endl;
        int num = stoi(pre) + stoi(post);
        op tmp = dfs(num, cnt + 1);
        if (tmp.cnt < res.cnt) {
            res = tmp;
        }
    }
    return res;
} // dfs(n, 0);
vector<int> solution(int n) {
    vector<int> answer;
    op res = dfs(n, 0);
    answer.push_back(res.cnt);
    answer.push_back(res.res);
    return answer;
}