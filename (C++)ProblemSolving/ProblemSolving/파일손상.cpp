#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

enum COMMAND {
	CMD_ADD = 1,
	CMD_MOVE,
	CMD_INFECT,
	CMD_RECOVER,
	CMD_REMOVE
};

extern void init();
extern int cmdAdd(int, int, int);
extern int cmdMove(int, int);
extern int cmdInfect(int);
extern int cmdRecover(int);
extern int cmdRemove(int);

static int run(int score) {
	int N;
	scanf("%d", &N);

	int pre_cmd;
	for (int i = 0; i < N; i++) {
		int cmd;
		int ret = 0;
		scanf("%d", &cmd);
		switch (cmd) {
		case CMD_ADD: {
			int id, pid, fileSize;
			scanf("%d%d%d", &id, &pid, &fileSize);
			ret = cmdAdd(id, pid, fileSize);
			break;
		}
		case CMD_MOVE: {
			int id, pid;
			scanf("%d%d", &id, &pid);
			ret = cmdMove(id, pid);
			break;
		}
		case CMD_INFECT: {
			int id;
			scanf("%d", &id);
			ret = cmdInfect(id);
			break;
		}
		case CMD_RECOVER: {
			int id;
			scanf("%d", &id);
			ret = cmdRecover(id);
			break;
		}
		case CMD_REMOVE: {
			int id;
			scanf("%d", &id);
			ret = cmdRemove(id);
			break;
		}
		}

		int checkSum;
		scanf("%d", &checkSum);
		if (ret != checkSum) {
			printf("여기서 틀렸음! %d %d\n", cmd, pre_cmd);
			score = 0;
		}
		pre_cmd = cmd;
	}
	return score;
}

int main() {
	setbuf(stdout, NULL);
	freopen("C:\\Users\\swimm\\Downloads\\sample_input25 (1).txt", "r", stdin);

	int TC, score;
	scanf("%d%d", &TC, &score);
	for (int t = 1; t <= TC; t++) {
		init();
		int ret = run(score);
		printf("#%d %d\n", t, ret);
	}

	return 0;
}


#include <iostream>
#include <map>
#include <list>
using namespace std;

int totalFileSize;
int fileCnt;
map<int, int> vIDtable;
int vIDCnt;

struct Node {
	int vpID;
	int pureSize;
	int fileSize;
	int fileCnt;
	list<int> children;
} Pool[10002];

void init() {
	vIDtable.clear();

	totalFileSize = 0;
	fileCnt = 0;
	vIDCnt = 0;

	int rootID = vIDtable[10000] = vIDCnt++;
	Node& root = Pool[rootID];
	root.pureSize = 0;
	root.fileSize = 0;
	root.fileCnt = 0;
	root.vpID = -1;
	root.children.clear();
}

void addFile(int vID, int fileSize, int fileCnt) {
	if (vID == -1)
		return;
	Node& cur = Pool[vID];
	cur.fileSize += fileSize;
	cur.fileCnt += fileCnt;
	addFile(cur.vpID, fileSize, fileCnt);
}

void removeFile(int vID, int fileSize, int fileCnt) {
	if (vID == -1)
		return;
	Node& cur = Pool[vID];
	cur.fileSize -= fileSize;
	cur.fileCnt -= fileCnt;
	
	removeFile(cur.vpID, fileSize, fileCnt);
}

int cmdAdd(int newID, int pID, int fileSize) {
	int vpID = vIDtable[pID];
	int vnID = vIDtable[newID] = vIDCnt++;

	// 새로운 파일 정보 업데이트 
	Node& child = Pool[vnID];
	child.pureSize = fileSize;
	child.fileSize = fileSize;
	child.fileCnt = fileSize > 0 ? 1 : 0;
	child.vpID = vpID;
	child.children.clear();

	// 부모 노드에서 자식 파일 정보 추가
	Node& parent = Pool[vpID];
	parent.children.push_back(vnID);

	// 상위 디렉터리의 총 파일크기, 사이즈 갱신
	addFile(vpID, fileSize, child.fileCnt);

	// totalFileSize, fileCnt 갱신
	totalFileSize += fileSize;
	if (fileSize)
		fileCnt += 1;

	//cout << "[] " << parent.fileSize << '\n';
	return parent.fileSize;
}

int cmdMove(int tID, int pID) {
	int vpID = vIDtable[pID];
	int vtID = vIDtable[tID];

	// vtID의 부모 노드에서 vtID 삭제
	Node& target = Pool[vtID];
	Node& preParent = Pool[target.vpID];
	for (auto it = preParent.children.begin(); it != preParent.children.end(); ++it) {
		if ((*it) == vtID) {
			preParent.children.erase(it);
			break;
		}
	}
	removeFile(target.vpID, target.fileSize, target.fileCnt);

	// 타켓 부모 정보 변경
	target.vpID = vpID;
	// 부모 이동
	Node& parent = Pool[vpID];
	parent.children.push_back(vtID);
	addFile(vpID, target.fileSize, target.fileCnt);


	//cout << "{} " << parent.fileSize << '\n';
	return parent.fileSize;
}

int infect(int vID, int addFileSize) {
	Node& cur = Pool[vID];

	int sum = 0;
	for (auto it = cur.children.begin(); it != cur.children.end(); ++it) {
		sum += infect(*it, addFileSize);
	}

	if (cur.pureSize != 0) {
		cur.fileSize += addFileSize;
		totalFileSize += addFileSize;

		return addFileSize;
	}
	else {
		cur.fileSize += sum;

		return sum;
	}
}

int cmdInfect(int tID) {
	if (fileCnt == 0) return 0;

	int vtID = vIDtable[tID];
	Node& target = Pool[vtID];

	int preFileSize = target.fileSize;
	int addFileSize = totalFileSize / fileCnt;
	infect(vtID, addFileSize);
	int fileSize = target.fileSize;

	addFile(target.vpID, fileSize - preFileSize, 0);

	return fileSize;
}

int recover(int vID) {
	Node& cur = Pool[vID];

	int sum = 0;
	for (auto it = cur.children.begin(); it != cur.children.end(); ++it) {
		sum += recover(*it);
	}

	// 파일이면
	if (cur.pureSize != 0) {
		int diff = cur.fileSize - cur.pureSize;

		cur.fileSize -= diff;
		totalFileSize -= diff;

		return diff;
	}
	// 디렉터리이면
	else {
		cur.fileSize -= sum;

		return sum;
	}
}

int cmdRecover(int tID) {
	int vtID = vIDtable[tID];
	Node& target = Pool[vtID];

	int preFileSize = target.fileSize;
	recover(vtID);
	int fileSize = target.fileSize;

	removeFile(target.vpID, preFileSize - fileSize, 0);

	return fileSize;

}

int cmdRemove(int tID) {
	int vtID = vIDtable[tID];
	Node& target = Pool[vtID];
	if (target.vpID != -1) {
		Node& parent = Pool[target.vpID];

		for (auto it = parent.children.begin(); it != parent.children.end(); ++it) {
			if ((*it) == vtID) {
				parent.children.erase(it);
				break;
			}
		}

		removeFile(target.vpID, target.fileSize, target.fileCnt);
	}
	totalFileSize -= target.fileSize;
	fileCnt -= target.fileCnt;
	
	int ret = target.fileSize;
	
	target.children.clear();
	target.fileSize = 0;
	target.pureSize = 0;
	target.fileCnt = 0;

	return ret;
}
