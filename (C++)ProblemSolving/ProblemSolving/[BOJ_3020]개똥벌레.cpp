#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, H;
vector<int> down_line;
vector<int> up_line;

int bsearch(vector<int>& line, int var) {
    int start, mid, end;
    start = 0;
    end = (N / 2) - 1;

    int res = -1;
    while (start <= end) {
        mid = (start + end) / 2;
        if (line[mid] <= var) {
            start = mid + 1;
            if (res < mid) {
                res = mid;
            }
        }
        else {
            end = mid - 1;
        }
    }
    return res;
}

int main(void) {
    cin.tie(NULL); ios::sync_with_stdio(false);
    cin >> N >> H;
    down_line.resize(N / 2);
    up_line.resize(N / 2);
    for (int i = 0; i < N; i++) {
        int len;
        cin >> len;
        if (i % 2 == 0)  down_line[i / 2] = len;
        else up_line[i / 2] = len;
    }
    sort(down_line.begin(), down_line.end());
    sort(up_line.begin(), up_line.end());
    int cnt = 0;
    int len = -1;

    for (int i = 1; i <= H; i++) {
        // STL upper_bound를 사용했을 때
        //vector<int>::iterator upper1, upper2;
        //upper1 = upper_bound(down_line.begin(), down_line.end(), i - 1);
        //upper2 = upper_bound(up_line.begin(), up_line.end(), H - i);

        //int u = N/2 - (upper1 - down_line.begin());
        //int v = N/2 - (upper2 - up_line.begin());
        
        // 직접 만든 upper_bound를 이용했을 때
        int u = N / 2 - bsearch(down_line, i-1) - 1;
        int v = N / 2 - bsearch(up_line, H-i) - 1;
        cout << u << " " << v << endl;
        int sum = u + v;
        if (len == sum) {
            cnt++;
        }
        else if (len == -1 || len > sum) {
            cnt = 1;
            len = sum;
        }

    }
    cout << len << ' ' << cnt << endl;
    return 0;
}