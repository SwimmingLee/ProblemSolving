#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Ʈ�� ������ �����ϱ� 
// ���������� �ϳ��� �Ʒ��� ���ٸ� ���� �� ������?

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
	
	// blocks�� �ִ� �͵��� ���� ������ �ڷᱸ�� �ű�� �۾��� �ʿ���
	// blocks �� block[idx] = �� �̷��� ����� ����'
	// �� ������ �ڽ� ��带 ã�� �� �ֵ��� �ݹ� �ذ��� �� ���� ������ �ʹ�. 
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