#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
struct ele{
    int dir, y, x;
    int cost;
};
//typedef pair<pair<int, int>, pair<int, int>> pii;
vector<vector<int>> cost[2];
int dy[] = { 0, 0, -1, 1 };
int dx[] = { -1, 1, 0, 0 };
int solution(vector<vector<int>> board) {
    int answer = 0;
    int inf = 987987987;
    int board_sz = board.size();
    cost[0].resize(board_sz, vector<int>(board_sz, inf));
    cost[1].resize(board_sz, vector<int>(board_sz, inf));
    queue<ele> q;
    q.push({ 0, 0, 0, 0});
    q.push({ 1, 0, 0, 0});
    cost[0][0][0] = 0;
    cost[1][0][0] = 0;

    while (!q.empty()) {
        ele cur = q.front();
        int y = cur.y;
        int x = cur.x;
        int cdir = cur.dir;
        int ccost = cur.cost;
        q.pop();
        //cout << y << " " << x << " " << dir << endl;
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || nx < 0 || ny >= board_sz || nx >= board_sz) continue;
            if (board[ny][nx] == 1) continue;
            // 꺽이는 경우 
            // dir == 0 수직
            // dir == 1 수평 
            if ((cdir == 0 && i < 2) || (cdir == 1 && i >= 2)) {
                int ndir = (i < 2 ? 1 : 0);
                int ncost = ccost + 600;
                if (ncost < cost[ndir][ny][nx]) {
                    cost[ndir][ny][nx] = ncost;
                    q.push({ ndir, ny, nx, ncost});
                }
            }
            else {
                int ndir = (i < 2 ? 1 : 0);
                int ncost = ccost + 100;
                if (ncost < cost[ndir][ny][nx]) {
                    cost[ndir][ny][nx] = ncost;
                    q.push({ ndir, ny, nx, ncost });
                }
            }
            
        }
    }
    //for (int i = 0; i < board_sz; i++) {
    //    for (int j = 0; j < board_sz; j++) {
    //        cout << cost[0][i][j] << ' ';
    //    }
    //    cout << endl;
    //}
    //cout << "-----\n";
    //for (int i = 0; i < board_sz; i++) {
    //    for (int j = 0; j < board_sz; j++) {
    //        cout << cost[1][i][j] << ' ';
    //    }
    //    cout << endl;
    //}
    answer = min(cost[0][board_sz - 1][board_sz - 1], cost[1][board_sz-1][board_sz-1]);
    return answer;
}