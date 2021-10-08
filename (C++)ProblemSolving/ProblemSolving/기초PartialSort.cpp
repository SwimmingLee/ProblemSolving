#define MAX_USERS (100002)
struct User{
	int uID;
	int income;
	User(int _uID, int _income): uID(_uID), income(_income) {}
	User() {}
	//bool operator<(const User& rhs) {
	//	if (income < rhs.income) return true;
	//	else if (income > rhs.income) return false;
	//	else return uID > rhs.uID;
	//}
};

struct Heap {
	User heap_array[MAX_USERS];
	int heap_size;
	int root;
	Heap() {
		root = 1;
		heap_size = 0;
	}
	bool compare(const User& lhs, const User& rhs) {
		if (lhs.income < rhs.income) return true;
		else if (lhs.income > rhs.income) return false;
		else return lhs.uID > rhs.uID;
	}
	int getParent(int n) {
		return n / 2;
	}
	int getLeftChild(int n) {
		return 2 * n;
	}
	int getRightChild(int n) {
		return 2 * n + 1;
	}
	void push(User user) {
		int cur = ++heap_size;
		int parent = getParent(cur);

		while (parent != 0 && compare(heap_array[parent], user)) {
			heap_array[cur] = heap_array[parent];
			cur = parent;
			parent = getParent(cur);
		}
		heap_array[cur] = user;
	}
	User pop() {
		User ruser = heap_array[root];
		User tmp = heap_array[heap_size--];

		int cur = root;
		int lchild, rchild, maxchild;

		while (true) {
			lchild = getLeftChild(cur);
			rchild = getRightChild(cur);

			if (lchild > heap_size) break;
			if (lchild == heap_size) maxchild = lchild;
			else maxchild = ((compare(heap_array[lchild],heap_array[rchild])) ? rchild : lchild); /**/

			if (compare(tmp, heap_array[maxchild])) {
				heap_array[cur] = heap_array[maxchild];
				cur = maxchild;
			}
			else break;
		}
		heap_array[cur] = tmp;

		return ruser;
	}
	bool empty() {
		return (heap_size == 0);
	}
};

Heap heap;
void init()
{
	heap.heap_size = 0;
}

void addUser(int uID, int height)
{
	heap.push(User(uID, height));
}

int getTop10(int result[10])
{
	User top_users[10];
	int top_cnt = 0;
	while (!heap.empty() && top_cnt < 10) {
		top_users[top_cnt] = heap.pop();
		result[top_cnt] = top_users[top_cnt].uID;
		top_cnt++; /*******SSIBALALLLL********/
	}

	for (int i = 0; i < top_cnt; i++) {
		heap.push(User(top_users[i].uID, top_users[i].income));
	}
	
	return top_cnt;
}
