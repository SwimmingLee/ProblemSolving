#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define BAR_LEN 5

#define CMD_INIT 100
#define CMD_MAKEWALL 200
#define CMD_MATCHPIECE 300

extern void init();
extern void makeWall(int mHeights[BAR_LEN]);
extern int matchPiece(int mHeights[BAR_LEN]);

static bool run()
{
	int N;
	int cmd;
	int heights[BAR_LEN];

	int ret = 0;
	int ans = 0;
	scanf("%d", &N);

	scanf("%d", &cmd);
	bool okay = false;
	if (cmd == CMD_INIT)
	{
		init();
		okay = true;
	}

	for (int turn = 0; turn < N - 1; turn++)
	{
		scanf("%d", &cmd);
		for (int i = 0; i < BAR_LEN; i++)
		{
			scanf("%d", &heights[i]);
		}

		switch (cmd)
		{
		case CMD_MAKEWALL:
			makeWall(heights);
			break;
		case CMD_MATCHPIECE:
			ret = matchPiece(heights);
			scanf("%d", &ans);
			if (ans != ret)
				okay = false;
			break;
		}
	}
	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("C:\\Users\\swimm\\Downloads\\sample_25_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);
	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}


#define WALL_SZ		5

struct Node {
	int height;
	Node* next;
	Node* prev;
} Pool[100000];
int pCnt;

Node* head;
Node* tail;
int blockCnt;
int fail[WALL_SZ-1];
int blockShape[20][20][20][20];

void init()
{
	blockCnt = 0;
	pCnt = 0;
	head = &Pool[pCnt++];
	tail = &Pool[pCnt++];
	head->next = tail;
	tail->prev = head;

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				for (int l = 0; l < 20; ++l) {
					blockShape[i][j][k][l] = 0;
				}
			}
		}
	}
}

void addBlock(Node* block) {

	if (block == head) return;

	for (int i = 0; i < 3 && block->prev != head; ++i) {
		block = block->prev;
	}

	int idx = 0;
	int diff[11];
	for (Node* cur = block; cur->next != tail && idx < 7; cur = cur->next, idx++) {
		diff[idx] = cur->height - cur->next->height;

		if (idx >= 3) {
			blockShape[diff[idx - 3] + 10][diff[idx - 2] + 10][diff[idx - 1] + 10][diff[idx] + 10]++;
		}
	}
}

void deleteBlock(Node* block) {
	int idx = 0;
	int diff[11];
	for (Node* cur = block; cur->next != tail && idx < 8; cur = cur->next, idx++) {
		diff[idx] = cur->height - cur->next->height;

		if (idx >= 3) {
			blockShape[diff[idx - 3] + 10][diff[idx - 2] + 10][diff[idx - 1] + 10][diff[idx] + 10]--;
		}
	}

	idx = 0;
	for (Node* cur = block; cur->prev != head && idx < 4; cur = cur->prev, idx++) {
		diff[idx] = -(cur->height - cur->prev->height);

		if (idx >= 3) {
			blockShape[diff[idx] + 10][diff[idx-1] + 10][diff[idx-2] + 10][diff[idx-3] + 10]--;
		}
	}
}


void makeWall(int mHeights[WALL_SZ])
{
	for (int i = 0; i < WALL_SZ; ++i) {
		Node* block = &Pool[pCnt++];
		block->height = mHeights[i];

		block->prev = head;
		block->next = head->next;

		head->next->prev = block;
		head->next = block;

		blockCnt++;
	}

	//addBlock(head->next);
	int idx = 0;
	int diff[11];
	for (Node* cur = head->next; cur->next != tail && idx < 8; cur = cur->next, idx++) {
		diff[idx] = cur->height - cur->next->height;

		if (idx >= 3) {
			blockShape[diff[idx - 3] + 10][diff[idx - 2] + 10][diff[idx - 1] + 10][diff[idx] + 10]++;
		}
	}
}



int matchPiece(int mHeights[WALL_SZ])
{
	int diff[WALL_SZ - 1];
	for (int i = 0; i < WALL_SZ - 1; ++i) {
		diff[i] = -(mHeights[i] - mHeights[i+1]);
	}

	if (blockShape[diff[0] + 10][diff[1] + 10][diff[2] + 10][diff[3] + 10] <= 0) {
		//printf("¾øÀ½\n");
		return -1;
	}

	int j = 0;
	fail[0] = 0;
	for (int i = 1; i < WALL_SZ - 1; ++i) {
		while (j > 0 && diff[i] != diff[j]) {
			j = fail[j - 1];
		}
		if (diff[i] == diff[j]) {
			fail[i] = ++j;
		}
		else {
			fail[i] = 0;
		}
	}

	j = 0;
	int idx = 0;
	for (Node* cur = head->next; cur != tail; cur = cur->next, idx++) {
		int i = cur->height - cur->next->height;
		while (j > 0 && i != diff[j]) {
			j = fail[j - 1];
		}
		if (i == diff[j]) {
			++j;
			if (j == WALL_SZ-1) {
				j = 0;
				Node* realNext = cur->next->next;
				Node* realPrev = cur->prev->prev->prev->prev;

				deleteBlock(realPrev->next);

				realPrev->next = realNext;
				realNext->prev = realPrev;

				addBlock(realPrev);

				blockCnt -= 5;
				return blockCnt - idx - 1 + 5;
			}
		}
	}

	return -1;
}