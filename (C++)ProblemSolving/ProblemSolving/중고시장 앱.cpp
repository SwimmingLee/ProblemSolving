

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
using namespace std;

struct Product {
	int tag;
	int price;
};
unordered_map<string, int> hTable;
int hCnt;

struct Node {
	Product p;
	Node* next;
}a [30001];
int aCnt;

Node* myalloc() {
	return &a[aCnt++];
}
Node* head;

void init(int N)
{
	aCnt = hCnt = 0;
	head  = myalloc();
	head->next = nullptr;

	hTable.clear();
}
int tagNo(char* str) {
	if (hTable.find(str) == hTable.end()) {
		hTable[str] = hCnt++;
	}
	return hTable[str];
}
void addProduct(int mPrice, int tagNum, char tagName[][10])
{
	int tag = 0;
	for (int i = 0; i < tagNum; ++i) {
		int bit = tagNo(tagName[i]);
		tag |= (1 << bit);
	}
	Node* node = myalloc();
	node->p.tag = tag;
	node->p.price = mPrice;

	node->next = head->next;
	head->next = node;
}

int buyProduct(char tag1[], char tag2[], char tag3[])
{
	int tag = 0;
	int bit;

	bit = tagNo(tag1);
	tag |= (1 << bit);

	bit = tagNo(tag2);
	tag |= (1 << bit);

	bit = tagNo(tag3);
	tag |= (1 << bit);

	int buyPrice = -1;
	Node* prev = head;
	Node* prevRemoveNode = head;
	for (Node* it = head->next; it != nullptr; it = it->next) {
		Product& p = it->p;
		if ((p.tag & tag) == tag) {
			if (buyPrice == -1 || buyPrice > p.price) {
				cout << p.price << endl;
				buyPrice = p.price;
				prevRemoveNode = prev;
			}
		}
		prev = it;
	}

	if (buyPrice != -1) {
		Node* removeNode = prevRemoveNode->next;
		prevRemoveNode->next = removeNode->next;
	}
	return buyPrice;
}

void adjustPrice(char tag1[], int changePrice)
{
	int tag = 0;
	int bit;

	bit = tagNo(tag1);
	tag |= (1 << bit);

	for (Node* it = head->next; it != nullptr; it = it->next) {
		Product& p = it->p;
		if (p.tag & tag) {
			p.price += changePrice;
		}
	}
}