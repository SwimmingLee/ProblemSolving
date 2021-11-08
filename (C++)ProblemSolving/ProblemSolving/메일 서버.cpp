
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define INIT         0
#define SENDMAIL     1
#define GETCOUNT     2
#define DELETEMAIL   3
#define SEARCHMAIL   4

extern void init(int N, int K);
extern void sendMail(char subject[], int uID, int cnt, int rIDs[]);
extern int getCount(int uID);
extern int deleteMail(int uID, char subject[]);
extern int searchMail(int uID, char text[]);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#define MAX_WORD 10000
static char Word[MAX_WORD][11];

static int N, W, minR, maxR, SW;

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 214013 + 2531011;
	return (mSeed >> 16) & 0x7FFF;
}

static void make_string(int seed)
{
	mSeed = seed;

	for (int i = 0; i < W; ++i) {
		int length = 5 + pseudo_rand() % 6;
		for (int k = 0; k < length; ++k) {
			Word[i][k] = 'a' + pseudo_rand() % 26;
		}
		Word[i][length] = '\0';
	}
}

static void send_mail(int seed)
{
	char str[200];
	int pos = 0;

	mSeed = seed;

	int wcnt = 1 + pseudo_rand() % SW;
	for (int i = 0; i < wcnt; ++i) {
		int widx = pseudo_rand() % W;
		for (int k = 0; k < 10; ++k) {
			if (Word[widx][k] == '\0') break;
			str[pos++] = Word[widx][k];
		}
		str[pos++] = ' ';
	}
	str[pos - 1] = '\0';

	int uid = pseudo_rand() % N;
	int rcnt = minR + pseudo_rand() % (maxR - minR + 1);
	int rids[50];
	for (int i = 0; i < rcnt; ++i) {
		rids[i] = pseudo_rand() % N;
	}

	sendMail(str, uid, rcnt, rids);
}

static int delete_mail(int uid, int seed)
{
	char str[200];
	int pos = 0;

	mSeed = seed;

	int wcnt = 1 + pseudo_rand() % SW;
	for (int i = 0; i < wcnt; ++i) {
		int widx = pseudo_rand() % W;
		for (int k = 0; k < 10; ++k) {
			if (Word[widx][k] == '\0') break;
			str[pos++] = Word[widx][k];
		}
		str[pos++] = ' ';
	}
	str[pos - 1] = '\0';

	return deleteMail(uid, str);
}

static int run(int answer)
{
	int Q, K, cmd, sample, seed, param1, param2, ret;
	char str[30];

	scanf("%d %d %d %d", &Q, &sample, &N, &K);
	if (sample == 0) {
		scanf("%d %d %d %d %d", &W, &minR, &maxR, &SW, &seed);
		make_string(seed);
	}

	init(N, K);

	for (int i = 1; i < Q; ++i) {
		if (answer == 0)
			printf("[ASDF]\n");
		scanf("%d", &cmd);
		switch (cmd) {
		case SENDMAIL:
			if (sample == 1) {
				int uid, rcnt;
				int rids[10];
				scanf("%s %d %d", str, &uid, &rcnt);
				for (int k = 0; k < rcnt; ++k) scanf("%d", &rids[k]);
				for (int k = 0; k < 30; ++k) {
					if (str[k] == '\0') break;
					if (str[k] == '_') str[k] = ' ';
				}
				sendMail(str, uid, rcnt, rids);
			}
			else {
				scanf("%d", &seed);
				send_mail(seed);
			}
			break;
		case GETCOUNT:
			scanf("%d %d", &param1, &param2);
			ret = getCount(param1);
			if (ret != param2)
				answer = 0;
			if (answer == 0)
				printf("[ASDF]\n");
			break;
		case DELETEMAIL:
			if (sample == 1) {
				int uid;
				scanf("%d %s %d", &param1, str, &param2);
				for (int k = 0; k < 30; ++k) {
					if (str[k] == '\0') break;
					if (str[k] == '_') str[k] = ' ';
				}
				ret = deleteMail(param1, str);
				if (ret != param2)
					answer = 0;
				if (answer == 0)
					printf("[ASDF]\n");
			}
			else {
				scanf("%d %d %d", &param1, &seed, &param2);
				ret = delete_mail(param1, seed);
				if (ret != param2)
					answer = 0;
				if (answer == 0)
					printf("[ASDF]\n");
			}
			break;
		case SEARCHMAIL:
			scanf("%d %s %d", &param1, str, &param2);
			ret = searchMail(param1, str);
			if (ret != param2)
				answer = 0;
			if (answer == 0)
				printf("[ASDF]\n");
			break;
		default:
			break;
		}
	}

	return answer;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T, Mark;
	scanf("%d %d", &T, &Mark);

	for (int tc = 1; tc <= T; tc++) {
		printf("#%d %d\n", tc, run(Mark));
	}

	return 0;
}





/*
* #include <string>
#include <unordered_map>
using namespace std;
 
#define QSIZE 512
 
int n, k;
unordered_map<string, int> title;
struct Mail {
    int q[QSIZE];
    int cnt;
    int head;
    int tail;
};
Mail mailbox[1000];
int mail[10000][10];
int mail_word_cnt[10000];
 
inline int HASH(char* mWord) {
    unsigned long h = 5381;
    int c;
    char* p = mWord;
    while (c = *p++) {
        h = (((h << 5) + h) + c);
    }
    return h;
}
 
void init(int N, int K) {
    n = N;
    k = K;
    title.clear();
 
    for (int i = 0; i < n; ++i) {
        mailbox[i].cnt = 0;
        mailbox[i].head = 0;
        mailbox[i].tail = 0;
    }
}
 
void parse(char subject[], int index) {
    mail_word_cnt[index] = 0;
    int start = 0;
    for (int i = 0; subject[i]; ++i) {
        if (subject[i] == ' ') {
            subject[i] = 0;
            int h = HASH(subject + start);
            mail[index][mail_word_cnt[index]++] = h;
            start = i + 1;
        }
    }
    int h = HASH(subject + start);
    mail[index][mail_word_cnt[index]++] = h;
}
 
void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
    int index;
    if (title.count(subject)) index = title[subject];
    else {
        index = title[subject] = title.size();
        parse(subject, index);
    }
 
    for (int i = 0; i < cnt; ++i) {
        Mail& box = mailbox[rIDs[i]];
        if (box.cnt < k) {
            box.q[box.tail] = index;
            box.tail = (box.tail + 1) % QSIZE;
            box.cnt++;
        }
        else {
            box.q[box.tail] = index;
            box.head = (box.head + 1) % QSIZE;
            box.tail = (box.tail + 1) % QSIZE;
        }
    }
}
 
int getCount(int uID) {
    return mailbox[uID].cnt;
}
 
int deleteMail(int uID, char subject[]) {
    int index;
    if (title.count(subject)) index = title[subject];
    else {
        index = title[subject] = title.size();
        parse(subject, index);
    }
 
    int ret = 0;
    Mail& box = mailbox[uID];
    for (int i = box.head, i2 = box.head; i != box.tail; i = (i + 1) % QSIZE) {
        if (box.q[i] == index) {
            ret++;
            box.cnt--;
        }
        else {
            box.q[i2] = box.q[i];
            i2 = (i2 + 1) % QSIZE;
        }
    }
    box.tail = (box.head + box.cnt) % QSIZE;
    return ret;
}
 
int searchMail(int uID, char text[]) {
    int w = HASH(text);
 
    int ret = 0;
    Mail& box = mailbox[uID];
    for (int i = box.head; i != box.tail; i = (i + 1) % QSIZE) {
        for (int j = 0; j < mail_word_cnt[box.q[i]]; ++j) {
            if (mail[box.q[i]][j] == w) {
                ret++;
                break;
            }
        }
    }
    return ret;
}
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
using namespace std;

#define MAX_USER	1001
#define MAX_WORD	10001
#define MAX_MAIL	10001
#define QUEUE_SZ	301

int curStep;
int wordCnt;
struct Trie {
	int number;
	int step;
	Trie* child[26];
	Trie() {
		step = -1;
		number = -1;
		for (int i = 0; i < 26; ++i)
			child[i] = nullptr;
	}
	~Trie() {
		for (int i = 0; i < 26; ++i) {
			if (child[i] != nullptr)
				delete child[i];
		}
	}
	int insert(char* str) {
		int c = *str;
		if (c == 0) {
			if (number != -1 && step == curStep)
				return number;

			step = curStep;
			number = wordCnt++;
			return number;
		}
		c = c % 26;
		if (child[c] == nullptr)
			child[c] = new Trie;
		return child[c]->insert(str + 1);
	}
	int search(char* str) {
		int c = *str;
		if (c == 0) {
			if (step == curStep)
				return number;
			else
				return -1;
		}
		c = c % 26;
		if (child[c] == nullptr)
			return -1;
		return child[c]->search(str + 1);
	}
};


int n;
int k;

Trie root;

int mailCnt;
int mailWords[MAX_MAIL][10];
int mailWordSz[MAX_MAIL];
unordered_map<string, int> titleTable;

int userMailBox[MAX_USER][QUEUE_SZ];
int userMailHead[MAX_USER];
int userMailTail[MAX_USER];
int userMailCnt[MAX_USER];

void init(int N, int K)
{
	n = N;
	k = K;

	curStep++;
	wordCnt = 0;

	titleTable.clear();
	mailCnt = 0;

	for (int i = 0; i < MAX_USER; ++i) {
		userMailHead[i] = userMailTail[i] = 0;
		userMailCnt[i] = 0;
	}

}

int getMailID() {
	return mailCnt++;
}

void sendMail(char subject[], int uID, int cnt, int rIDs[])
{
	int mID;
	
	// 중복된 메일 제목인지 검사하기
	if (titleTable.find(subject) == titleTable.end()) {
		mID = titleTable[subject] = getMailID();
		int mSz = 0;
		// 제목 안에 포함된 단어 파싱하기
		char c;
		char* keyword = subject;
		char* prev = keyword;
		while (c = *keyword++) {
			if (c == ' ') {
				*prev = '\0';
				mailWords[mID][mSz++] = root.insert(subject);
				subject = keyword;
			}
			prev = keyword;
		}
		mailWords[mID][mSz++] = root.insert(subject);
		mailWordSz[mID] = mSz;
	}
	else {
		mID = titleTable[subject];
	}

	// 메일박스에다가 메일 담기
	for (int i = 0; i < cnt; ++i) {
		int ruID = rIDs[i];
		userMailBox[ruID][userMailTail[ruID]] = mID;

		if (userMailCnt[ruID] < k) {
			userMailCnt[ruID]++;
			userMailTail[ruID] = (userMailTail[ruID] + 1) % QUEUE_SZ;
		}
		else {
			userMailHead[ruID] = (userMailHead[ruID] + 1) % QUEUE_SZ;
			userMailTail[ruID] = (userMailTail[ruID] + 1) % QUEUE_SZ;
		}
	}
}

int getCount(int uID)
{
	return userMailCnt[uID];
}

int deleteMail(int uID, char subject[])
{
	int answer = 0;
	
	// 제목이랑 일치하는 메일이 있는지 확인하기
	int mID;
	if (titleTable.find(subject) == titleTable.end())
		return 0;

	mID = titleTable[subject];

	// mailbox 순회하면서 같은 메일이 있나 검사하기
	int cur, prev;
	for (cur = userMailHead[uID], prev = userMailHead[uID]; cur != userMailTail[uID]; cur = (cur + 1) % QUEUE_SZ) {
		// 메일 삭제
		if (userMailBox[uID][cur] == mID) {
			answer++;
			userMailCnt[uID]--;
		}
		else {
			userMailBox[uID][prev] = userMailBox[uID][cur];
			prev = (prev + 1) % QUEUE_SZ;
		}
	}
	userMailTail[uID] = prev;

	return answer;
}

int searchMail(int uID, char text[])
{
	int answer = 0;
	int key = root.search(text);
	if (key == -1) return 0;

	// mailbox 순회하면서 단어가 겹치는 메일이 있나 검사하기
	int cur;
	for (cur = userMailHead[uID]; cur != userMailTail[uID]; cur = (cur + 1) % QUEUE_SZ) {
		int mID = userMailBox[uID][cur];
		for (int i = 0; i < mailWordSz[mID]; ++i) {
			if (mailWords[mID][i] == key) {
				answer++;
				break;
			}
		}
	}
	return answer;
}