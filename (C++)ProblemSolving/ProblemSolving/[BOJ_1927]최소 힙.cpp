//#include <iostream>
//using namespace std;
//
//#define MAX_COMMAND		100000
//#define PARENT(x)		((x)/2)
//#define LEFT_CHILD(x)	((x)*(2))
//#define RIGHT_CHILD(x)	((x)*(2)+1)
//#define ROOT_IDX		1
//
//struct heap {
//	int arr[MAX_COMMAND+1];
//	int heap_size;
//	heap() : heap_size(0) {}
//	void push(int val) {
//		int cur = ++heap_size;
//		int par = PARENT(cur);
//		arr[cur] = val;
//
//		while (cur != ROOT_IDX && arr[cur] < arr[par]) {
//			swap(arr[cur], arr[par]);
//			cur = par;
//			par = PARENT(par);
//		}
//	}
//	int pop() {
//		if (heap_size == 0) return 0;
//		int res = arr[ROOT_IDX];
//		int cur = ROOT_IDX;
//		arr[cur] = arr[heap_size--];
//		while (true) {
//			int left = LEFT_CHILD(cur);
//			int right = RIGHT_CHILD(cur);
//			int select;
//
//			if (left > heap_size)
//				break;
//			else if (left == heap_size || arr[left] < arr[right])
//				select = left;
//			else
//				select = right;
//
//			if (arr[select] >= arr[cur]) break;
//			swap(arr[select], arr[cur]);
//			cur = select;
//		}
//		return res;
//	}
//};
//
//int main(void) {
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
//	int num_command;
//	int val;
//	heap Heap;
//
//	cin >> num_command;
//	for (int i = 0; i < num_command; i++) {
//		cin >> val;
//		if (val == 0) cout << Heap.pop() << '\n';
//		else Heap.push(val);
//	}
//	return 0;
//}


#include <iostream>
#include <vector>
using namespace std;

struct Heap {
	vector<int> arr;
	int size;
	Heap(int max_size) : size(0) { arr.resize(max_size+1); };
	int pop() {
		if (size == 0) return 0;

		int cur = 1;
		int res = arr[cur];
		while (true) {
			int left = cur * 2;
			int right = cur * 2 + 1;

			int next;
			if (left > size) break;

			if (left == size || arr[left] < arr[right]) next = left;
			else next = right;

			if (arr[size] <= arr[next]) break;
			else {
				arr[cur] = arr[next];
				//swap(arr[cur], arr[next]);
				cur = next;
			}

		}
		arr[cur] = arr[size--];
		return res;
	}

	void push(int x) {
		arr[++size] = x;

		int cur = size;
		int par = cur / 2;
		while (cur != 1 && arr[par] > arr[cur]) {
			swap(arr[par], arr[cur]);
			cur = par;
			par = cur / 2;
			
		}
	}
};

int main(void) {
	cin.tie(NULL); ios::sync_with_stdio(false);
	int n_cmd;
	cin >> n_cmd;
	Heap heap(n_cmd);
	while (n_cmd--) {
		int x;
		cin >> x;
		if (x == 0) cout << heap.pop() << '\n';
		else heap.push(x);
	}
}