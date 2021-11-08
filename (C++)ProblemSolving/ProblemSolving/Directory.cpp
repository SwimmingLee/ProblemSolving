#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include<stdio.h>

#define CMD_MKDIR 1
#define CMD_RM 2
#define CMD_CP 3
#define CMD_MV 4
#define CMD_FIND 5

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

extern void init(int n);
extern void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]);
extern void cmd_rm(char path[PATH_MAXLEN + 1]);
extern void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]);
extern void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]);
extern int cmd_find(char path[PATH_MAXLEN + 1]);

static bool run(int m) {

	bool isAccepted = true;
	int cmd;
	char name[NAME_MAXLEN + 1];
	char path1[PATH_MAXLEN + 1], path2[PATH_MAXLEN + 1];

	while (m--) {

		scanf("%d", &cmd);

		if (cmd == CMD_MKDIR) {
			scanf("%s%s", path1, name);
			cmd_mkdir(path1, name);
		}
		else if (cmd == CMD_RM) {
			scanf("%s", path1);
			cmd_rm(path1);
		}
		else if (cmd == CMD_CP) {
			scanf("%s%s", path1, path2);
			cmd_cp(path1, path2);
		}
		else if (cmd == CMD_MV) {
			scanf("%s%s", path1, path2);
			cmd_mv(path1, path2);
		}
		else {
			int ret;
			int answer;

			scanf("%s", path1);
			ret = cmd_find(path1);
			scanf("%d", &answer);

			isAccepted &= (ret == answer);
		}
	}

	return isAccepted;
}

int main(void) {

	int test, T;
	int n, m;

	freopen("C:\\Users\\swimm\\Downloads\\sample_input_10 (1).txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &T);

	for (test = 1; test <= T; ++test) {

		scanf("%d%d", &n, &m);

		init(n);

		if (run(m)) {
			printf("#%d 100\n", test);
		}
		else {
			printf("#%d 0\n", test);
		}
	}

	return 0;
}

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <map>
using namespace std;

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

unordered_map<string, int> nTable;
int nCnt;

int getNameID(const char* str) {
	auto it = nTable.find(str);
	if (it != nTable.end()) {
		return (*it).second;
	}
	else {
		nTable[str] = nCnt;
		return nCnt++;
	}
}

struct Node {
	int nameID;
	Node* parent;
	vector<Node*> children;
	int num;
	Node* find(int nameID) {
		for (int i = 0; i < children.size(); ++i) {
			if (children[i]->nameID == nameID) {
				return children[i];
			}
		}
	}
} pool[50001];

int pCnt;
Node* root;
void init(int n) {
	nCnt = 0;
	pCnt = 0;
	
	nTable.clear();

	root = &pool[pCnt++];
	root->nameID = getNameID("/");
	root->children.clear();
	root->num = 0;
}

Node* pathDir(char* path) {
	char c;
	Node* cur = root;
	path += 1;
	char* name = path;
	char* prev = path;
	while (c = *(path++)) {
		if (c == '/') {
			*prev = '\0';
			int nameID = getNameID(name);
			for (int i = 0; i < cur->children.size(); ++i) {
				if (nameID == cur->children[i]->nameID) {
					cur = cur->children[i];
					break;
				}
			}
			name = path;
		}
		prev = path;
	}
	return cur;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* parentDir = pathDir(path);

	Node* newDir = &pool[pCnt++];
	newDir->nameID = getNameID(name);
	newDir->parent = parentDir;
	newDir->children.clear();
	newDir->num = 0;
	parentDir->children.push_back(newDir);

	while (parentDir != root) {
		parentDir->num += 1;
		parentDir = parentDir->parent;
	}
	root->num += 1;
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	Node* dir = pathDir(path);
	vector<Node*>::iterator it;
	for (it = dir->parent->children.begin(); it != dir->parent->children.end(); it++) {
		if ((*it)->nameID == dir->nameID) {
			dir->parent->children.erase(it);
			break;
		}
	}

	int removedNum = dir->num;
	while (dir != root) {
		dir->num -= removedNum+1;
		dir = dir->parent;
	}
	root->num -= removedNum+1;
}

int cp(Node* src, Node* dst) {
	int ret = 0;

	Node* findDir = nullptr; 
	if (findDir == nullptr) {
		Node* newDir = &pool[pCnt++];
		newDir->nameID = src->nameID;
		newDir->parent = dst;
		newDir->num = src->num;
		newDir->children.clear();
		findDir = newDir;

		dst->children.push_back(newDir);
		ret++;
	}
	

	for (int i = 0; i < src->children.size(); ++i) {	
		ret += cp(src->children[i], findDir);
	}
	return ret;
}
void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* srcDir = pathDir(srcPath);
	Node* dstDir = pathDir(dstPath);
	int n = cp(srcDir, dstDir);

	int addNum = n;
	while (dstDir != root) {
		dstDir->num += addNum;
		dstDir = dstDir->parent;
	}
	root->num += addNum;
}

void mv(Node* src, Node* dst) {
	vector<Node*>::iterator it;
	for (it = src->parent->children.begin(); it != src->parent->children.end(); it++) {
		if ((*it)->nameID == src->nameID) {
			src->parent->children.erase(it);
			break;
		}
	}

	Node* curDir = nullptr; 
	if (curDir == nullptr) {
		src->parent = dst;
		dst->children.push_back(src);
	}
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* srcDir = pathDir(srcPath);
	Node* dir = srcDir->parent;
	Node* dstDir = pathDir(dstPath);
	mv(srcDir, dstDir);

	int removedNum = srcDir->num;
	while (dir != root) {
		dir->num -= (removedNum + 1);
		dir = dir->parent;
	}
	while (dstDir != root) {
		dstDir->num += removedNum + 1;
		dstDir = dstDir->parent;
	}
}


int cmd_find(char path[PATH_MAXLEN + 1]) {
	Node* dir = pathDir(path);
	return dir->num;
}