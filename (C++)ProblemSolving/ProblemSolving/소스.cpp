//#include <string>
//#include <vector>
//#include <iostream>
//
//using namespace std;
//
//string solution(vector<int> numbers, string hand) {
//    string answer = "";
//    int left_hand_y = 3, right_hand_y = 3;
//    int left_hand_x = 0, right_hand_x = 2;
//    for (int i = 0; i < numbers.size(); i++) {
//        int cur_x, cur_y;
//        if (numbers[i] == 0) {
//            cur_y = 3;
//            cur_x = 1;
//        }
//        else {
//            cur_y = (numbers[i] - 1) / 3;
//            cur_x = (numbers[i] - 1) % 3;
//        }
//
//        if (cur_x == 0) {
//            answer.append("L");
//            left_hand_y = cur_y;
//            left_hand_x = cur_x;
//        }
//        else if (cur_x == 2) {
//            answer.append("R");
//            right_hand_y = cur_y;
//            right_hand_x = cur_x;
//        } else {
//            int left_diff = abs(left_hand_y - cur_y) + abs(left_hand_x - cur_x);
//            int right_diff = abs(right_hand_y - cur_y) + abs(right_hand_x - cur_x);
//            cout << "left diff" << left_diff << " right_diff" << right_diff << endl;
//
//            if (left_diff > right_diff) {
//                answer.append("R");
//                right_hand_y = cur_y;
//                right_hand_x = cur_x;
//            }
//            else if (left_diff < right_diff) {
//                answer.append("L");
//                left_hand_y = cur_y;
//                left_hand_x = cur_x;
//            }
//            else {
//                if (hand == "right") {
//                    answer.append("R");
//                    right_hand_y = cur_y;
//                    right_hand_x = cur_x;
//                }
//                else {
//                    answer.append("L");
//                    left_hand_y = cur_y;
//                    left_hand_x = cur_x;
//                }
//            }
//        }
//        
//    }
//    return answer;
//}