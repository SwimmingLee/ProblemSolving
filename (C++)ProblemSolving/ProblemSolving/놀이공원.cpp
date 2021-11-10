#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int mId[], int mDuration[], int mCapacity[]);
extern int add(int tStamp, int mId, int mNum, int mPriority);
extern void search(int tStamp, int mCount, int mId[], int mWait[]);

/////////////////////////////////////////////////////////////////////////

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_SEARCH 3

#define MAX_N 100

static int rideId[MAX_N];
static int rideDuration[MAX_N];
static int rideCapa[MAX_N];

static bool run() {
	int q;
	scanf("%d", &q);

	int n, num, pri, time, idx, cnt;
	int cmd, ans, ret = 0;
	int mId[10];
	int mWait[10];
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
		case CMD_INIT:
			scanf("%d", &n);
			for (int j = 0; j < n; ++j) {
				scanf("%d %d %d", &rideId[j], &rideDuration[j], &rideCapa[j]);
			}
			init(n, rideId, rideDuration, rideCapa);
			okay = true;
			break;
		case CMD_ADD:
			scanf("%d %d %d %d %d", &time, &idx, &num, &pri, &ans);
			if (okay) {
				ret = add(time, rideId[idx], num, pri);
			}
			if (ret != ans)
				okay = false;
			break;
		case CMD_SEARCH:
			scanf("%d %d", &time, &cnt);
			if (okay) {
				search(time, cnt, mId, mWait);
			}
			for (int j = 0; j < cnt; ++j) {
				scanf("%d %d", &idx, &num);
				if (num != mWait[j] || rideId[idx] != mId[j]) {
					okay = false;
				}
			}
			break;
		default:
			okay = false;
			break;
		}
	}

	return okay;
}

int main() {
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}


#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;
#define MAX_RIDE	100
typedef pair<int, int> pii;
struct Ride{
	int id;
	int duration;
	int capacity;
	int start;
	int wait;
} rides[MAX_RIDE];
unordered_map<int, int> vTable;
priority_queue<pii> waiting[MAX_RIDE]; // priority, N - 같은 priority에 대해서 N이 여러개 있을 수 있음
priority_queue<pii> startPQ; // tStamp, vId
int N;

void init(int n, int mId[], int mDuration[], int mCapacity[]) {
	N = n;
	for (int i = 0; i < N; ++i) {
		rides[i].id = mId[i];
		rides[i].duration = mDuration[i];
		rides[i].capacity = mCapacity[i];
		rides[i].start = -999;
		rides[i].wait = 0;
		
		while (!waiting[i].empty()) {
			waiting[i].pop();
		}
	}
	while (!startPQ.empty()) {
		startPQ.pop();
	}
	vTable.clear();
	for (int i = 0; i < N; ++i) {
		vTable[rides[i].id] = i;
	}

	return;
}

// (t < tStamp) 놀이기구 출발
void playRides(int tStamp) {
	while (!startPQ.empty() && -startPQ.top().first <= tStamp) {
		int t = -startPQ.top().first;
		int vId = startPQ.top().second;
		startPQ.pop();

		// 놀이기구가 지금 운행하고 있는지 확인
		Ride& ride = rides[vId];
		if (t < ride.start + ride.duration) continue;
		// 대기인원이 있다면 몇 명 탈건지 계산하기
		int passengerCnt = 0;
		while (!waiting[vId].empty()) {
			pii waitPeople = waiting[vId].top();
			waiting[vId].pop();

			if (passengerCnt + waitPeople.second <= ride.capacity) {
				passengerCnt += waitPeople.second;
			}
			else {
				waitPeople.second -= ride.capacity - passengerCnt;
				passengerCnt += ride.capacity - passengerCnt;
				if (waitPeople.second > 0) {
					waiting[vId].push(waitPeople);
				}
				break;
			}
		}

		// 승객이 없다면 무시
		if (passengerCnt == 0)
			continue;

		// 출발 
		ride.start = t;
		ride.wait -= passengerCnt;
		

		// 출발시켰는데도 대기인원이 있다면 startPQ에 추가
		//if (ride.wait > 0) {/**/ 운행하고 있는 도중에 올 수도 있는거라서 그렇다.
			startPQ.push({ -(t + ride.duration) , vId });
		//}
	}
}

int add(int tStamp, int mId, int mNum, int mPriority) {
	playRides(tStamp-1); /**/

	int vId = vTable[mId];
	waiting[vId].push({mPriority, mNum});
	rides[vId].wait += mNum;

	startPQ.push({-tStamp, vId});

	playRides(tStamp);

	int ret;
	if (waiting[vId].empty()) {
		ret = 0;
	}
	else {
		ret = waiting[vId].top().first;
	}

	return ret;
}

struct Tmp {
	int id;
	int wait;
} tmp[100];
void search(int tStamp, int mCount, int mId[], int mWait[]) {
	playRides(tStamp);

	int cnt = 0;
	for (int i = 0; i < N; ++i) {
		tmp[i].id = rides[i].id;
		tmp[i].wait = rides[i].wait;
	}
	sort(tmp, tmp + N, [](const Tmp& lhs, const Tmp& rhs) {return (lhs.wait != rhs.wait ? lhs.wait > rhs.wait : lhs.id > rhs.id); });

	for (int i = 0; i < mCount; ++i) {
		mId[i] = tmp[i].id;
		mWait[i] = tmp[i].wait;
	}
	return;
}
