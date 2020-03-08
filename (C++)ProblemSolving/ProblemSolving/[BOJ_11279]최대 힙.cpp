#include <iostream>
using namespace std;

#define MAX_COMMAND 1000/*100000*/
#define ROOT_IDX	1
struct heap {
	int arr[MAX_COMMAND+1];
	int heap_size;
	heap(): heap_size(0) {}
	bool empty() {
		return heap_size == 0 ? true : false;
	}
	int left_child(int idx) {
		return idx * 2;
	}
	int right_child(int idx) {
		return idx * 2 + 1;
	}
	int parent(int idx) {
		return idx / 2;
	}
	int pop() {
		if (empty()) return 0;
		int res = arr[ROOT_IDX];
		int cur = ROOT_IDX;

		arr[cur] = arr[heap_size--];
		while (true) {
			int left = left_child(cur);
			int right = right_child(cur);
			int select;

			if (left > heap_size)
				break;
			else if (left == heap_size || arr[left] > arr[right])
				select = left;
			else
				select = right;

			if (arr[select] <= arr[cur])
				break;

			swap(arr[select], arr[cur]);
			cur = select;
		}
		return res;
	}

	void push(int val) {
		int cur = ++heap_size;
		int par = parent(cur);

		arr[cur] = val;
		while (cur != ROOT_IDX && arr[cur] > arr[par]) {
			swap(arr[cur], arr[par]);
			cur = par;
			par = parent(par);
		}
	}
};

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int num_command;
	cin >> num_command;
	heap Heap;
	for (int i = 0; i < num_command; i++) {
		int num;
		cin >> num;
		if (num == 0) cout << Heap.pop() << '\n';
		else Heap.push(num);
	}
	return 0;
}