#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<int> food_times, long long k) {
    int answer = 0;
    
    vector<int> sorted_times(food_times);
    long long n_food = food_times.size();
    long long cnt = 0;
    long long n_cycle = 0;
    int idx = 0;
    sort(sorted_times.begin(), sorted_times.end());

    while (true) {
        long long step = sorted_times[idx] - n_cycle;

        if (k < cnt + n_food * step) {
            int micro_step = (k - cnt) / n_food;
            n_cycle += micro_step;
            cnt += n_food * micro_step;
            break;
        }
        n_cycle += step;
        cnt += n_food * step;

        while (idx < sorted_times.size() && sorted_times[idx] <= n_cycle) {
            idx++;
            n_food--;
        }
        if (idx == sorted_times.size()) {
            return -1;
        }
     }
   
    for (int i = 0; i < food_times.size(); i++) {
        if (food_times[i] > n_cycle) {
            cnt++;
            if (k < cnt) {
                answer = i + 1;
                break;
            }
        }
    }
    return answer;
}