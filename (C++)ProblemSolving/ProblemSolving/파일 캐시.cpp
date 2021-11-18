#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N);
extern int access(int fileId, int fileSize);
extern int usage();

/////////////////////////////////////////////////////////////////////////

#define CMD_INIT 1
#define CMD_ACCESS 2
#define CMD_USAGE 3

static bool run() {
	int q;
	scanf("%d", &q);

	int n, fileId, fileSize;
	int cmd, ans, ret = 0;
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
		case CMD_INIT:
			scanf("%d", &n);
			init(n);
			okay = true;
			break;
		case CMD_ACCESS:
			scanf("%d %d %d", &fileId, &fileSize, &ans);
			ret = access(fileId, fileSize);
			if (ans != ret) {
				printf("누구냐!! %d %d", ret, ans);
				okay = false;
			}
			break;
		case CMD_USAGE:
			ret = usage();
			scanf("%d", &ans);
			if (ans != ret) {
				//printf("총합 오류\n");
				okay = false;
			}
			break;
		default:
			okay = false;
			break;
		}
	}
	return okay;
}

int main() {
	setbuf(stdout, NULL);
	freopen("C:\\Users\\swimm\\Downloads\\sample_25_input (2).txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}
#define MAX_NUM     20017

#define INSERT(n, nn)   do {    \
    n->next = nn;                \
    n->prev = n->next->prev;   \
    n->prev->next = n;            \
    n->next->prev = n;            \
} while(0)                      

#define DELETE(n) do {          \
    n->prev->next = n->next;   \
    n->next->prev = n->prev;   \
} while(0)                      

struct FILE {
	int     id, key, start, size;
	FILE* prev, * next;
} file[MAX_NUM];

struct EMPTY {
	int     start, size;
	EMPTY* prev, * next;
} empty[MAX_NUM];

struct HASH {
	int     fileId;
	FILE* fp;
} hash[MAX_NUM];


FILE* fHead, * fTail;
EMPTY* eHead, * eTail;
int     fIdx, eIdx;
int     usingSize;

int getKey(int fileId)
{
	int h = fileId % MAX_NUM;
	int cnt = MAX_NUM;

	while ((hash[h].fileId != -1) && cnt--)
	{
		if (hash[h].fileId == fileId)   return h;
		h = (h + 1) % MAX_NUM;
	}

	return -1;
}

int addKey(int fileId)
{
	int h = fileId % MAX_NUM;

	while (hash[h].fileId != -1)
	{
		h = (h + 1) % MAX_NUM;
	}

	hash[h].fileId = fileId;

	return h;
}

void delKey(int key)
{
	hash[key].fileId = -1;
}

void init(int N) {

	fIdx = eIdx = usingSize = 0;
	for (int i = 0; i < MAX_NUM; i++)
	{
		hash[i] = { -1, };
	}

	// Init head and tail for File LIst
	fHead = &(file[fIdx++]);
	fTail = &(file[fIdx++]);
	fHead->next = fTail; fHead->size = 0;
	fTail->prev = fHead; fTail->size = 0;

	// Init head and tail for Empty List
	eHead = &(empty[eIdx++]);
	eTail = &(empty[eIdx++]);
	eHead->next = eTail; eHead->size = 0;
	eTail->prev = eHead; eTail->size = 0;

	// Insert first empty space
	EMPTY* e = &(empty[eIdx++] = { 0, N, });
	INSERT(e, eTail);

	return;
}

int access(int fileId, int fileSize) {

	int key;

	// Update LSU, if fileId is already existed...
	if ((key = getKey(fileId)) != -1)
	{
		FILE* fp = hash[key].fp;
		DELETE(fp);
		INSERT(fp, fTail);

		return fp->start;
	}

	// Create the new file
	key = addKey(fileId);
	FILE* newFp = &(file[fIdx++] = { fileId, key, 0, fileSize, });
	hash[key].fp = newFp;

	while (1)
	{
		// Check Empty space
		EMPTY* e = eHead->next;

		while (e)
		{
			if (e->size >= fileSize)  break;
			e = e->next;
		}

		// Find Space...
		if (e)
		{
			usingSize += fileSize;

			newFp->start = e->start;

			// Add LSU
			INSERT(newFp, fTail);

			// Change the empty space
			if (e->size > fileSize)
			{
				e->start += fileSize;
				e->size -= fileSize;
			}
			else
			{
				DELETE(e);
			}

			return newFp->start;
		}

		// Delete the oldest file and make a empty space...
		{
			FILE* oldFp = fHead->next;

			// Find where to add the newEmpty space...
			EMPTY* nextEmpty = eHead->next;
			while (nextEmpty && (nextEmpty != eTail))
			{
				if (nextEmpty->start > oldFp->start)   break;
				nextEmpty = nextEmpty->next;
			}

			// Insert the new empty space
			EMPTY* newEmpty = &(empty[eIdx++] = { oldFp->start, oldFp->size, });
			INSERT(newEmpty, nextEmpty);

			// Merge with the previous empty space
			if ((newEmpty->prev != eHead) && ((newEmpty->prev->start + newEmpty->prev->size) == newEmpty->start))
			{
				newEmpty->start = newEmpty->prev->start;
				newEmpty->size += newEmpty->prev->size;

				EMPTY* prev = newEmpty->prev;
				DELETE(prev);
			}

			// Merge with the next empty space
			if ((newEmpty->next != eTail) && ((newEmpty->start + newEmpty->size) == newEmpty->next->start))
			{
				newEmpty->size += newEmpty->next->size;

				EMPTY* next = newEmpty->next;
				DELETE(next);
			}

			// Update usingSize...
			usingSize -= oldFp->size;
			delKey(oldFp->key);
			DELETE(oldFp);
		}
	}

	return 0;
}

int usage() {
	return usingSize;
}

#include<unordered_map>
#include<map>
#include<queue>
using namespace std;

struct EmptyBlock {
	int start;
	int size;
	EmptyBlock(int st, int sz) {
		this->start = st; this->size = sz;
	}
};
struct File {
	int id;
	int start;
	int size;
	int acsTime;
	File(int id, int st, int sz, int t) {
		this->id = id; this->start = st; this->size = sz; this->acsTime = t;
	}
};
struct Compare {
	bool operator()(File a, File b) {
		return a.acsTime > b.acsTime;
	}
};
map<int, EmptyBlock*> emptyMap; // start position : key
unordered_map<int, File*> fileMap;    //id : key
priority_queue<File, vector<File>, Compare> lrupq;
int cacheSz;
int t;

void init(int N) {
	lrupq = {};
	fileMap.clear();
	emptyMap.clear();
	cacheSz = 0;
	EmptyBlock* tmp = new EmptyBlock(0, N);
	emptyMap[0] = tmp;
	t = 0;
	return;
}
int findEmptySpace(int fileSize) {
	int emptyStart = -1;
	for (auto iter : emptyMap) {
		if (fileSize <= iter.second->size) {
			emptyStart = iter.first;
			return emptyStart;
		}
	}
	return emptyStart;
}
void mergeBlock() {
	for (auto iter : emptyMap) {
		int nextStart = iter.second->start + iter.second->size;
		while (emptyMap.count(nextStart) != 0) {
			EmptyBlock* tmp = emptyMap[nextStart];
			iter.second->size += tmp->size;
			emptyMap.erase(nextStart);
			nextStart += tmp->size;
		}
	}
}
void makeNewEmptySpace(int start, int size) {
	EmptyBlock* newEmpty = new EmptyBlock(start, size);
	emptyMap[start] = newEmpty;
	mergeBlock();
}

int access(int fileId, int fileSize) {
	t++;
	if (fileId == 985863898) {
		int a = 1;
	}
	if (fileMap.count(fileId) == 0) {
		int emptySpace = findEmptySpace(fileSize);
		while (emptySpace == -1) {
			File lru = lrupq.top();
			lrupq.pop();
			while (lru.acsTime != fileMap[lru.id]->acsTime) {
				lru = lrupq.top();
				lrupq.pop();
			}
			fileMap.erase(lru.id);
			cacheSz -= lru.size;
			makeNewEmptySpace(lru.start, lru.size);
			emptySpace = findEmptySpace(fileSize);
		}
		EmptyBlock* blk = emptyMap[emptySpace];
		blk->start += fileSize;
		blk->size -= fileSize;
		int newKey = blk->start;
		emptyMap.erase(emptySpace);
		if (blk->size != 0) emptyMap[newKey] = blk;
		File* newFile = new File(fileId, emptySpace, fileSize, t);
		fileMap[fileId] = newFile;
		lrupq.push(*newFile);
		cacheSz += fileSize;
		return newKey - fileSize;
	}
	fileMap[fileId]->acsTime = t;
	lrupq.push(*fileMap[fileId]);
	return fileMap[fileId]->start;
}

int usage() {
	return cacheSz;
}



#include <iostream>
#include <unordered_map>
using namespace std;

const int MAX_FILE = 20003;

struct FNode {
	int vfId;
	int time;
	
	int pos;
	int size;
	FNode* prev;
	FNode* next;
} fPool[MAX_FILE];
int fCnt;
FNode* head;
FNode* tail;

bool compare(const FNode* lhs, const FNode* rhs) {
	return lhs->time < rhs->time;
}

struct Heap {
	FNode* arr[MAX_FILE];
	int heapIdx[MAX_FILE];
	int heapSize;
	void init() {
		heapSize = 0;
	}
	inline int parent(int n) {
		return (n - 1) >> 1;
	}
	inline int leftChild(int n) {
		return (n << 1) + 1;
	}
	inline int rightChild(int n) {
		return (n << 1) + 2;
	}
	void push(FNode* nFile) {
		int cur = heapSize++;
		
		arr[cur] = nFile;
		heapIdx[nFile->vfId] = cur;

		while (cur > 0 && compare(arr[cur], arr[parent(cur)])) {
			swap(arr[cur], arr[parent(cur)]);
			swap(heapIdx[arr[cur]->vfId], heapIdx[arr[parent(cur)]->vfId]);
			cur = parent(cur);
		}
	}

	FNode* pop() {
		int cur = 0;
		FNode* ret = arr[cur];

		arr[cur] = arr[--heapSize];
		heapIdx[arr[cur]->vfId] = cur;

		while (leftChild(cur) < heapSize) {
			int child;
			if (leftChild(cur) == heapSize - 1) {
				child = leftChild(cur);
			}
			else if (compare(arr[leftChild(cur)], arr[rightChild(cur)])) {
				child = leftChild(cur);
			}
			else {
				child = rightChild(cur);
			}

			if (compare(arr[cur], arr[child])) {
				break;
			}

			swap(arr[cur], arr[child]);
			swap(heapIdx[arr[cur]->vfId], heapIdx[arr[child]->vfId]);
			cur = child;
		}
		return ret;
	}

	FNode* update(int vfId, int time) {
		FNode* ret;
		int cur = heapIdx[vfId];
		arr[cur]->time = time;
		ret = arr[cur];

		while (cur > 0 && compare(arr[cur], arr[parent(cur)])) {
			swap(arr[cur], arr[parent(cur)]);
			swap(heapIdx[arr[cur]->vfId], heapIdx[arr[parent(cur)]->vfId]);
			cur = parent(cur);
		}
		while (leftChild(cur) < heapSize) {
			int child;
			if (leftChild(cur) == heapSize - 1) {
				child = leftChild(cur);
			}
			else if (compare(arr[leftChild(cur)], arr[rightChild(cur)])) {
				child = leftChild(cur);
			}
			else {
				child = rightChild(cur);
			}

			if (compare(arr[cur], arr[child])) {
				break;
			}

			swap(arr[cur], arr[child]);
			swap(heapIdx[arr[cur]->vfId], heapIdx[arr[child]->vfId]);
			cur = child;
		}

		return ret;
	}
};

unordered_map<int, int> vfTable;
int vfCnt;
bool isAliveFile[MAX_FILE];
int N;
int usedMemory;
Heap heap;
int timeStamp;

void init(int n) {
	N = n;
	usedMemory = 0;
	timeStamp = 0;
	fCnt = 0;
	vfCnt = 0;
	vfTable.clear();
	heap.init();

	for (int i = 0; i < MAX_FILE; ++i) {
		isAliveFile[i] = false;
	}

	head = &fPool[fCnt++];
	tail = &fPool[fCnt++];
	
	head->pos = 0;
	head->size = 0;
	tail->pos = N;
	tail->size = 0;

	head->next = tail;
	tail->prev = head;

	return;
}

int access(int fileId, int fileSize) {
	// 기존에 살아있나 검사하기
	int vfId;
	if (vfTable.find(fileId) == vfTable.end()) {
		vfTable[fileId] = vfCnt++;
	}
	vfId = vfTable[fileId];

	// 살아있으면~ time 갱신 
	if (isAliveFile[vfId]) {
		FNode* cur = heap.update(vfId, timeStamp++);
		return cur->pos;
	}

	int ret = -1;
	// head를 쭉 검사..
	int curLast;
	for (FNode* cur = head; cur != tail; cur = cur->next) {
		int curLast = cur->pos + cur->size;
		if ((cur->next->pos - curLast) >= fileSize) {
			ret = curLast;

			FNode* nFile = &fPool[fCnt++];
			nFile->vfId = vfId;
			nFile->time = timeStamp++;
			nFile->pos = curLast;
			nFile->size = fileSize;
			
			nFile->next = cur->next;
			nFile->prev = cur;

			cur->next->prev = nFile;
			cur->next = nFile;

			usedMemory += fileSize;
			isAliveFile[vfId] = true;
			heap.push(nFile);
			return ret;
		}
	}

	// 만약에 못넣어? 그러면 가장 오래된 캐시를 팝해서 그 전 단계 노드부터 확인! 
	while (heap.heapSize > 0) {
		FNode* rFile = heap.pop();
		usedMemory -= rFile->size;
		isAliveFile[rFile->vfId] = false;
		FNode* cur = rFile->prev;
		
		cur->next = rFile->next;
		rFile->next->prev = cur;

		int curLast = cur->pos + cur->size;
		if ((cur->next->pos - curLast) >= fileSize) {
			ret = curLast;

			FNode* nFile = &fPool[fCnt++];
			nFile->vfId = vfId;
			nFile->time = timeStamp++;
			nFile->pos = curLast;
			nFile->size = fileSize;

			nFile->next = cur->next;
			nFile->prev = cur;

			cur->next->prev = nFile;
			cur->next = nFile;

			usedMemory += fileSize;
			isAliveFile[vfId] = true;
			heap.push(nFile);
			return ret;
		}
	}
	
	return ret;
}

int usage() {
	return usedMemory;
}
