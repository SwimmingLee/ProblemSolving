
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT		100
#define CMD_ADD			200
#define CMD_MOVETYPE	300
#define CMD_MOVENAME	400
#define CMD_DELETENAME	500
#define CMD_COUNTBOOK	600

#define MAX_N			5

#define MAX_NAME_LEN	7
#define MAX_TAG_LEN		4

extern void init(int M);
extern void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection);
extern int  moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo);
extern void moveName(char mName[MAX_NAME_LEN], int mSection);
extern void deleteName(char mName[MAX_NAME_LEN]);
extern int  countBook(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection);

static bool run()
{
	int  Q;
	int  cmd, M, mTypeNum, mSection, mFrom, mTo;
	char mName[MAX_NAME_LEN], mType[MAX_TAG_LEN], mTypes[MAX_N][MAX_TAG_LEN];

	int  ret, ans;

	scanf("%d", &Q);

	bool okay = false;

	for (int q = 0; q <= Q; ++q)
	{
		scanf("%d", &cmd);

		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d", &M);
			init(M);
			okay = true;
			break;
		case CMD_ADD:
			scanf("%s %d", mName, &mTypeNum);
			for (int i = 0; i < mTypeNum; ++i)
				scanf("%s", mTypes[i]);
			scanf("%d", &mSection);
			if (okay)
				add(mName, mTypeNum, mTypes, mSection);
			break;
		case CMD_MOVETYPE:
			scanf("%s %d %d", mType, &mFrom, &mTo);
			if (okay)
				ret = moveType(mType, mFrom, mTo);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_MOVENAME:
			scanf("%s %d", mName, &mSection);
			if (okay)
				moveName(mName, mSection);
			break;
		case CMD_DELETENAME:
			scanf("%s", mName);
			if (okay)
				deleteName(mName);
			break;
		case CMD_COUNTBOOK:
			scanf("%d", &mTypeNum);
			for (int i = 0; i < mTypeNum; ++i)
				scanf("%s", mTypes[i]);
			scanf("%d", &mSection);
			if (okay)
				ret = countBook(mTypeNum, mTypes, mSection);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

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
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

#define MAX_N			5

#define MAX_NAME_LEN	7
#define MAX_TAG_LEN		4

#define MAX_BOOK		(1<<17)
#define MAX_TYPE		(1<<18) //175,616

void mstrcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != '\0') ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
	int c = 0;
	while (str1[c] != '\0' && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

unordered_map<string, int> bookMap;
int bookCnt;
unordered_map<string, int> typeMap;
int typeCnt;
int searchCnt;
int been[MAX_BOOK];
int section[MAX_BOOK];
vector<int> typeId2bookId[MAX_TYPE];

void init(int M)
{
	bookCnt = typeCnt = 0;
	searchCnt = 0;
	bookMap.clear();
	typeMap.clear();
	for (int i = 0; i < MAX_TYPE; ++i)
		typeId2bookId[i].clear();
	for (int i = 0; i < MAX_BOOK; ++i) {
		been[i] = -1;
		section[i] = -1;
	}
}

void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
	int bookId = bookCnt++;
	bookMap[string(mName)] = bookId;
	section[bookId] = mSection;

	for (int i = 0; i < mTypeNum; ++i) {
		int typeId;
		if (typeMap.find(string(mTypes[i])) != typeMap.end()) {
			typeId = typeMap[string(mTypes[i])];
		}
		else {
			typeId = typeCnt++;
			typeMap[string(mTypes[i])] = typeId;
		}
		typeId2bookId[typeId].push_back(bookId);
	}

}

int moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo)
{
	int typeId;
	if (typeMap.find(string(mType)) != typeMap.end()) {
		typeId = typeMap[string(mType)];
	}
	else {
		return 0;
	}


	int ans = 0;
	for (int i = 0; i < typeId2bookId[typeId].size(); ++i) {
		int bookId = typeId2bookId[typeId][i];
		if (section[bookId] == mFrom) {
			ans++;
			section[bookId] = mTo;
		}
	}
	return ans;
}

void moveName(char mName[MAX_NAME_LEN], int mSection)
{
	int bookId = bookMap[string(mName)];
	section[bookId] = mSection;
}

void deleteName(char mName[MAX_NAME_LEN])
{
	int bookId = bookMap[string(mName)];
	section[bookId] = -1;
}

int countBook(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
	int searchIdx = searchCnt++;
	int ans = 0;
	for (int i = 0; i < mTypeNum; ++i) {
		int typeId;
		if (typeMap.find(string(mTypes[i])) != typeMap.end()) {
			typeId = typeMap[string(mTypes[i])];
		}
		else {
			continue;
		}
		
		for (int j = 0; j < typeId2bookId[typeId].size(); ++j) {
			int bookId = typeId2bookId[typeId][j];
			if (been[bookId] != searchIdx && section[bookId] == mSection) {
				ans++;
				been[bookId] = searchIdx;
			}
		}
	}
	return ans;
}