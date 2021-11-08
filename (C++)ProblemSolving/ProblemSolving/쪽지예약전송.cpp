#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT				100
#define CMD_SEND_MESSAGE		200
#define CMD_RETRIEVE_SENTBOX	300
#define CMD_RETRIEVE_INBOX		400
#define CMD_READ_MESSAGE		500
#define CMD_DELETE_MESSAGE		600

#define MAXM					3

extern void init(int N);
extern void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp);
extern int  retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM]);
extern int  retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM]);
extern int  readMessage(int cTimestamp, int uID, int mID);
extern int  deleteMessage(int cTimestamp, int uID, int mID);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run()
{
	int Q, N;
	int cTimestamp, scheduleTimestamp;
	int uID, uID1, uID2, mID;
	int ret, ans;
	int mIDList[MAXM], uIDList[MAXM], readList[MAXM];
	int mIDList_a[MAXM], uIDList_a[MAXM], readList_a[MAXM];

	bool okay = false;

	scanf("%d", &Q);

	for (int q = 0; q <= Q; ++q)
	{
		int op;
		scanf("%d", &op);

		switch (op)
		{
		case CMD_INIT:
			scanf("%d", &N);
			init(N);
			okay = true;
			break;
		case CMD_SEND_MESSAGE:
			scanf("%d %d %d %d %d", &cTimestamp, &uID1, &uID2, &mID, &scheduleTimestamp);
			if (okay)
				sendMessage(cTimestamp, uID1, uID2, mID, scheduleTimestamp);
			break;
		case CMD_RETRIEVE_SENTBOX:
			scanf("%d %d", &cTimestamp, &uID);
			if (okay)
				ret = retrieveSentbox(cTimestamp, uID, mIDList, uIDList, readList);
			scanf("%d", &ans);
			for (int i = 0; i < ans; ++i)
				scanf("%d %d %d", &mIDList_a[i], &uIDList_a[i], &readList_a[i]);
			if (ret != ans)
			{
				printf("여기군\n");
				okay = false;
			}
			else
			{
				for (int i = 0; i < ans; ++i) {
					//printf("%d %d ", readList[i], readList_a[i]);
					if (mIDList[i] != mIDList_a[i]
						|| uIDList[i] != uIDList_a[i] || readList[i] != readList_a[i]) {
						okay = false;
						printf("여기을수도?\n");
					}
				}
			}
			break;
		case CMD_RETRIEVE_INBOX:
			scanf("%d %d", &cTimestamp, &uID);
			if (okay)
				ret = retrieveInbox(cTimestamp, uID, mIDList, uIDList, readList);
			scanf("%d", &ans);
			for (int i = 0; i < ans; ++i)
				scanf("%d %d %d", &mIDList_a[i], &uIDList_a[i], &readList_a[i]);
			if (ret != ans)
			{
				printf("보낸메일함\n");
				okay = false;
			}
			else
			{
				for (int i = 0; i < ans; ++i)
					if (mIDList[i] != mIDList_a[i]
						|| uIDList[i] != uIDList_a[i] || readList[i] != readList_a[i]) {
						okay = false;
						printf("보낸 메일함22\n");
					}
			}
			break;
		case CMD_READ_MESSAGE:
			scanf("%d %d %d", &cTimestamp, &uID, &mID);
			if (okay)
				ret = readMessage(cTimestamp, uID, mID);
			scanf("%d", &ans);
			if (ret != ans) {
				printf("잘못읽?\n");
				okay = false;
			}
			break;
		case CMD_DELETE_MESSAGE:
			scanf("%d %d %d", &cTimestamp, &uID, &mID);
			if (okay)
				ret = deleteMessage(cTimestamp, uID, mID);
			scanf("%d", &ans);
			if (ret != ans) {
				printf("잘못지?\n");
				okay = false;
			}
			break;
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("C:\\Users\\swimm\\Downloads\\input10 (5).txt", "r", stdin);

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
#include <vector>
#include <queue>
using namespace std;

#define MAXM	3
#define MAX_MAIL	100001
#define MAX_USER	1001

struct Mail{
	int from;
	int to;
	bool isRead;
	bool isFromDeleted;
	bool isToDeleted;
	bool isSent;
} mail[MAX_MAIL];

priority_queue<pair<int, int>> reservedPQ;
vector<int> inbox[MAX_USER];
vector<int> sentbox[MAX_USER];

void init(int N)
{
	while(!reservedPQ.empty())
		reservedPQ.pop();

	for (int i = 1; i <= N; ++i) {
		inbox[i].clear();
		sentbox[i].clear();
	}

	for (int i = 1; i < MAX_MAIL; ++i) {
		mail[i].from = -1;
		mail[i].to = -1;
		mail[i].isRead = false;
		mail[i].isFromDeleted = false;
		mail[i].isToDeleted = false;
		mail[i].isSent = false;
	}
}
void updateMail(int currentTime) {
	while (!reservedPQ.empty()) {
		int reservedTime = -reservedPQ.top().first;
		if (currentTime < reservedTime) break;

		int mID = -reservedPQ.top().second;
		reservedPQ.pop();
		if (mail[mID].isFromDeleted) continue;

		mail[mID].isSent = true;
		inbox[mail[mID].to].push_back(mID);
	}
}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
	updateMail(cTimestamp);
	mail[mID].from = uID1;
	mail[mID].to = uID2;

	reservedPQ.push({ -scheduleTimestamp, -mID });
	sentbox[uID1].push_back(mID);
}


int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
	updateMail(cTimestamp);

	int i = 0;
	vector<int> st;
	while (!sentbox[uID].empty() && i < 3) {
		int mID = sentbox[uID].back();
		sentbox[uID].pop_back();
		
		if (mail[mID].isFromDeleted) continue;

		mIDList[i] = mID;
		uIDList[i] = mail[mID].to;
		readList[i] = mail[mID].isRead;
		st.push_back(mID);
		i += 1;
	}

	while (!st.empty()) {
		int mID = st.back();
		st.pop_back();

		sentbox[uID].push_back(mID);
	}

	return i;
}



int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
	updateMail(cTimestamp);

	int i = 0;
	vector<int> st;
	while (!inbox[uID].empty() && i < 3) {
		int mID = inbox[uID].back();
		inbox[uID].pop_back();

		if (mail[mID].isToDeleted) continue;

		mIDList[i] = mID;
		uIDList[i] = mail[mID].from;
		readList[i] = mail[mID].isRead;
		st.push_back(mID);
		i += 1;
	}
	while (!st.empty()) {
		int mID = st.back();
		st.pop_back();

		inbox[uID].push_back(mID);
	}

	return i;
}

int readMessage(int cTimestamp, int uID, int mID)
{
	updateMail(cTimestamp);

	int ableRead = false;
	if (mail[mID].from == uID) {
		ableRead = !mail[mID].isFromDeleted;
	}
	else if (mail[mID].to == uID && mail[mID].isSent) {
		ableRead = !mail[mID].isToDeleted;
		if (ableRead)
			mail[mID].isRead = true;
	}
 	return ableRead;
}

int deleteMessage(int cTimestamp, int uID, int mID)
{
	updateMail(cTimestamp);

	int ableDelete = false;
	if (mail[mID].from == uID) {
		ableDelete = !mail[mID].isFromDeleted;
		mail[mID].isFromDeleted = true;
	}
	else if (mail[mID].to == uID && mail[mID].isSent) {
		ableDelete = !mail[mID].isToDeleted;
		mail[mID].isToDeleted = true;
	}

	return ableDelete;
}