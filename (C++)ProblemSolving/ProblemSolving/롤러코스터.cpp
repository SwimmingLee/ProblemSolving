#include <algorithm>
using namespace std;
#define MAX_RAIL	200000
extern int CalcFinalSpeed(int N, int* a, int* b, int* p);

/*
* 이걸 어떻게 이렇게 풀 생각을 했지?
* 진짜... 난 왜 이런 생각을 못했지? 
* 
* 일단 수식으로 전개해보고, 그다음에 뭔가 규칙이 있지 않을까 하는 생각으로 접근하니까 못풀었다. 
* 이건 정확히 답이 있다고 생각을 한 다음에!
* 그리고 나서 답이랑 달라지는 것이 있다면 그건, 답보다 속도가 더 빠를 것이다. 라는 생각을 가져야 한다....
*/
struct compare {
    int* a;
    int* b;
    compare(int* a, int* b) {
        this->a = a;
        this->b = b;
    }
    bool operator()(const int lhs, const int rhs) {
        double lvel = (double)(a[lhs] - 1) / b[lhs];
        double rvel = (double)(a[rhs] - 1) / b[rhs];

        return lvel > rvel;
    }
};

int p[MAX_RAIL];
int MinRailSpeed(int N, int* a, int* b) {
    int answer = 0;
    for (int i = 0; i < N; ++i) {
        p[i] = i;
    }
    sort(p, p + N, compare(a, b));

    answer = CalcFinalSpeed(N, a, b, p);
    return answer;
}