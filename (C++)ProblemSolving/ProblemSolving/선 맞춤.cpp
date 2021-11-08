#include <iostream>
using namespace std;

#define MAX_POINT	10000
int N, e;
struct Point{
	int x, y;
	Point() {}
	Point(int _x, int _y) : x(_x), y(_y) {}
} points[MAX_POINT];

int D[MAX_POINT];

void init() {
	for (int i = 0; i < N; ++i) {
		D[i] = 0;
	}
}

long long ccw(Point& a, Point& b, Point& c) {
	return (b.x - a.x)* (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}


bool rightTurn(Point& a, Point& b, Point& c) {
	return ccw(a, b, c) <= 0;
}
bool leftTurn(Point& a, Point& b, Point& c) {
	return ccw(a, b, c) >= 0;
}

int lineFitting() {
	// x 좌표가 작은 순으로 하나씩 검사하기
	for (int i = 0; i < N - 1; ++i) {
		Point upper(points[i].x, points[i].y + 1);
		Point lower(points[i].x, points[i].y - 1);
		// 기준 점 i 보다 x축으로 더 큰 점 j로 선분을 이어보기
		for (int j = i + 1; j < N; ++j) {
			// upper, lower 업데이트
			Point tmpUpper = Point(points[j].x, points[j].y + e);
			if (rightTurn(points[i], upper, tmpUpper))
				upper = tmpUpper;
			Point tmpLower = Point(points[j].x, points[j].y - e);
			if (leftTurn(points[i], lower, tmpLower))
				lower = tmpLower;

			// upper, lower 위치가 역전됐으면 멈춤 
			if (!rightTurn(points[i], upper, lower)) break;

			// 점 j가 선분 upper, lower 사이에 있는지 검사
			if (rightTurn(points[i], upper, points[j]) && leftTurn(points[i], lower, points[j])) {
				if (D[j] == 0)
					D[j] = D[i] + 1;
				else
					D[j] = min(D[j], D[i] + 1);
			}
		}
	}

	return D[N-1];
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> e;
		init();
		for (int i = 0; i < N; ++i) {
			int x, y;
			cin >> points[i].x >> points[i].y;
		}
		int answer = lineFitting();
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}