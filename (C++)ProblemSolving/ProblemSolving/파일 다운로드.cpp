

#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <list>
#include <cstring>
using namespace std;

const int INF = 987654321;
#define MAX_NODE  10001

int hCnt;
int been[MAX_NODE];
list<int> edges[MAX_NODE];
unordered_map<string, int> hTable;
string nodeName[MAX_NODE];
//list<int> sysFiles;

int getHashID(const string& s) {
	if (hTable.find(s) == hTable.end()) {
		nodeName[hCnt] = s;
		hTable[s] = hCnt++;
	}
	return hTable[s];
}

void init() {
	hCnt = 0;
	hTable.clear();
	//sysFiles.clear();
	getHashID("/");
	for (int i = 0; i < MAX_NODE; i++) {
		edges[i].clear();
		been[i] = INF;
	}
}
void makeDir(char path[], char dirname[]) {
	int p = getHashID(string(path));
	int c = getHashID(string(path) + string(dirname) + "/");
	
	edges[p].push_back(c);
	edges[c].push_back(p);

	been[c] = been[p] + 1;
}

void updateDist(int n) {
	queue<int> q;
	q.push(n);

	while (!q.empty()) {
		int file = q.front(); q.pop();

		for (auto nextFile : edges[file]) {
			if (been[file] + 1 < been[nextFile]) {
				been[nextFile] = been[file] + 1;
				q.push(nextFile);
			}
		}
	}
}

void makeLink(char path1[], char path2[]) {
	int n1 = getHashID(string(path1));
	int n2 = getHashID(string(path2));

	edges[n2].push_back(n1);
	updateDist(n2);
}

void makeSystemFile(char path[]) {
	int p = getHashID(string(path));
	//sysFiles.push_back(p);
	been[p] = 0;
	updateDist(p);
}


void findDownloadDir(char downloadPath[]) {
	int downloadFile = 0;
	for (int i = 1; i < hCnt; ++i) {
		if (been[downloadFile] < been[i])
			downloadFile = i;
	}

	strcpy(downloadPath, nodeName[downloadFile].c_str());
}