#include <string>
#include <vector>
#include <iostream>
using namespace std;

int dy[] = { 0, 1, 0, -1 };
int dx[] = { 1, 0, -1, 0 };

int solution(vector<vector<int>> maze) {
    int answer = 0;
    int y, x, d;
    y = x = d = 0;

    // 앞으로 갈 수 있으면 앞으로 가는 것이 맞다
    // 그리고 왼쪽에 옆에 벽이 없으면 왼쪽으로 꺾는다 
    // 그리고 가려고 하는 방향에 벽이 있으면 오른쪽으로 꺽는다. 
    bool bfinish = false;
    while (!bfinish) {
        int ny = y + dy[d];
        int nx = x + dx[d];
        // 가려고 하는 방향이 벽으로 막혀 있으면 오른쪽 회전
        if (ny < 0 || nx < 0 || ny >= maze.size() || nx >= maze[0].size() || \
            maze[ny][nx] == 1) {
            d = (d + 1) % 4;
            continue;
        }

        // 가려고 하는 방향으로 갈 수 있다면 일단 간다.
        y = ny;
        x = nx;
        //cout << y << " " << x << " " << endl;
        answer++;

        // 도착했다면 탈출
        if (y == maze.size() - 1 && x == maze[0].size() - 1) {
            bfinish = true;
            break;
        }

        // 왼쪽에 벽이 있는부터 확인
        int left_dir = (d + 3) % 4;
        ny = y + dy[left_dir];
        nx = x + dx[left_dir];
        /*if (ny >= 0 && nx >= 0 && ny < maze.size() && nx < maze[0].size())
            cout << "[] " << ny << " " << nx << " " << maze[ny][nx] << " " << endl;*/
        // 왼쪽에 벽이 없으면 왼쪽으로 회전
        if (ny >= 0 && nx >= 0 && ny < maze.size() && nx < maze[0].size() && \
            maze[ny][nx] != 1) {
            d = left_dir;
        }
    }
    return answer;
}