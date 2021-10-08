#include <iostream>
//#include <list>
using namespace std;

#define MAX_USER	10000
enum USER_STATE {
	NONE = 0, EDIT, CONFICT
};
struct Node {
	char c;
	bool isEdit; // 처음 기록하고, editing이 완료되는 다시 false로 변경해줘하는 번거로움이 있음
	Node* next;
	Node* nextHead;
} a[1000];
int aCnt;
Node* startHead;
int userState[MAX_USER];

struct UserEdit {
	Node* node;
	int length;
	
};

Node* myalloc() {
	return &a[aCnt++];
}

Node* insertNode(Node* node, char c) {
	Node* nnode = myalloc();
	nnode->c = c;
	nnode->isEdit = false;
	nnode->next = nullptr;
	nnode->nextHead = nullptr;
	
	node->next = nnode;
}

void Init(int width, int length, char str[])
{	
	Node* node = myalloc();
	Node* head = node;
	startHead = node;
	int w = 0;
	for (int i = 0; i < length; ++i) {
		if (str[i] == '\n' || w == width) {
			w = 0;

			Node* nextHead = myalloc();
			head->nextHead = nextHead;
			head = nextHead;
			node = head;

			if (str[i] == '\n')
				continue;
		}

		insertNode(node, str[i]);
		w += 1;
	}
}

void Edit(int id, int row, int col)
{
	Node* node = startHead;
	for (int i = 0; i < row; ++i) {
		node = node->nextHead;
	}
	for (int i = 0; i < col; ++i) {
		node = node->next;
	}
}

void Add(int id, int length, char str[])
{
	
}

void Delete(int id, int length)
{
}

void Substitute(int id, int length, char str[])
{
}

int EditDone(int id)
{
	return 0;
}
