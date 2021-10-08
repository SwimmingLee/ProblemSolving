//
//int strcmp(const char* str1, const char* str2) {
//	while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0') {
//		str1++; str2++;
//	}
//	return (*str1 - *str2);
//}
//void strcpy(char* des, char* src) {
//	char c;
//	while (c = *(src++)) {
//		*(des++) = c;
//	}
//	*des = '\0';
//}
//
//struct Node {
//	int idx;
//	char name[11];
//	Node() {}
//	Node(int _idx, char _name[]) {
//		idx = _idx;
//		strcpy(name, _name);
//	}
//	bool operator<(const Node& rhs) {
//		int cmpRet = strcmp(name, rhs.name);
//		if (cmpRet < 0) return true;
//		else if (cmpRet > 0) return false;
//		else {
//			if (idx > rhs.idx) return true;
//			else return false;
//		}
//	}
//} heap[100001];
//int aCnt;
//int root;
//
//int parent(int n) {
//	return (n - 1) >> 1;
//}
//int leftChild(int n) {
//	return (n << 1) + 1;
//}
//int rightChild(int n) {
//	return (n << 1) + 2;
//}
//
//void init() {
//	aCnt = 0;
//	root = 0;
//}
//
//void clear() {
//	aCnt = 0;
//}
//
//void push(int idx, char* name) {
//	Node node = Node(idx, name);
//
//	int p = parent(aCnt);
//	int c = aCnt;
//	while (c != root && heap[p] < node) {
//		strcpy(heap[c].name, heap[p].name);
//		heap[c].idx = heap[p].idx;
//		c = p;
//		p = parent(p);
//	}
//	strcpy(heap[c].name, node.name);
//	heap[c].idx = node.idx;
//	aCnt++;
//}
//
//int pop() {
//	int ret = heap[root].idx;
//	//printf("[] %d %s\n", ret, heap[root].name);
//	aCnt -= 1;
//	Node node = heap[aCnt];
//
//	int p = root;
//	int lc, rc, c = -1;
//	
//	while (true) {
//		lc = leftChild(p);
//		rc = rightChild(p);
//
//		if (lc >= aCnt)					break;
//		else if (lc == aCnt - 1)		c = lc;
//		else if (heap[lc] < heap[rc])	c = rc;
//		else							c = lc;
//
//		if (heap[c] < node) break;
//		strcpy(heap[p].name, heap[c].name);
//		heap[p].idx = heap[c].idx;
//		p = c;
//	}
//	strcpy(heap[p].name, node.name);
//	heap[p].idx = node.idx;
//	
//	return ret;
//}
//
//int top() {
//	return heap[root].idx;
//}
//
