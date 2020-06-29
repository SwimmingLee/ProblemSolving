#include <string>
#include <vector>
#include <iostream>
#include <stack>
using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int row_sz = board.size();
    vector<int> st;
    for (int c : moves) {
        for (int r = 0; r < row_sz; r++) {
            int& cur = board[r][c - 1];
            if (cur != 0) {
                int cnt = 0;
                while (!st.empty() && st.back() == cur) {
                    st.pop_back();
                    cnt += 1;
                }
                if (cnt != 0)
                    answer += cnt + 1;
                else
                    st.push_back(cur);

                cur = 0;
                break;
            }
        }
    }
    return answer;
}

//int solution(vector<vector<int>> board, vector<int> moves) {
//    int answer = 0;
//    int height = board[0].size();
//    vector<int> st;
//    for (int c : moves) {
//        for (int r = 0; r < height; r++) {
//            int& stat = board[r][c-1];
//            if (stat != 0) {
//                if (!st.empty() && st.back() == stat) {
//                    answer += 2;
//                    st.pop_back();
//                }
//                else {
//                    st.push_back(stat);
//                }
//                stat = 0;
//                break;
//            }
//        }
//    }
//    return answer;
//}
