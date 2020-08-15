#include <iostream>
#include <string>
#include <queue>
using namespace std;

int height, width;
string board[101];
bool chk[101][101];
int dh[] = { 0, 0, -1, 1 };
int dw[] = { -1, 1, 0, 0 };

//stick height

bool isSafe(queue<pair<int, int>>& Q) {
    int sz = Q.size();
    if (sz == 0) return true;

    //int num = chk[Q.front().first][Q.front().second];
    while (sz--) {
        int h = Q.front().first;
        int w = Q.front().second;
        Q.pop();
        Q.push({ h, w });

        if (h + 1 == height || (chk[h+1][w] == false && board[h+1][w] == 'x')) {
            return true;
        }
    }
    return false;
}

void moveDown(queue<pair<int, int>>& Q) {
    int sz = Q.size();

    //int num = chk[Q.front().first][Q.front().second];
    while (sz--) {
        int h = Q.front().first;
        int w = Q.front().second;
        Q.pop();
        Q.push({ h, w });
        board[h][w] = '.';
        chk[h][w] = false;
    }
    sz = Q.size();
    while (sz--) {
        int h = Q.front().first;
        int w = Q.front().second;
        Q.pop();
        Q.push({ h + 1, w });
        board[h + 1][w] = 'x';
        chk[h + 1][w] = true;
    }
}

void initChk() {
    // 초기화 
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            chk[h][w] = false;
        }
    }
}

void moveStick(int sh, int order) {
    int sw = -1;
    sh = height - sh;

    if (order % 2 == 0) {
        // 왼쪽에서 막대 날라감 
        for (int w = 0; w < width; w++) {
            if (board[sh][w] == 'x') {
                sw = w;
                break;
            }
        }
    }
    else {
        // 오른쪾에서 막대 날라감 =
        for (int w = width - 1; w >= 0; w--) {
            if (board[sh][w] == 'x') {
                sw = w;
                break;
            }
        }
    }
    // 미네랄 없으면 통과 
    if (sw == -1) return;

    board[sh][sw] = '.';
    for (int d = 0; d < 4; d++) {
        queue<pair<int, int>> Q;
        queue<pair<int, int>> chkQ;
        initChk();

        int ssh = sh + dh[d];
        int ssw = sw + dw[d];
        if (ssh < 0 || ssw < 0 || ssh >= height || ssw >= width) continue;
        if (board[ssh][ssw] == 'x') {
            chkQ.push({ ssh, ssw });
            chk[ssh][ssw] = true;
        }
        // 위쪽 클러스터 미네랄 획득
        while (!chkQ.empty()) {
            int h = chkQ.front().first;
            int w = chkQ.front().second;
            chkQ.pop();
            Q.push({ h, w });

            for (int i = 0; i < 4; i++) {
                int nh = h + dh[i];
                int nw = w + dw[i];

                if (nh < 0 || nw < 0 || nh >= height || nw >= width) continue;
                if (board[nh][nw] == 'x' && !chk[nh][nw]) {
                    chkQ.push({ nh, nw });
                    chk[nh][nw] = true;
                }
            }
        }

        while (!isSafe(Q)) {
            moveDown(Q);
        }
     
    }
}

int main(void) {
    cin >> height >> width;

    for (int h = 0; h < height; h++) {
        cin >> board[h];
    }
    int n_attack;
    cin >> n_attack;
    for (int i = 0; i < n_attack; i++) {
        int stick_height;
        cin >> stick_height;
        moveStick(stick_height, i);

        //cout << "****************" << endl;
        //for (int h = 0; h < height; h++) {
        //    cout << board[h] << '\n';
        //}
        //cout << endl;
    }


    for (int h = 0; h < height; h++) {
        cout << board[h] << '\n';
    }
    return 0;
}