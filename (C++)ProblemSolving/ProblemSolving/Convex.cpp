#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_POINT 100001

struct Point {
	int x, y;
	Point operator-(const Point& rhs) {
		Point p;
		p.x = this->x - rhs.x;
		p.y = this->y - rhs.y;
		return p;
	}
	bool operator<(const Point& rhs) {
		return (this->x != rhs.x ? this->x < rhs.x : this->y < rhs.y);
	}
};

int N;
Point points[MAX_POINT];

long long ccw(const Point& a, const Point& b) {
	return ((long long)a.x * b.y) - ((long long)a.y * b.x);
}
long long ccw(Point& a, Point& b, Point& c) {
	return ccw(b - a, c - a);
}

int main(void) {
	int T;
	cin >> T;
	vector<Point> st;
	vector<Point> upper_st;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N;
		for (int i = 0; i < N; ++i) {
			cin >> points[i].x >> points[i].y;
		}
		sort(points, points + N);

		int k = 0;
		st.clear();
		for (int i = 0; i < N; ++i) {
			int sz = st.size();
			while (sz >= 2 && ccw(st[sz - 2], st[sz - 1], points[i]) <= 0) {
				k--;
				st.pop_back();
				sz = st.size();
			}
			k++;
			st.push_back(points[i]);
		}

		int t = k + 1;
		for (int i = N - 1; i >= 0; --i) {
			int sz = st.size();
			while (sz >= t && ccw(st[sz - 2], st[sz - 1], points[i]) <= 0) {
				k--;
				st.pop_back();
				sz = st.size();
			}
			k++;
			st.push_back(points[i]);
		}

		cout << '#' << tc << ' ' << k-1 << '\n';
	}
	return 0;
}