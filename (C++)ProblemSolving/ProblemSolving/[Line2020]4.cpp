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

    // ������ �� �� ������ ������ ���� ���� �´�
    // �׸��� ���ʿ� ���� ���� ������ �������� ���´� 
    // �׸��� ������ �ϴ� ���⿡ ���� ������ ���������� ���´�. 
    bool bfinish = false;
    while (!bfinish) {
        int ny = y + dy[d];
        int nx = x + dx[d];
        // ������ �ϴ� ������ ������ ���� ������ ������ ȸ��
        if (ny < 0 || nx < 0 || ny >= maze.size() || nx >= maze[0].size() || \
            maze[ny][nx] == 1) {
            d = (d + 1) % 4;
            continue;
        }

        // ������ �ϴ� �������� �� �� �ִٸ� �ϴ� ����.
        y = ny;
        x = nx;
        //cout << y << " " << x << " " << endl;
        answer++;

        // �����ߴٸ� Ż��
        if (y == maze.size() - 1 && x == maze[0].size() - 1) {
            bfinish = true;
            break;
        }

        // ���ʿ� ���� �ִº��� Ȯ��
        int left_dir = (d + 3) % 4;
        ny = y + dy[left_dir];
        nx = x + dx[left_dir];
        /*if (ny >= 0 && nx >= 0 && ny < maze.size() && nx < maze[0].size())
            cout << "[] " << ny << " " << nx << " " << maze[ny][nx] << " " << endl;*/
        // ���ʿ� ���� ������ �������� ȸ��
        if (ny >= 0 && nx >= 0 && ny < maze.size() && nx < maze[0].size() && \
            maze[ny][nx] != 1) {
            d = left_dir;
        }
    }
    return answer;
}