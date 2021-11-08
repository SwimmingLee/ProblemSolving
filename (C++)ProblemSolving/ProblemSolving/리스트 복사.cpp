#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

#define MAX_NODE 110000

unordered_map<string, int> hTable;
int hCntReal; // 진또배기 리스트 인데스 
int hCntCopy; // 카피 리스트 인덱스

int arr[10][200000];

int parent[MAX_NODE];
bool hasChild[MAX_NODE];
vector<pair<int, int>> updatedElements[MAX_NODE];

int disjoint[MAX_NODE];
int find(int u) {
	if (disjoint[u] == u) return u;
	return disjoint[u] = find(disjoint[u]);
}
void merge(int u, int v) {
	u = find(u);
	v = find(v); // v == find(v) 인 것들만 들어오는게 보증됨
	disjoint[u] = v;
}

int makeHashRealID(char name[]) {
	string s(name);
	int ID = hCntReal;
	hTable[s] = hCntReal++;
	return ID;
}
int makeHashCopyID(char name[]) {
	string s(name);
	int ID = hCntCopy;
	hTable[s] = hCntCopy++;
	return ID;
}

void init() {
	hCntReal = 0;
	hCntCopy = 11;

	for (int i = 0; i < MAX_NODE; ++i) {
		disjoint[i] = i;
		hasChild[i] = false;
		updatedElements[i].clear();
	}
}

void makeList(char name[], int len, int list[]) {
	int ID = makeHashRealID(name);
	for (int i = 0; i < len; ++i) {
		arr[ID][i] = list[i];
	}
	// 진또배기 리스트는 분별하기
	parent[ID] = -1;
}

void copyList(char srcName[], char desName[], bool isDeepCopy) {
	int parentID = hTable[string(srcName)];
	parentID = find(parentID);

	if (isDeepCopy) {
		int childId = makeHashCopyID(desName);
		parent[childId] = parentID;
		hasChild[parentID] = true;
	}
	else {
		hTable[string(desName)] = parentID;
	}
}

void updateElement(char name[], int idx, int value) {
	int ID = hTable[string(name)];
	ID = find(ID);

	if (!hasChild[ID]) {
		// 진또배기 리스트라면 바로 수정
		if (parent[ID] == -1) {
			arr[ID][idx] = value;
		}
		else {
			updatedElements[ID].emplace_back(idx, value);
		}
	}
	else {
		int childID = hCntCopy++;
		merge(ID, childID); // 해쉬에서 ID를 찾아도 childID로 매핑할 수 있게끔
		parent[childID] = ID;
		updatedElements[childID].emplace_back(idx, value);
	}
}

int element(char name[], int idx) {
	int ID = hTable[string(name)];
	ID = find(ID);

	int answer;
	bool isFind = false;
	while (parent[ID] != -1) {
		
		for (int i = (int)updatedElements[ID].size() - 1; i >= 0; --i) {
			if (updatedElements[ID][i].first == idx) {
				answer = updatedElements[ID][i].second;
				isFind = true;
				break;
			}
		}
		if (isFind) break;
		ID = parent[ID];
	}
	if (!isFind) {
		answer = arr[ID][idx];
	}

	return answer;
}