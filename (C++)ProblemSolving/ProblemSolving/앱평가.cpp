#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

static int mstrcmp(const char str1[], const char str2[])
{
	int c = 0;
	while (str1[c] != 0 && str1[c] == str2[c])
		++c;
	return str1[c] - str2[c];
}

static void mstrcpy(char dest[], const char src[])
{
	int i = 0;
	while (src[i] != '\0') { dest[i] = src[i]; i++; }
	dest[i] = src[i];
}

static const int CMD_INIT = 100;
static const int CMD_ADDRATING = 200;
static const int CMD_DELETERATING = 300;
static const int CMD_BANUSER = 400;
static const int CMD_SORTBYSCORE = 500;
static const int CMD_SORTBYNUMBER = 600;

static const int MAXL = 16;

struct RESULT {
	char mApp[5][MAXL];
};

extern void init(int, const char[][MAXL]);
extern void addRating(int, const char[MAXL], int);
extern void deleteRating(int, const char[MAXL]);
extern void banUser(int);
extern RESULT sortByScore();
extern RESULT sortByNumber();

static char applist[10000][MAXL];
static int mSeed;
static char anslist[10000][MAXL];

static int pseudoRand()
{
	mSeed = (mSeed * 214013 + 2531011) & 0xFFFFFFFF;
	return (mSeed >> 16) & 0x7FFF;
}

static void makeApp(int num)
{
	for (int i = 0; i < num; i++) {
		int len = 5 + pseudoRand() % 11;
		for (int j = 0; j < len; j++) {
			applist[i][j] = 'A' + pseudoRand() % 26;
		}
		applist[i][len] = 0;
	}
}

static int run(void)
{
	int ret = 0;
	int query_cnt, cmd;
	int appNum;
	int mUser, mApp, mScore;
	RESULT user;
	int ans;

	scanf("%d %d %d", &query_cnt, &mSeed, &appNum);
	makeApp(appNum);
	for (int i = 0; i < appNum; i++)
		mstrcpy(anslist[i], applist[i]);

	for (int q = 0; q < query_cnt; q++)
	{
		scanf("%d", &cmd);
		switch (cmd) {
		case CMD_INIT:
			init(appNum, applist);
			ret = 1;
			break;
		case CMD_ADDRATING:
			scanf("%d %d %d", &mUser, &mApp, &mScore);
			addRating(mUser, applist[mApp], mScore);
			break;
		case CMD_DELETERATING:
			scanf("%d %d", &mUser, &mApp);
			deleteRating(mUser, applist[mApp]);
			break;
		case CMD_BANUSER:
			scanf("%d", &mUser);
			banUser(mUser);
			break;
		case CMD_SORTBYSCORE:
			user = sortByScore();
			for (int i = 0; i < 5; i++) {
				scanf("%d", &ans);
				if (mstrcmp(user.mApp[i], anslist[ans]))
					ret = 0;
			}
			break;
		case CMD_SORTBYNUMBER:
			user = sortByNumber();
			for (int i = 0; i < 5; i++) {
				scanf("%d", &ans);
				if (mstrcmp(user.mApp[i], anslist[ans]))
					ret = 0;
			}
			break;
		default:
			ret = 0;
			break;
		}
	}

	return ret;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("C:\\Users\\swimm\\Downloads\\sample_input25 (2).txt", "r", stdin);
	int tc, MARK;

	scanf("%d %d", &tc, &MARK);

	for (int t = 1; t <= tc; t++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", t, score);
	}

	return 0;
}


#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;
//static const int MAXL = 16;
const int MAXUSER = 10000;
const int MAXAPP = 10000;

//struct RESULT {
//	char mApp[5][MAXL];
//};


int appCnt;

struct AppRating {
	int appIdx;
	int ratingCnt;
	int totalScore;
};

struct Heap {
	AppRating arr[MAXAPP+1];
	int heapIdx[MAXAPP+1]; // appIdxÀÇ heapIdx ¹ÝÈ¯
	bool (*compare)(const AppRating&, const AppRating&);

	Heap(bool (*_compare)(const AppRating&, const AppRating&)) {
		compare = _compare;
	}

	inline int parent(int idx) {
		return (idx - 1) >> 1;
	}
	inline int leftChild(int idx) {
		return (idx << 1) + 1;
	}
	inline int rightChild(int idx) {
		return (idx << 1) + 2;
	}

	void init() {
		for (register int i = 0; i < appCnt; ++i) {
			heapIdx[i] = i;
			arr[i].appIdx = i;
			arr[i].ratingCnt = 0;
			arr[i].totalScore = 0;
		}
	}
	
	AppRating pop() {
		register int cur = 0;
		AppRating ret = arr[cur];
		heapIdx[ret.appIdx] = -1;
		appCnt -= 1;

		arr[cur] = arr[appCnt];
		heapIdx[arr[cur].appIdx] = cur;

		while (leftChild(cur) < appCnt) {

			int child;
			if (leftChild(cur) == appCnt - 1) {
				child = leftChild(cur);
			}
			else if (compare(arr[leftChild(cur)], arr[rightChild(cur)])) {
				child = leftChild(cur);
			}
			else {
				child = rightChild(cur);
			}

			if (compare(arr[cur], arr[child])) {
				break;
			}

			swap(arr[cur], arr[child]);
			swap(heapIdx[arr[cur].appIdx], heapIdx[arr[child].appIdx]);
			cur = child;
		}
		return ret;
	}

	void push(AppRating rating) {
		register int cur = appCnt++;
		arr[cur] = rating;
		heapIdx[arr[cur].appIdx] = cur;

		while (cur != 0 && compare(arr[cur], arr[parent(cur)])) {
			swap(arr[cur], arr[parent(cur)]);
			swap(heapIdx[arr[cur].appIdx], heapIdx[arr[parent(cur)].appIdx]);
			cur = parent(cur);
		}
	}

	void update(int appIdx, int addRatingCnt, int addScore) {
		register int cur = heapIdx[appIdx];
		
		arr[cur].ratingCnt += addRatingCnt;
		arr[cur].totalScore += addScore;

		if (cur != 0 && compare(arr[cur], arr[parent(cur)])) {
			while (cur != 0 && compare(arr[cur], arr[parent(cur)])) {
				swap(arr[cur], arr[parent(cur)]);
				swap(heapIdx[arr[cur].appIdx], heapIdx[arr[parent(cur)].appIdx]);
				cur = parent(cur);
			}
		}
		else {
			while (leftChild(cur) < appCnt) {
				int child;
				if (leftChild(cur) == appCnt - 1) {
					child = leftChild(cur);
				}
				else if (compare(arr[leftChild(cur)], arr[rightChild(cur)])) {
					child = leftChild(cur);
				}
				else {
					child = rightChild(cur);
				}

				if (compare(arr[cur], arr[child])) {
					break;
				}

				swap(arr[cur], arr[child]);
				swap(heapIdx[arr[cur].appIdx], heapIdx[arr[child].appIdx]);
				cur = child;
			}
		}
	}
};


bool ratingCntCompare(const AppRating& lhs, const AppRating& rhs) {
	return lhs.ratingCnt != rhs.ratingCnt ? lhs.ratingCnt > rhs.ratingCnt : lhs.appIdx < rhs.appIdx;
}
bool scoreCompare(const AppRating& lhs, const AppRating& rhs) {
	int lhsScore = lhs.ratingCnt == 0 ? 0 : (lhs.totalScore * 10) / lhs.ratingCnt;
	int rhsScore = rhs.ratingCnt == 0 ? 0 : (rhs.totalScore * 10) / rhs.ratingCnt;
	return lhsScore != rhsScore ? lhsScore > rhsScore : lhs.appIdx < rhs.appIdx;
}

Heap scoreHeap(scoreCompare);
Heap ratingHeap(ratingCntCompare);
bool isBanUser[MAXUSER + 1];
unordered_map<string, int> appIdxTable;
unordered_map<int, int> userRating[MAXUSER + 1]; // appIdx, score
string appName[MAXAPP];

void init(int N, const char mApp[][MAXL])
{
	appCnt = N;
	appIdxTable.clear();
	for (register int i = 0; i < N; ++i) {
		appName[i] = mApp[i];
	}
	sort(appName, appName + N);
	for (register int i = 0; i < N; ++i) {
		appIdxTable[appName[i]] = i;
		
	}

	for (register int i = 0; i <= MAXUSER; ++i) {
		userRating[i].clear();
		isBanUser[i] = false;
	}
	scoreHeap.init();
	ratingHeap.init();
}

void addRating(int mUser, const char mApp[MAXL], int mScore)
{
	if (isBanUser[mUser]) return;

	register int appIdx = appIdxTable[mApp];

	int preScore = -1;
	if (userRating[mUser].find(appIdx) != userRating[mUser].end())
		preScore = userRating[mUser][appIdx];
	userRating[mUser][appIdx] = mScore;

	// heapify
	if (preScore == -1) {
		scoreHeap.update(appIdx, 1, mScore);
		ratingHeap.update(appIdx, 1, mScore);
	}
	else {
		scoreHeap.update(appIdx, 0, mScore - preScore);
		ratingHeap.update(appIdx, 0, mScore - preScore);
	}

}

void deleteRating(int mUser, const char mApp[MAXL])
{
	register int appIdx = appIdxTable[string(mApp)];
	
	int preScore = userRating[mUser][appIdx];
	userRating[mUser].erase(userRating[mUser].find(appIdx));

	// heapify
	scoreHeap.update(appIdx, -1, -preScore);
	ratingHeap.update(appIdx, -1, -preScore);

}

void banUser(int mUser)
{
	if (isBanUser[mUser]) return;
	isBanUser[mUser] = true;
	for (auto it = userRating[mUser].begin(); it != userRating[mUser].end(); ++it) {
		// heapify
		int appIdx = (*it).first;
		int preScore = (*it).second;
		scoreHeap.update(appIdx, -1, -preScore);
		ratingHeap.update(appIdx, -1, -preScore);

	}
}

AppRating highScoreAppRating[5];
RESULT sortByScore()
{
	RESULT ret = {};
	for (int i = 0; i < 5; ++i) {
		highScoreAppRating[i] = scoreHeap.pop();
		strcpy(ret.mApp[i], appName[highScoreAppRating[i].appIdx].c_str());
	}
	for (int i = 0; i < 5; ++i) {
		scoreHeap.push(highScoreAppRating[i]);
	}
	
	return ret;
}

RESULT sortByNumber()
{
	RESULT ret = {};
	for (int i = 0; i < 5; ++i) {
		highScoreAppRating[i] = ratingHeap.pop();
		strcpy(ret.mApp[i], appName[highScoreAppRating[i].appIdx].c_str());
	}
	for (int i = 0; i < 5; ++i) {
		ratingHeap.push(highScoreAppRating[i]);
	}

	return ret;
}