//#include <string>
//#include <vector>
//#include <queue>
//#include <iostream>
//using namespace std;
//typedef pair<int, int> pii;
//int board[10][10];
//int dy[] = {0, 0, -1, 1};
//int dx[] = { -1, 1, 0, 0 };
//
//int rider_cache0[10][10];
//int rider_cache1[10];
//
//int solution(int n, vector<vector<int>> walls, vector<vector<int>> riders, vector<vector<int>> s, vector<vector<int>> e) {
//    int answer = 0;
//    for (auto wall : walls) {
//        int y = wall[0];
//        int x = wall[1];
//        board[y][x] = 1;
//    }
//
//    for (int i = 0; i < riders.size(); i++) {
//        queue<pair<int, int>> q;
//        int ry = riders[i][0];
//        int rx = riders[i][1];
//        q.push({ ry, rx });
//   
//        vector<vector<int>> chk(n, vector<int>(n, -1));
//        chk[ry][rx] = 0;
//        while (q.empty()) {
//            pii cur = q.front();
//            q.pop();
//            int y = cur.first;
//            int x = cur.second;
//            for (int cc = 0; cc++ < s.size(); cc++) {
//                if (s[cc][0] == y && s[cc][1] == x) {
//                    rider_cache0[i][cc] = chk[y][x];
//                }
//            }
//            for (int d = 0; d < 4; d++) {
//                int ny = y + dy[d];
//                int nx = x + dx[d];
//                if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
//                if (chk[ny][nx] != -1 || board[ny][nx]) continue;
//                q.push({ ny, nx });
//                chk[ny][nx] = chk[y][x] + 1;
//            }    
//        }
//    }
//
//    for (int i = 0; i < riders.size(); i++) {
//        queue<pair<int, int>> q;
//        int ry = s[i][0];
//        int rx = s[i][1];
//        q.push({ ry, rx });
//
//        vector<vector<int>> chk(n, vector<int>(n, -1));
//        chk[ry][rx] = 0;
//        while (q.empty()) {
//            pii cur = q.front();
//            q.pop();
//            int y = cur.first;
//            int x = cur.second;
//            if (e[i][0] == y && e[i][1] == x) {
//               rider_cache1[i] = chk[y][x];
//            }
//            for (int d = 0; d < 4; d++) {
//                int ny = y + dy[d];
//                int nx = x + dx[d];
//                if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
//                if (chk[ny][nx] != -1 || board[ny][nx]) continue;
//                q.push({ ny, nx });
//                chk[ny][nx] = chk[y][x] + 1;
//            }
//        }
//    }
//    return answer;
//}