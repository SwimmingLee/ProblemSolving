#include <string>
#include <vector>

using namespace std;

int chk[1000001];
int solution(vector<vector<int>> boxes) {
    int answer = -1;
    int n_box = boxes.size();
    for (int i = 0; i < n_box; i++) {
        chk[boxes[i][0]]++;
        chk[boxes[i][1]]++;
    }
    int n_set = 0;
    for (int i = 1; i < 1000001; i++) {
        n_set += chk[i] / 2;
    }
    answer = n_box - n_set;
    return answer;
}