#define MAX_NODE 10000

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;
//Node* tail;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
	nodeCnt = 0;
	Node* dummy = getNode(-99999999);
	head = dummy;
}

void addNode2Head(int data)
{
	Node* nnode = getNode(data);
	nnode->next = head->next;
	head->next = nnode; /*½Ç¼ö*/
}

void addNode2Tail(int data)
{
	Node* nnode = getNode(data);
	Node* cur = head;
	while (cur->next != nullptr) {
		cur = cur->next;
	}
	cur->next = nnode;
}

void addNode2Num(int data, int num)
{
	Node* nnode = getNode(data);
	Node* cur = head;
	int cnt = 1;
	while (cur->next != nullptr && cnt < num) {
		cur = cur->next;
		cnt++;
	}
	nnode->next = cur->next;
	cur->next = nnode;

}

void removeNode(int data)
{
	Node* cur = head;
	while (cur->next != nullptr && cur->next->data == data) {
		cur = cur->next;
	}
	
	Node* rnode = cur->next;
	cur->next = cur->next->next;

}

int getList(int output[MAX_NODE])
{
	int cnt = 0;
	Node* cur = head->next;

	while (cur->next != nullptr) {
		output[cnt++] = cur->data;
		cur = cur->next;
	}
	if (cur != nullptr) {
		output[cnt++] = cur->data;
	}
	return cnt;
}