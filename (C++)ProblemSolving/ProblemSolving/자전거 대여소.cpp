#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT	100
#define CMD_ADD		200
#define CMD_BUY		300
#define CMD_RENT	400
#define CMD_RETURN	500

#define MAXN		100
#define MAXL		8

extern void init(int N, int durableTime, int deliveryTimes[MAXN]);
extern void addBicycle(int cTimestamp, int pID, int bicycleNum);
extern void buyTicket(int cTimestamp, char uName[MAXL], int validTime);
extern int rentBicycle(int cTimestamp, char uName[MAXL], int pID);
extern int returnBicycle(int cTimestamp, char uName[MAXL], int pID);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 246247151 + 9543169;
	return (mSeed >> 16) & 0x7FFFFFFF;
}

static bool run()
{
	int Q;
	int N, durableTime, deliveryTimes[MAXN], cTimestamp, pID, bicycleNum, validTime;
	int res = -1, ans;

	char uName[MAXL];

	int dT;

	scanf("%d %d", &Q, &mSeed);

	bool okay = false;

	if (mSeed == 0)
	{
		for (int q = 0; q <= Q; ++q)
		{
			int cmd;
			scanf("%d", &cmd);

			switch (cmd)
			{
			case CMD_INIT:
				scanf("%d %d", &N, &durableTime);
				for (int i = 0; i < N; ++i)
					scanf("%d", &deliveryTimes[i]);
				init(N, durableTime, deliveryTimes);
				okay = true;
				break;
			case CMD_ADD:
				scanf("%d %d %d", &cTimestamp, &pID, &bicycleNum);
				if (okay)
					addBicycle(cTimestamp, pID, bicycleNum);
				break;
			case CMD_BUY:
				scanf("%d %s %d", &cTimestamp, uName, &validTime);
				if (okay)
					buyTicket(cTimestamp, uName, validTime);
				break;
			case CMD_RENT:
				scanf("%d %s %d", &cTimestamp, uName, &pID);
				if (okay)
					res = rentBicycle(cTimestamp, uName, pID);
				scanf("%d", &ans);
				if (res != ans)
					okay = false;
				break;
			case CMD_RETURN:
				scanf("%d %s %d", &cTimestamp, uName, &pID);
				if (okay)
					res = returnBicycle(cTimestamp, uName, pID);
				scanf("%d", &ans);
				if (res != ans)
					okay = false;
				break;
			}
		}
	}
	else
	{
		scanf("%d", &dT);

		cTimestamp = 0;

		for (int q = 0; q <= Q; ++q)
		{
			int cmd;
			scanf("%d", &cmd);

			switch (cmd)
			{
			case CMD_INIT:
				scanf("%d %d", &N, &durableTime);
				for (int i = 0; i < N; ++i)
					scanf("%d", &deliveryTimes[i]);
				init(N, durableTime, deliveryTimes);
				okay = true;
				break;
			case CMD_ADD:
				cTimestamp += pseudo_rand() % dT + 1;
				scanf("%d %d", &pID, &bicycleNum);
				if (okay)
					addBicycle(cTimestamp, pID, bicycleNum);
				break;
			case CMD_BUY:
				cTimestamp += pseudo_rand() % dT + 1;
				scanf("%s %d", uName, &validTime);
				if (okay)
					buyTicket(cTimestamp, uName, validTime);
				break;
			case CMD_RENT:
				cTimestamp += pseudo_rand() % dT + 1;
				scanf("%s %d", uName, &pID);
				if (okay)
					res = rentBicycle(cTimestamp, uName, pID);
				scanf("%d", &ans);
				if (res != ans)
					okay = false;
				break;
			case CMD_RETURN:
				cTimestamp += pseudo_rand() % dT + 1;
				scanf("%s %d", uName, &pID);
				if (okay)
					res = returnBicycle(cTimestamp, uName, pID);
				scanf("%d", &ans);
				if (res != ans)
					okay = false;
				break;
			}
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("C:\\Users\\swimm\\downloads\\sample_input25 (3).txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;

		printf("#%d %d\n", tc, score);
	}

	return 0;
}

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

#define MAXUSER		10000
#define MAXN		100
#define MAXL		8

priority_queue<int> station[MAXN];
priority_queue<pair<int, int>> newBicycle; // time, pID

struct User {
	int purchaseTime;
	int validTime;
	bool hasBycle;
	int rentTime;
	int bycleRunningTime;
} users[MAXUSER];
unordered_map<string, int> uIdTable;
int uCnt;
int durableTime;
int deliveryTimes[MAXN];

int getuID(char* name) {
	int cnt = uIdTable.count(name);
	if (cnt == 0) {
		uIdTable[name] = uCnt++;
	}
	return uIdTable[name];
}

void init(int N, int _durableTime, int _deliveryTimes[MAXN])
{
	for (int i = 0; i < N; ++i) {
		deliveryTimes[i] = _deliveryTimes[i];
		while (!station[i].empty())
			station[i].pop();
	}
	for (int i = 0; i < MAXUSER; ++i) {
		users[i].hasBycle = false;
		users[i].purchaseTime = 0;
		users[i].validTime = 0;
	}
	durableTime = _durableTime;
	uCnt = 0;
	while(!newBicycle.empty())
		newBicycle.pop();
	uIdTable.clear();
}

void addBicycle(int cTimestamp, int pID, int bicycleNum)
{
	for (int i = 0; i < bicycleNum; ++i) {
		station[pID].push(0);
	}
}

void buyTicket(int cTimestamp, char uName[MAXL], int validTime)
{
	int uID = getuID(uName);
	if (users[uID].purchaseTime + users[uID].validTime < cTimestamp) {
		users[uID].purchaseTime = cTimestamp;
		users[uID].validTime = validTime;
	}
	else {
		users[uID].validTime += validTime;
	}
}

int rentBicycle(int cTimestamp, char uName[MAXL], int pID)
{
	while (!newBicycle.empty() && -newBicycle.top().first <= cTimestamp) {
		int stationID = newBicycle.top().second;
		newBicycle.pop();
		station[stationID].push(0);
	}

	int uID = getuID(uName);
	if (users[uID].hasBycle) {
		return -1;
	}
	else if (station[pID].empty()) {
		return -1;
	}
	else if (users[uID].purchaseTime + users[uID].validTime <= cTimestamp) {
		return -1;
	}

	int ret = -station[pID].top();
	station[pID].pop();

	users[uID].hasBycle = true;
	users[uID].rentTime = cTimestamp;
	users[uID].bycleRunningTime = ret;

	return ret;
}

int returnBicycle(int cTimestamp, char uName[MAXL], int pID)
{
	int uID = getuID(uName);

	if (!users[uID].hasBycle) {
		return -1;
	}
	
	int ret;
	ret = max(0, cTimestamp - (users[uID].purchaseTime + users[uID].validTime - 1));

	int runningTime = (cTimestamp - users[uID].rentTime) + users[uID].bycleRunningTime;
	if (runningTime > durableTime) {
		newBicycle.push({ -(cTimestamp + deliveryTimes[pID]), pID });
	}
	else {
		station[pID].push(-runningTime);
	}

	users[uID].hasBycle = false;

	return ret;
}