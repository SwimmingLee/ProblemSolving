//#include <string>
//#include <vector>
//#include <queue>
//#include <iostream>
//using namespace std;
//typedef pair<long long, int> pli;
//long long user[20001];
//
//long long solution(int  m, vector<int> v) {
//    long long answer = 0;
//    priority_queue<pli> q;
//
//    for (int i = 0; i < m; i++) {
//        q.push({ 0, i });
//    }
//    for (int i = 0; i < v.size(); i++) {
//        pli cur = q.top();
//        q.pop();
//
//        user[cur.second] += v[i];
//        q.push({ -user[cur.second], cur.second });
//    }
//    bool chk = false;
//    for (int i = 0; i < m; i++) {
//        cout << user[i] << endl;
//        if (chk == false || answer > user[i]) {
//            answer = user[i];
//            chk = true;
//        }
//    }
//    return answer;
//}