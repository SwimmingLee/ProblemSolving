#include <iostream>
using namespace std;

typedef long long ll; /*ull 절대 안돼!!!!!!!!!!!!!!!!*/
int N;

//// return: <gcd(a, b), n, m>
//tuple<int, int, int> xGCD(int a, int b) {
//	if (b == 0) {
//		return make_tuple(a, 1, 0);
//	}
//	int g, x, y;
//	tie(g, x, y) = xGCD(b, a % b);
//	return make_tuple(g, y, x - (a / b) * y);
//}

// a*x + b*y = gcd(a,b)
// extended ecuild algorithm 전개하여 x구하기
void extendedEcuild(ll a, ll b, ll& s, ll& t) {
	ll r, r1 = a, r2 = b;
	ll x, x1 = 1, x2 = 0;
	ll y, y1 = 0, y2 = 1;
	ll q;

	while (r2 != 0) {
		q = r1 / r2;

		r = r1 - q * r2;
		r1 = r2;
		r2 = r;

		x = x1 - q * x2;
		x1 = x2;
		x2 = x;

		y = y1 - q * y2;
		y1 = y2;
		y2 = y;
	}
	s = x1;
	t = y1;

}

void crt(ll b1, ll m1, ll b2, ll m2, ll& b, ll& m) {
	// 모듈러 곱셈 역원 구하기
	// x = m1(inv m2) => m1*x = 1 mod(m2)
	// m1*s + m2*(-k) = 1
	// 이때 gcd(m1, m2) = 1 이므로 확장된 유클리드 알고리즘으로 s 계산
	ll s, t;
	extendedEcuild(m1, m2, s, t);
	// 확장 유클리드 검증
	// cout << "[m1(inv m2)] " << m1 << " " << m2 << " " << s << '\n';
	
	// x = b1 mod(m1) 과 x = b2 mod(m2)
	// x = m1*q1 + b1 = b2 mod(m2)
	// m1*q1 = b2 - b1 mod(m2)
	// q1 = m1(inv m2) * (b2 - b1) mod(m2)

	// q1 = m2*k + m1(inv m2) * (b2 - b1)
	// x = m1*q1 + b1
	// x = m1*(m2*k + m1(inv m2) *(b2-b1)) + b1
	// x = m1*m2*k + m1*m1(inv m2)*(b2-b1) + b1
	// x = m1(m1(inv m2)*(b2-b1)) + b1 mod(m1*m2)
	m = m1 * m2;
	b = (m1 * s * (b2 - b1) + b1) % m;
}

ll b[10];
ll m[10];
int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N;
		for (int i = 0; i < N; ++i) {
			cin >> b[i] >> m[i];
		}

		ll a1 = b[0];
		ll m1 = m[0];

		for (int i = 1; i < N; ++i) {
			ll a2 = b[i];
			ll m2 = m[i];

			ll a, m;
			crt(a1, m1, a2, m2, a, m);
			a1 = a;
			m1 = m;
			/*ll s, t;
			extendedEcuild(m1, m2, s, t);
			ll x = (a1 * m2 * t + a2 * m1 * s) % (m1 * m2);
			a1 = x;
			m1 = m1 * m2;*/
			
		}
		if (a1 < 0) a1 += m1;

		cout << '#' << tc << ' ' << a1 << '\n';
	}
	return 0;
}