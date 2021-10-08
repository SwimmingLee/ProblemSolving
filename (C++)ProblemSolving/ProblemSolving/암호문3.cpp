#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
	Node* prev;
} a[4502];
int aCnt;

int N;
Node* head;
Node* tail;
Node* myalloc() {
	return &a[aCnt++];
}

void init() {
	aCnt = 0;
	head = myalloc();
	tail = myalloc();

	head->next = tail;
	tail->prev = head;
}

void run() {
	cin >> N;
	// 원본 암호문 입력
	int data;
	Node* node;
	Node* prev = head;
	for (int i = 0; i < N; ++i) {
		cin >> data;
		node = myalloc();
		node->data = data;

		node->prev = prev;
		prev->next = node;
		prev = node;
	}
	prev->next = tail;
	tail->prev = prev;

	cin >> N;
	char cmd;
	int idx;
	int password;
	for (int i = 0; i < N; ++i) {
		cin >> cmd;
		if (cmd == 'I') {
			cin >> idx >> password;
			int cnt = 0;
			Node* prev = head;
			Node* iter;
			for (iter = head->next; iter != tail && cnt < idx; iter = iter->next, cnt++) {
				prev = iter;
			}
			for (int j = 0; j < password; ++j) {
				cin >> data;
				node = myalloc();
				node->data = data;

				node->prev = prev;
				node->next = iter;

				prev->next = node;
				iter->prev = node;

				prev = prev->next;
			}
		}
		else if (cmd == 'D') {
			cin >> idx >> password;
			int cnt = 0;
			Node* prev = head;
			Node* iter;
			for (iter = head->next; iter != tail && cnt < idx; iter = iter->next, cnt++) {
				prev = iter;
			}
			for (int j = 0; j < password; ++j) {
				iter->prev->next = iter->next;
				iter->next->prev = iter->prev;

				iter = iter->next;
			}
		}
		else if (cmd == 'A') {
			cin >> password;
			for (int i = 0; i < password; ++i) {
				cin >> data;

				node = myalloc();
				node->data = data;

				tail->prev->next = node;
				node->prev = tail->prev;

				node->next = tail;
				tail->prev = node;

			}
		}
	}
}

void print(int tc) {
	cout << '#' << tc << ' ';
	for (Node* iter = head->next; iter != tail; iter = iter->next) {
		cout << iter->data << ' ';
	}
	cout << '\n';
}