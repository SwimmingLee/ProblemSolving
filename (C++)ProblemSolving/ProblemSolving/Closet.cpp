#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define MAX_POINT 100000
struct Point {
	int x, y;
};
int N;
Point points[MAX_POINT];
const int INF = 987654312;

long long calcDist(Point& a, Point& b) {
	return (long long)(a.x - b.x) * (a.x - b.x) + (long long)(a.y - b.y) * (a.y - b.y);
}

vector<Point> yAxis;
long long closet(int start, int last) {
	if (start == last) {
		return INF;
	}

	int mid = start + (last - start) / 2;
	
	long long delta1 = closet(start, mid);
	delta1 = min(delta1, closet(mid + 1, last));

	double delta = sqrt(delta1);

	yAxis.clear();
	for (int i = start; i <= last; ++i) {
		if (abs(points[mid].x - points[i].x) < delta)
			yAxis.push_back(points[i]);
	}

	sort(begin(yAxis), end(yAxis), [](const Point& lhs, const Point& rhs) {return lhs.y < rhs.y; });
	for (int i = 0; i < yAxis.size(); ++i) {
		int j = i - 1;
		while (j >= 0 && abs(yAxis[j].y - yAxis[i].y) < delta) {
			long long dist = calcDist(yAxis[j], yAxis[i]);
			if (dist < delta1) {
				delta1 = dist;
				delta = sqrt(delta1);
			}
			j--;
		}

		j = i + 1;
		while (j < yAxis.size() && abs(yAxis[j].y - yAxis[i].y) < delta) {
			long long dist = calcDist(yAxis[j], yAxis[i]);
			if (dist < delta1) {
				delta1 = dist;
				delta = sqrt(delta1);
			}
			j++;
		}
	}

	return delta1;

}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N;
		for (int i = 0; i < N; ++i) {
			cin >> points[i].x >> points[i].y;
		}

		sort(points, points + N, [](const Point& lhs, const Point& rhs) {return lhs.x < rhs.x; });
		long long answer = closet(0, N - 1);
		cout << '#' << tc << ' ' << answer << '\n';
	}
	return 0;
}