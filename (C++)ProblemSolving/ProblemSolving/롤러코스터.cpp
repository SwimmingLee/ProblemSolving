#include <algorithm>
using namespace std;
#define MAX_RAIL	200000
extern int CalcFinalSpeed(int N, int* a, int* b, int* p);

/*
* �̰� ��� �̷��� Ǯ ������ ����?
* ��¥... �� �� �̷� ������ ������? 
* 
* �ϴ� �������� �����غ���, �״����� ���� ��Ģ�� ���� ������ �ϴ� �������� �����ϴϱ� ��Ǯ����. 
* �̰� ��Ȯ�� ���� �ִٰ� ������ �� ������!
* �׸��� ���� ���̶� �޶����� ���� �ִٸ� �װ�, �亸�� �ӵ��� �� ���� ���̴�. ��� ������ ������ �Ѵ�....
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