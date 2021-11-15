#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_MERGE 300
#define CMD_MOVE 400
#define CMD_RECRUIT 500

extern void init(int mNum);
extern void destroy();
extern int addDept(char mUpperDept[], char mNewDept[], int mNum);
extern int mergeDept(char mDept1[], char mDept2[]);
extern int moveEmployee(char mDept[], int mDepth, int mNum);
extern void recruit(int mDeptNum, int mNum);

/////////////////////////////////////////////////////////////////////////
static int Score;

static void cmd_init()
{
	int mNum;
	scanf("%d", &mNum);
	init(mNum);
}

static void cmd_destroy()
{
	destroy();
}

static void cmd_add()
{
	char mUpperDept[10], mNewDept[10];
	int mNum;
	scanf("%s %s %d", mUpperDept, mNewDept, &mNum);
	int result = addDept(mUpperDept, mNewDept, mNum);
	int check;
	scanf("%d", &check);
	if (result != check)
		Score = 0;
}

static void cmd_merge()
{
	char mDept1[10], mDept2[10];
	scanf("%s %s", mDept1, mDept2);
	int result = mergeDept(mDept1, mDept2);
	int check;
	scanf("%d", &check);
	if (result != check)
		Score = 0;
}

static void cmd_move()
{
	char mDept[10];
	int mDepth, mNum;
	scanf("%s %d %d", mDept, &mDepth, &mNum);
	int result = moveEmployee(mDept, mDepth, mNum);
	int check;
	scanf("%d", &check);
	if (result != check)
		Score = 0;
}

static void cmd_recruit()
{
	int deptNum, mNum;
	scanf("%d %d", &deptNum, &mNum);
	recruit(deptNum, mNum);
}

static void run()
{
	int N;
	scanf("%d", &N);
	Score = 100;
	for (int i = 0; i < N; ++i)
	{
		int cmd;
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT: cmd_init(); break;
		case CMD_ADD: cmd_add(); break;
		case CMD_MOVE: cmd_move(); break;
		case CMD_MERGE: cmd_merge(); break;
		case CMD_RECRUIT: cmd_recruit(); break;
		default: Score = 0; break;
		}
	}
	cmd_destroy();
}

int main()
{
	setbuf(stdout, NULL);
	freopen("C:\\Users\\swimm\\Downloads\\sample_input (11).txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		run();
		if (Score == 100) printf("#%d %d\n", tc, MARK);
		else printf("#%d %d\n", tc, 0);
	}
	return 0;
}

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define MAX_NODE    10001
typedef pair<int, int> pii;
struct Node {
    int parent;
    int children[11];
    int childrenNum;
    int num;
} tree[MAX_NODE];
int pCnt;

bool isAlive[MAX_NODE];
unordered_map<string, int> tTable;

string debug_table[MAX_NODE];

void init(int mNum)
{
    for (int i = 0; i < MAX_NODE; ++i) {
        isAlive[i] = false;
    }
    tTable.clear();
    pCnt = 0;

    debug_table[pCnt] = "root";
    int rootIdx = tTable["root"] = pCnt++;
    isAlive[rootIdx] = true;
    Node& root = tree[rootIdx];
    root.parent = -1;
    root.childrenNum = 0;
    root.num = mNum;

}

void destroy()
{

}

int getDepth(int curIdx) {
    int ret = 0;
    while (tree[curIdx].parent != -1) {
        curIdx = tree[curIdx].parent;
        ret++;

    }

    return ret;
}


int addDept(char mUpperDept[], char mNewDept[], int mNum)
{
    // mUpperDepth 존재 확인 - isAlive를 쓸지 고민...
    if (tTable.find(mUpperDept) == tTable.end() || tTable.find(mNewDept) != tTable.end()) {
        return -1;
    }

    int upperIdx = tTable[mUpperDept];
    int parentDepth = getDepth(upperIdx);
    Node& parent = tree[upperIdx];
    // mUpperDepth가 5차 부서인지, mNum이하인지, 10개 하위부서가 있는지 검사
    if (parentDepth == 5 || parent.num <= mNum || parent.childrenNum == 10) {
        return -1;
    }

    debug_table[pCnt] = mNewDept;
    int newIdx = tTable[mNewDept] = pCnt++;
    isAlive[newIdx] = true;
    parent.num -= mNum;
    parent.children[parent.childrenNum++] = newIdx;

    Node& child = tree[newIdx];
    child.parent = upperIdx;
    child.childrenNum = 0;
    child.num = mNum;

    //cout << "[AddDept] " << tree[upperIdx].num << '\n';
    return tree[upperIdx].num;
}


int getChildDepth(int curIdx) {
    int ret = 0;
    for (int i = 0; i < tree[curIdx].childrenNum; ++i) {
        ret = max(ret, getChildDepth(tree[curIdx].children[i]) + 1);
    }
    return ret;
}

int mergeDept(char mDept1[], char mDept2[])
{
    // Dept1, Dept2 존재 검사
    if (tTable.find(mDept1) == tTable.end() || tTable.find(mDept2) == tTable.end()) {
        return -1;
    }
    int dept1Idx = tTable[mDept1];
    int dept2Idx = tTable[mDept2];

    // Dept1이, Dept2의 하위부서인지 검사하기
    int curIdx = dept1Idx;
    while (curIdx != -1) {
        if (curIdx == dept2Idx) return -1;
        curIdx = tree[curIdx].parent;
    }

    // maxChildDepth 구하기
    int dept1Depth = getDepth(dept1Idx);
    int dept2Depth = getDepth(dept2Idx);
    Node& dept1 = tree[dept1Idx];
    Node& dept2 = tree[dept2Idx];

    int addDepth = getChildDepth(dept2Idx);

    if ((dept1Depth + addDepth > 5) ||
        (dept1.childrenNum + dept2.childrenNum > 10 && dept2.parent != dept1Idx) ||
        (dept1.childrenNum + dept2.childrenNum > 11 && dept2.parent == dept1Idx)
        )
    {
        return -1;
    }

    dept1.num += dept2.num;
    for (int i = 0; i < dept2.childrenNum; ++i) {
        dept1.children[dept1.childrenNum] = dept2.children[i];
        dept1.childrenNum += 1;
        tree[dept2.children[i]].parent = dept1Idx;
    }

    // dept2의 부모에서 dept2 자르기
    for (int i = 0; i < tree[dept2.parent].childrenNum; ++i) {
        if (tree[dept2.parent].children[i] == dept2Idx) {
            tree[dept2.parent].children[i] = tree[dept2.parent].children[--tree[dept2.parent].childrenNum];
            break;
        }

    }
    //tree[dept2.parent].childrenNum -= 1;
    isAlive[dept2Idx] = false;
    tTable.erase(mDept2);

    return tree[dept1Idx].num;
}

void moveEmployee(int deptIdx, int curIdx, int depth, int num) {
    if (depth < 0) return;

    if (deptIdx != curIdx) {
        if (tree[curIdx].num > num) {
            tree[deptIdx].num += num;
            tree[curIdx].num -= num;
        }
        else {
            tree[deptIdx].num += tree[curIdx].num - 1;
            tree[curIdx].num = 1;
        }
    }

    for (int i = 0; i < tree[curIdx].childrenNum; ++i) {
        moveEmployee(deptIdx, tree[curIdx].children[i], depth - 1, num);
    }
}


int moveEmployee(char mDept[], int mDepth, int mNum)
{
    // Dept 존재 검사
    if (tTable.find(mDept) == tTable.end()) {
        return -1;
    }

    int deptIdx = tTable[mDept];
    moveEmployee(deptIdx, deptIdx, mDepth, mNum);

    return tree[deptIdx].num;
}

vector<pair<int, int>> recuitDept;
void recruit(int mDeptNum, int mNum)
{
    // root부터 순회하면서, num이 가장 낮으면서 idx가 가장 높은거 찾기
    recuitDept.clear();
    for (int i = 0; i < pCnt; ++i) {
        if (isAlive[i]) {
            recuitDept.emplace_back(tree[i].num, i);
        }
    }

    sort(begin(recuitDept), end(recuitDept), [](const pii& lhs, const pii& rhs) {
        return lhs.first != rhs.first ? lhs.first < rhs.first : lhs.second > rhs.second; });

    for (int i = 0; i < mDeptNum; ++i) {
        tree[recuitDept[i].second].num += mNum;
    }

}