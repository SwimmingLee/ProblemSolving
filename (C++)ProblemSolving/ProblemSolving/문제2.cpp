#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 트리 구조로 생각하기 
// 위에서부터 하나씩 아래로 간다면 구할 수 있을까?

int tree[130];
int depth[20];
void init() {
	for (int i = 1; i < 17; i++) {
		depth[i] = i * (i + 1) / 2;
	}
}


int getLeftChild(int idx) {
	int layer = 0;
	for (int i = 1; i <= 15; i++) {
		if (idx > depth[i]) {
			break;
		}
		layer = i;
	}
	
	int layer_seq = depth[layer] - depth[layer - 1];
	int left_child = depth[layer] + layer_seq;

	if (left_child > max_seq)
		return 0;
	else
		return left_child;
}

int getRightChild(int idx) {
	int layer = 0;
	for (int i = 1; i <= 15; i++) {
		if (idx > depth[i]) {
			break;
		}
		layer = i;
	}

	int layer_seq = depth[layer] - depth[layer - 1];
	int right_child = depth[layer] + layer_seq + 1;

	if (right_child > max_seq)
		return 0;
	else
		return right_child;

}

int block_value[130];
bool chk[130];
void search(int idx) {
	chk[idx] = true;
	int left_child = getLeftChild(idx);
	int right_child = getRightChild(idx);

	cout << "Idx :" << idx << " L: " << left_child << " R:" << right_child << endl;
	if (left_child != 0 && !chk[left_child])
		search(left_child);
	if (right_child != 0 && !chk[right_child])
		search(right_child);
}

int max_seq;
vector<int> solution(vector<vector<int>> blocks) {
	vector<int> answer;
	
	// blocks에 있는 것들을 내가 생각한 자료구로 옮기는 작업이 필요함
	// blocks 를 block[idx] = 값 이렇게 만들어 놓고'
	// 각 블럭끼리 자식 노드를 찾을 수 있따면 금방 해결할 수 있지 않을까 싶다. 
	// 
	init();
	max_seq = depth[blocks.size()];
	for (int i = 0; i < blocks.size(); i++) {
		int depth_start_idx = depth[i+1];
		int seq = blocks[i][0];
		int value = blocks[i][1];
		block_value[depth_start_idx + seq] = value;
	}

	search();

	return answer;
}