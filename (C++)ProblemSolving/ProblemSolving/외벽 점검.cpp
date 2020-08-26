#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int a[15];
vector<int> weak, vector<int> dist;
int board_sz;

int cw(int weak_idx, int dist_idx) {
    int res = 0;
    int sz = dist.size();
    // weak[idx]에서 시계방향으로 dist[sz - i - 1]만큼 이동하면서 취약점 확인
    int start = weak[weak_idx];
    int end = weak[weak_idx] + dist[sz - dist_idx - 1];
    
    for (int j = 0; j < weak.size(); j++) {
        if ((start <= weak[j] && weak[j] <= end) || (end >= board_sz && weak[j] <= end - board_sz)) {
            res |= 1 << j;
        }
    }
    return res;
}

int ccw(int weak_idx, int dist_idx) {
    int res = 0;

    int sz = dist.size();
    // weak[idx]에서 반시계방향으로 dist[sz - i - 1]만큼 이동하면서 취약점 확인
    int end = weak[weak_idx];
    int start = weak[weak_idx] - dist[sz - dist_idx - 1];
    
    for (int j = 0; j < weak.size(); j++) {
        if ((start <= weak[j] && weak[j] <= end) || (start < 0 && weak[j] >= board_sz - start)) {
            res |= 1 << j;
        }
    }
    return res;
}
bool permu(int n, int m, int depth, int chk) {
    bool res = false;
    if (depth == m) {
        for (int i = 0; i < m; i++) {
            int chk_weak_cw = cw(a[i], i);
            int chk_weak_ccw = ccw(a[i], i);
            
        }
        cout << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (chk & (1 << i)) {
            a[depth] = i;
            res = permu(n, m, depth + 1, chk | (1 << i));
            if (res) return true;
        }
    }
    return false;
}
int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = -1;
    board_sz = n;
    
    sort(dist.begin(), dist.end());

    for (int i = 1; i <= dist.size(); i++) {
        bool res = permu(weak.size(), i, 0, 0);
        if (res) {
            answer = i;
            break;
        }
    }
    return answer;
}