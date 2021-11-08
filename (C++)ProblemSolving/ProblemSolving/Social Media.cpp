//#include <queue>
//using namespace std;
//
//const int MAXN = 1000;
//const int MAXPOST = 100000;
//#define MIN(x, y) ((x) < (y) ? (x) : (y))
//
//bool isFollow[MAXN + 1][MAXN + 1];
//
//struct Post {
//	int uID;
//	int pID;
//	int likes;
//	int timestamp;
//	Post() {}
//	Post(int uID, int pID, int likes, int timestamp) : uID(uID), pID(pID), likes(likes), timestamp(timestamp) {}
//};
//Post posts[MAXPOST + 1];
//int postCnt;
//
//void init(int N)
//{
//	for (int i = 1; i <= MAXN; i++) {
//		for (int j = 1; j <= MAXN; j++) {
//			isFollow[i][j] = false;
//			if (i == j) isFollow[i][j] = true;
//		}
//	}
//	postCnt = 0;
//}
//
//void follow(int uID1, int uID2, int timestamp)
//{
//	isFollow[uID1][uID2] = true;
//}
//
//void makePost(int uID, int pID, int timestamp)
//{
//	posts[pID] = Post(uID, pID, 0, timestamp);
//	postCnt++;
//}
//
//void like(int pID, int timestamp)
//{
//	posts[pID].likes++;
//}
//
//bool compare(const Post& a, const Post& b)
//{
//	if (a.likes == b.likes) return a.timestamp < b.timestamp;
//	return a.likes < b.likes;
//}
//
//struct pq_compare {
//	bool operator()(const Post& a, const Post& b) {
//		if (a.likes == b.likes) return a.timestamp < b.timestamp;
//		return a.likes < b.likes;
//	}
//};
//
//void getFeed(int uID, int timestamp, int pIDList[])
//{
//	int cnt = 0;
//	priority_queue<Post, vector<Post>, pq_compare> pq;
//	int p, i;
//
//	for (p = postCnt; p >= 1; p--) {
//		if (timestamp - posts[p].timestamp > 1000) break;
//		if (!isFollow[uID][posts[p].uID]) continue;
//		else {
//			pq.push(posts[p]);
//			cnt++;
//		}
//	}
//
//	for (i = 0; i < MIN(10, cnt); i++) {
//		pIDList[i] = pq.top().pID; pq.pop();
//	}
//	for (; i < 10 && p >= 1; i++, p--) {
//		if (!isFollow[uID][posts[p].uID]) { i--; continue; }
//		pIDList[i] = p;
//	}
//}

////정아
//#include <iostream>
//#include <cstring>
//#include <tuple>
//
//using namespace std;
//
//#define POSTMAX 100000
//#define USERMAX 1000
//
//struct Info {
//	int uId;
//	int pId;
//	int like;
//	int timestamp;
//};
//int postCnt = 0;
//Info post[POSTMAX + 1];
//bool followInfo[USERMAX + 1][USERMAX + 1]; // follow했는지 여부
//
//void init(int N)
//{
//	postCnt = 0;
//	memset(followInfo, false, sizeof(followInfo));
//}
//
//void follow(int uID1, int uID2, int timestamp)
//{
//	followInfo[uID1][uID2] = true;
//}
//
//void makePost(int uID, int pID, int timestamp)
//{
//	postCnt++;
//	post[pID].uId = uID;
//	post[pID].pId = pID;
//	post[pID].like = 0;
//	post[pID].timestamp = timestamp;
//}
//
//void like(int pID, int timestamp)
//{
//	post[pID].like += 1;
//}
//
//void getFeed(int uID, int timestamp, int pIDList[])
//{
//	Info pri[11]; // feed의 우선순위
//	int cnt = 0; // pri배열에 채워진 feed의 개수
//	int idx = postCnt;
//
//	if (idx == 0) return;
//
//	// postCnt부터 차근차근 아래로 pID를 탐색한다.
//	while (1)
//	{
//		if (idx == 0) break;
//		if (uID != post[idx].uId && !followInfo[uID][post[idx].uId])
//		{
//			idx--;
//			continue;
//		}
//
//		int gap = timestamp - post[idx].timestamp;
//		if (cnt == 10 && gap > 1000) break;
//		bool isPut = false; // feed가 들어갈 수 있는가?
//		int putIdx = cnt; // feed가 들어가야 하는 위치
//		if (gap <= 1000)
//		{
//			for (int i = 0; i < cnt; i++)
//			{
//				if (pri[i].like > post[idx].like) continue;
//				else if (pri[i].like == post[idx].like)
//				{
//					if (pri[i].timestamp > post[idx].timestamp) continue;
//					isPut = true;
//					putIdx = i;
//					break;
//				}
//				else {
//					isPut = true;
//					putIdx = i;
//					break;
//				}
//			}
//			if (isPut)
//			{
//				for (int i = cnt - 1; i >= putIdx; i--)
//				{
//					if (i + 1 == 10) continue;
//					pri[i + 1].pId = pri[i].pId;
//					pri[i + 1].like = pri[i].like;
//					pri[i + 1].timestamp = pri[i].timestamp;
//				}
//			}
//		}
//		pri[putIdx].pId = post[idx].pId;
//		pri[putIdx].like = post[idx].like;
//		pri[putIdx].timestamp = post[idx].timestamp;
//		if (cnt < 10) cnt++;
//		idx--;
//	}
//
//	for (int i = 0; i < cnt; i++)
//	{
//		pIDList[i] = pri[i].pId;
//	}
//}


#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_USER	1001
#define MAX_POST	100001

struct Post {
	int id;
	int likes;
	int time;
	Post() {}
	Post(int id, int time) : id(id), time(time), likes(0) {}
	bool operator<(const Post& rhs) {
		if (likes == rhs.likes) {
			return time > rhs.time;
		}
		else {
			return likes > rhs.likes;
		}
	}
};
int heapIdx[MAX_POST];

struct Heap {
	//Post arr[MAX_POST];
	vector<Post> arr;

	int sz;
	int root;
	Heap() {
		root = 0;
		sz = 0;
	}
	int getParent(int n) {
		return (n - 1) >> 1;
	}
	int getLeftChild(int n) {
		return (n << 1) + 1;
	}
	int getRightChild(int n) {
		return (n << 1) + 2;
	}

	void push(Post post) {
		int cur = sz++;
		arr.push_back(post);
		//arr[cur] = post;
		heapIdx[post.id] = cur;

		while (cur > 0 && arr[getParent(cur)] < arr[cur]) {
			swap(arr[getParent(cur)], arr[cur]);
			heapIdx[arr[cur].id] = cur;
			heapIdx[arr[getParent(cur)].id] = getParent(cur);

			cur = getParent(cur);
		}
	}

	Post pop() {
		Post rpost = arr[0];
		heapIdx[rpost.id] = -1;
		int cur = root;

		arr[cur] = arr[--sz]; 
		heapIdx[arr[cur].id] = cur;
		arr.pop_back();

		int child;
		while (getLeftChild(cur) <= sz - 1) {
			if (getLeftChild(cur) == sz - 1)
				child = getLeftChild(cur);
			else if (arr[getLeftChild(cur)] < arr[getRightChild(cur)])
				child = getRightChild(cur);
			else
				child = getLeftChild(cur);

			if (arr[child] < arr[cur]) {
				break;
			}
			swap(arr[child], arr[cur]);
			heapIdx[arr[cur].id] = cur;
			heapIdx[arr[child].id] = child;

			cur = child;
		}

		return rpost;
	}

	void likePost(int pID) {
		int cur = heapIdx[pID];
		arr[cur].likes++;

		if (arr[getParent(cur)] < arr[cur]) {
			while (cur > 0 && arr[getParent(cur)] < arr[cur]) {
				swap(arr[getParent(cur)], arr[cur]);
				heapIdx[arr[cur].id] = cur;
				heapIdx[arr[getParent(cur)].id] = getParent(cur);

				cur = getParent(cur);
			}
		}
		else {
			int child;
			while (getLeftChild(cur) <= sz - 1) {
				if (getLeftChild(cur) == sz - 1)
					child = getLeftChild(cur);
				else if (arr[getLeftChild(cur)] < arr[getRightChild(cur)])
					child = getRightChild(cur);
				else
					child = getLeftChild(cur);

				if (arr[child] < arr[cur]) {
					break;
				}
				swap(arr[child], arr[cur]);
				heapIdx[arr[cur].id] = cur;
				heapIdx[arr[child].id] = child;

				cur = child;
			}
		}

	}
};


vector<Post> outPosts[MAX_USER];
queue<Post> inPosts[MAX_USER];
vector<int> followUsers[MAX_USER];
int postWriter[MAX_POST];
Heap orderedPosts[MAX_USER];


void init(int N)
{
	for (int i = 0; i < MAX_USER; ++i) {
		outPosts[i].clear();
		while (!inPosts[i].empty())
			inPosts[i].pop();
		followUsers[i].clear();
		followUsers[i].push_back(i);
		orderedPosts[i].sz = 0;
		orderedPosts[i].arr.clear();
	}
}

void follow(int uID1, int uID2, int timestamp)
{
	followUsers[uID1].push_back(uID2);
}

void makePost(int uID, int pID, int timestamp)
{
	Post post = Post(pID, timestamp);
	orderedPosts[uID].push(post);
	inPosts[uID].push(post);
	postWriter[pID] = uID;
}

void like(int pID, int timestamp)
{
	int uID = postWriter[pID];
	// 1000sec 이내 데이터들만 좋아요 가능 -> 이 조건이 아니라면 수정해야함 수정완료!
	if (heapIdx[pID] != -1)
		orderedPosts[uID].likePost(pID);
}

void getFeed(int uID, int timestamp, int pIDList[])
{
	vector<Post> in1000s;
	vector<Post> out1000s;
	
	for (int i = 0; i < followUsers[uID].size(); ++i) {
		vector<Post> tmp;
		int cnt = 0;
		int follower = followUsers[uID][i];

		// orderedPosts에서 Post 담기
		while (orderedPosts[follower].sz > 0 && cnt < 10) {
			Post p = orderedPosts[follower].pop();
			if (timestamp - p.time <= 1000) {
				in1000s.push_back(p);
				tmp.push_back(p);
				cnt++;
			}
		}
		while (!tmp.empty()) {
			Post p = tmp.back();
			tmp.pop_back();
			orderedPosts[follower].push(p);
		}

		// inPosts 중에서 1000s가 지난 친구들은 outPosts로 이동
		while (!inPosts[follower].empty() && (timestamp - inPosts[follower].front().time) > 1000) {
			Post p = inPosts[follower].front();
			inPosts[follower].pop();
			outPosts[follower].push_back(p);
		}

		// outPosts 에서 마지막 인덱스부터 순서대로 담기
		int outIdx = (int)outPosts[follower].size() - 1;
		while (in1000s.size() < 10 && cnt < 10 && outIdx >= 0) {
			out1000s.push_back(outPosts[follower][outIdx--]);
			cnt++;
		}
	}

	sort(in1000s.begin(), in1000s.end());
	sort(out1000s.begin(), out1000s.end(), [](const Post& lhs, const Post& rhs) {return lhs.time > rhs.time; });
	
	int cnt = 0;
	for (int i = 0; i < in1000s.size() && cnt < 10; ++i) {
		pIDList[cnt++] = in1000s[i].id;
	}
	for (int i = 0; i < out1000s.size() && cnt < 10; ++i) {
		pIDList[cnt++] = out1000s[i].id;
	}
}