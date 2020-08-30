#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string solution(vector<int> numbers, string hand) {
    string answer = "";
    int left_layer, right_layer;
    int left_col, right_col;
    left_layer = right_layer = 3;
    left_col = 0;
    right_col = 2;
    for (int i = 0; i < numbers.size(); i++) {
        int num = numbers[i];
        int num_layer = (num == 0 ? 3 : (num - 1) / 3);
        int num_col = (num == 0 ? 1 : (num - 1) % 3);

        if (num_col == 0) {
            left_layer = num_layer;
            left_col = num_col;
            answer.push_back('L');
        }
        else if (num_col == 2) {
            right_layer = num_layer;
            right_col = num_col;
            answer.push_back('R');
        }
        else {
            int left_diff = abs(left_layer - num_layer) + abs(left_col - num_col);
            int right_diff = abs(right_layer - num_layer) + abs(right_col - num_col);
            cout << right_layer << " " << right_col << endl;
            cout << "[ " << i << " ] " << num << " >> " << left_diff << " " << right_diff << endl;

            if (left_diff < right_diff) {
                left_layer = num_layer;
                left_col = num_col;
                answer.push_back('L');
            }
            else if (left_diff > right_diff) {
                right_layer = num_layer;
                right_col = num_col;
                answer.push_back('R');
            }
            else {
                if (hand == "left") {
                    left_layer = num_layer;
                    left_col = num_col;
                    answer.push_back('L');
                }
                else {
                    right_layer = num_layer;
                    right_col = num_col;
                    answer.push_back('R');
                }
            }
        }
    }
    return answer;
}