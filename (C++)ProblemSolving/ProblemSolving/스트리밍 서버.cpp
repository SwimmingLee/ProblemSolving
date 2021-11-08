
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXLength (10000)
#define MAXServer (10)

int upos[MAXLength];
int spos[MAXServer];
pair<int,int> usDiff[MAXLength][MAXServer]; // ����-������ �Ÿ�, uid
int userver[MAXLength]; // ������ �����ִ� ����
int sviewer[MAXServer];
int spaceLen;
int nserver;
int viewLimit;

struct Node {
	int longestServer;
	int uid;
	Node* next;
} a[MAXLength+2];
int acnt = 0;
Node* head;
Node* tail;

Node* myalloc() {
	return &a[acnt++];
}

void choiceServer(int uid) {
	for (int i = 0; i < nserver; ++i) {
		int sid = usDiff[uid][i].second;
		if (sviewer[sid] < viewLimit) {
			sviewer[sid]++;
			userver[uid] = sid;

			break;
		}
	}
}

void init(int L, int N, int C, int axis[MAXServer])
{
	acnt = 0;
	head = myalloc();
	tail = myalloc();
	head->next = tail;

	spaceLen = L;
	nserver = N;
	viewLimit = C;
	for (int i = 0; i < N; ++i) {
		spos[i] = axis[i];
		sviewer[i] = 0;
	}
}

int add_user(int uid, int axis)
{
	// ������ ������ �Ÿ� �����ϱ�
	upos[uid] = axis;
	for (int i = 0; i < nserver; ++i) {
		int diff = abs(spos[i] - axis);
		diff = min(diff, spaceLen - diff);
		usDiff[uid][i] = { diff, i };
	}
	sort(usDiff[uid], usDiff[uid] + nserver);

	for (int i = 0; i < nserver; ++i) {
		sviewer[i] = 0;
	}

	// ������ ����Ʈ�� �߰��ϱ�
	int longestServer = usDiff[uid][nserver - 1].first;
	Node* user = myalloc();
	user->longestServer = longestServer;
	user->uid = uid;

	Node* prev = head;
	bool isAdd = false;
	for (Node* iter = head->next; iter != tail; iter = iter->next) {
		if (!isAdd && iter->longestServer < longestServer) {
			prev->next = user;
			user->next = iter;
			isAdd = true;

			iter = user;
		}

		choiceServer(iter->uid);

		prev = iter;
	}
	if (!isAdd) {
		prev->next = user;
		user->next = tail;

		// ����Ʈ�� �������鼭 ���� ���Ҵ�
		choiceServer(uid);

	}

	return userver[uid];
}

int remove_user(int uid)
{
	for (int i = 0; i < nserver; ++i) {
		sviewer[i] = 0;
	}

	int ret = userver[uid];

	// ������ ����Ʈ���� �����ϱ�
	Node* prev = head;
	bool isChecked = false;
	for (Node* iter = head->next; iter != tail; iter = iter->next) {
		if (!isChecked && iter->uid == uid) {
			prev->next = iter->next;
			isChecked = true;
			continue;
		}
		choiceServer(iter->uid);

		prev = iter;
	}

	return ret;
}

int get_users(int sid)
{
	return sviewer[sid];
}
