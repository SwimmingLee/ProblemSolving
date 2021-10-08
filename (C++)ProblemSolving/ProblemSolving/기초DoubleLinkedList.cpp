#define MAX_NODE 10002

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;
Node* tail;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
	int inf = -9999999999;
	nodeCnt = 0;
	head = getNode(inf);
	tail = getNode(inf);

	head->next = tail;
	tail->prev = head;
}

void addNode2Head(int data)
{
	Node* nnode = getNode(data);
	nnode->next = head->next;
	head->next->prev = nnode;

	head->next = nnode;
	nnode->prev = head;
}

void addNode2Tail(int data)
{
	Node* nnode = getNode(data);
	
	nnode->prev = tail->prev;
	tail->prev->next = nnode;
	
	tail->prev = nnode;
	nnode->next = tail;
}

void addNode2Num(int data, int num)
{
	Node* cur = head;
	int node_num = 1;
	while (cur->next != nullptr && node_num < num) {
		cur = cur->next;
		node_num++;
	}

	Node* nnode = getNode(data);
	nnode->next = cur->next;
	cur->next->prev = nnode;

	cur->next = nnode;
	nnode->prev = cur;
}

int findNode(int data)
{
	/*
	* 없다면 -1..? 이런 조건이라면 안됨
	*/
	Node* cur = head->next;
	int node_num = 1;
	while (cur->next != nullptr && cur->data != data) {
		cur = cur->next;
		node_num++;
	}
	return node_num;
}

void removeNode(int data)
{
	Node* cur = head->next;
	while (cur->next != nullptr && cur->data != data) {
		cur = cur->next;
	}

	if (cur == tail) return; /*이 조건 누락*/
	Node* rnode = cur;
	rnode->prev->next = rnode->next;
	rnode->next->prev = rnode->prev;
}

int getList(int output[MAX_NODE])
{
	Node* cur = head->next;
	int node_idx = 0;
	while (cur->next != nullptr) {
		output[node_idx++] = cur->data;
		cur = cur->next;
	}
	return node_idx;
}

int getReversedList(int output[MAX_NODE])
{
	Node* cur = tail->prev;
	int node_idx = 0;
	while (cur->prev != nullptr) {
		output[node_idx++] = cur->data;
		cur = cur->prev;
	}
	return node_idx;
}