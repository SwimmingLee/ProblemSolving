
struct Node{
	Node* children[5];
	Node* parent;
	int val;
	int cnt;
};

Node tree[100];
/*
* define MAX 100
int childNum[MAX];
int node[MAX][MAX];
 
void dfs_init(int N, int path[100][2])
{
    int parent, child;
    for(int i=0; i<MAX; i++){
        childNum[i] = 0;
    }
     
    for(int i=0; i<N; i++){
        parent = path[i][0];
        child = path[i][1];
        node[parent][childNum[parent]++] = child;
    }
}
 
int searchNode(int curr, int king){
    if(curr>king) return curr;
     
    for(int i=0; i<childNum[curr]; i++){
        int tmp = searchNode(node[curr][i], king);
        if(tmp!=-1) return tmp;
    }
     
    return -1;
}
 
 
int dfs(int n)
{
    return searchNode(n, n);
}
*/
void dfs_init(int N, int path[100][2])
{
	for (int i = 1; i < 100; i++) {
		tree[i].val = i;
		tree[i].cnt = 0;
	}

	for (int i = 0; i < N; i++) {
		int p = path[i][0];
		int c = path[i][1];

		tree[c].parent = &tree[p];
		tree[p].children[(tree[p].cnt++)] = &tree[c];
	}
}

int dfs(int ref_val, int n) {

	if (n > ref_val) return n;
	for (int i = 0; i < tree[n].cnt; i++) {
		int next = tree[n].children[i]->val;

		int child_val = dfs(ref_val, next);
		if (child_val > ref_val) {
			return child_val;
		}
	}
	return -1;
}


int dfs(int n)
{
	for (int i = 0; i < tree[n].cnt; i++) {
		int next = tree[n].children[i]->val;

		int child_val = dfs(n, next);
		if (child_val > n) {
			return child_val;
		}
	}
	
	return -1;
}

