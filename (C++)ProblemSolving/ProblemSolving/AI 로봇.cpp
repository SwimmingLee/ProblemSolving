
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CALL_JOB	(100)
#define RETURN_JOB	(200)
#define BROKEN		(300)
#define REPAIR		(400)
#define CHECK		(500)

extern void init(int N);
extern int callJob(int cTime, int wID, int mNum, int mOpt);
extern void returnJob(int cTime, int wID);
extern void broken(int cTime, int rID);
extern void repair(int cTime, int rID);
extern int check(int cTime, int rID);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int N, Q, cmd;

static int run(int score)
{
	int wIDCnt = 1;
	int cTime, mNum, rID, wID, mOpt;
	int res, ans;

	scanf("%d", &N);
	init(N);

	scanf("%d", &Q);

	while (Q--)
	{
		scanf("%d", &cmd);

		switch (cmd)
		{
		case CALL_JOB:
			scanf("%d %d %d", &cTime, &mNum, &mOpt);
			res = callJob(cTime, wIDCnt, mNum, mOpt);
			scanf("%d", &ans);
			if (ans != res) {
				printf("합산 여기가 틀림 %d \n", res);
				score = 0;
			}
			wIDCnt++;
			break;
		case RETURN_JOB:
			scanf("%d %d", &cTime, &wID);
			returnJob(cTime, wID);
			break;
		case BROKEN:
			scanf("%d %d", &cTime, &rID);
			broken(cTime, rID);
			break;
		case REPAIR:
			scanf("%d %d", &cTime, &rID);
			repair(cTime, rID);
			break;
		case CHECK:
			scanf("%d %d", &cTime, &rID);
			res = check(cTime, rID);
			scanf("%d", &ans);
			if (ans != res) {
				printf("상태 여기가 틀림 %d \n", res);
				score = 0;
			}
			break;
		default:
			score = 0;
			break;
		}
	}

	return score;
}

int main()
{

	setbuf(stdout, NULL);
	freopen("C:\\Users\\swimm\\Downloads\\sample_input25.txt", "r", stdin);

	int T, score;

	scanf("%d %d", &T, &score);

	for (int tc = 1; tc <= T; tc++)
		printf("#%d %d\n", tc, run(score));

	return 0;
}


#include <set>
#include <list>
using namespace std;
#define MAX_ROBOT	50001
#define MAX_WORK	50001
struct Robot {
	int id;
	int time;
	int IQ;
};


// 스펠링 이상하지만 올바르게 하면 내 컴퓨터에선 에러남
enum {
	CENTOR, WORK, BROKE
};

struct MaxCompare {
	bool operator() (const Robot& a, const Robot& b) const {
		int aIQ = a.IQ - a.time;
		int bIQ = b.IQ - b.time;

		if (aIQ == bIQ)
			return a.id < b.id;
		else
			return aIQ > bIQ;
	}
};
struct MinCompare {
	bool operator() (const Robot& a, const Robot& b) const {
		int aIQ = a.IQ - a.time;
		int bIQ = b.IQ - b.time;

		if (aIQ == bIQ)
			return a.id < b.id;
		else
			return aIQ < bIQ;
	}
};

int state[MAX_ROBOT];
int workplace[MAX_ROBOT];

int stdTime[MAX_ROBOT];
int stdIQ[MAX_ROBOT];
set<int> work[MAX_WORK];
set<Robot, MaxCompare> maxRobots;
set<Robot, MinCompare> minRobots;


void init(int N)
{
	for (int i = 0; i < MAX_WORK; ++i) {
		work[i].clear();
	}
	maxRobots.clear();
	minRobots.clear();
	Robot robot;
	robot.IQ = 0;
	robot.time = 0;
	for (int i = 1; i <= N; ++i) {
		robot.id = i;
		maxRobots.insert(robot);
		minRobots.insert(robot);
		state[i] = CENTOR;

		stdTime[i] = 0;
		stdIQ[i] = 0;
	}
	
}

int callJob(int cTime, int wID, int mNum, int mOpt)
{
	//print();
	int ret = 0;
	// 지능이 높은 것부터.. 그러나 rID는 작아야 함
	//printf("[] ");
	if (mOpt == 0) {
		int i = 0;
		auto it = maxRobots.begin();
		while (it != maxRobots.end() && i < mNum) {
			Robot robot = *it;

			//printf(" %d ", robot.id);
			ret += robot.id;
			work[wID].insert(robot.id);
			stdIQ[robot.id] = robot.IQ + cTime - robot.time;
			workplace[robot.id] = wID;
			state[robot.id] = WORK;

			auto minIt = minRobots.find(robot);
			minRobots.erase(minIt);
			it = maxRobots.erase(it);

			i += 1;
		}
	}
	// 지능이 낮은 것부터... 그러나 rID는 작아야함
	else {
		int i = 0;
		auto it = minRobots.begin();
		while (it != minRobots.end() && i < mNum) {
			Robot robot = *it;

			//printf(" %d ", robot.id);
			ret += robot.id;
			work[wID].insert(robot.id);
			stdIQ[robot.id] = robot.IQ + cTime - robot.time;
			workplace[robot.id] = wID;
			state[robot.id] = WORK;

			auto maxIt = maxRobots.find(robot);
			maxRobots.erase(maxIt);
			it = minRobots.erase(it);

			i += 1;
		}
	}
	//printf("\n");
	return ret;
}

void returnJob(int cTime, int wID)
{
	auto it = work[wID].begin();
	while (it != work[wID].end()) {
		Robot robot;
		int rID = *it;

		state[rID] = CENTOR;
		stdTime[rID] = cTime;
		

		robot.id = rID;
		robot.IQ = stdIQ[rID];
		robot.time = cTime;


		minRobots.insert(robot);
		maxRobots.insert(robot);

		it = work[wID].erase(it);
	}
}

void broken(int cTime, int rID)
{
	if (state[rID] == WORK) {
		state[rID] = BROKE;

		int wID = workplace[rID];
		auto it = work[wID].find(rID);

		work[wID].erase(it);
	}
}

void repair(int cTime, int rID)
{
	if (state[rID] == BROKE) {
		state[rID] = CENTOR;

		Robot robot;
		robot.id = rID;
		robot.IQ = 0;
		robot.time = cTime;

		stdTime[rID] = cTime;
		stdIQ[rID] = 0;

		minRobots.insert(robot);
		maxRobots.insert(robot);
	}
}

int check(int cTime, int rID)
{
	if (state[rID] == CENTOR) {
		return cTime + stdIQ[rID] - stdTime[rID];
	}
	else if (state[rID] == WORK) {
		return -workplace[rID];
	}
	else if (state[rID] == BROKE) {
		return 0;
	}
	
	// 여기 올 일 없음
	return 0;
}


////////
#define R register
#define MAX_ROBOT 50001
#define MAX_WORK 50001
#define MAX_SIZE 200001

typedef enum {
    CENTER = 0, WORK, BROKEN
}Status;

typedef struct {
    int rID; //로봇 고유번호
    int wID;
    int startWorkingTime;
    int exceptionnTime; //지능 개발을 못하는 시간의 총합
    Status state; //로봇 상태
}Robot;

Robot robot[MAX_ROBOT];
int rCnt;


typedef struct __node {
    int rID;
    struct __node* prev;
    struct __node* next;
}Node;

Node node[MAX_SIZE];
int nodeCnt;

//각 wID 마다 일을 하러 온 로봇을 관리하는 링크드 리스트
Node Head[MAX_WORK];
Node Tail[MAX_WORK];

typedef struct {
    int rID;
    int exceptionTime;
}HeapData;

HeapData data[MAX_SIZE];
int dCnt;

struct MaxHeap {
    HeapData* heap[MAX_ROBOT];
    int heapSize = 0;
    int heapIdx[MAX_ROBOT];

    void heapInit(void)
    {
        heapSize = 0;
        for (R int i = 0; i < MAX_ROBOT; i++) {
            heapIdx[i] = 0;
        }
    }

    bool comp(HeapData* idx1, HeapData* idx2) {
        //지능지수가 높을려면 exceptionTime 이 작아야한다
        if (idx1->exceptionTime < idx2->exceptionTime) {
            return true;
        }
        else if ((idx1->exceptionTime == idx2->exceptionTime) && (idx1->rID < idx2->rID)) {
            return true;
        }
        return false;
    }

    void heapPush(HeapData* value)
    {
        if (heapSize + 1 > MAX_ROBOT)
        {
            return;
        }

        heap[heapSize] = value;
        heapIdx[heap[heapSize]->rID] = heapSize; //1

        int current = heapSize;
        while (current > 0 && comp(heap[current], heap[(current - 1) / 2]))
        {
            HeapData* temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;

            //2
            heapIdx[heap[(current - 1) / 2]->rID] = (current - 1) / 2;
            heapIdx[heap[current]->rID] = current;

            current = (current - 1) / 2;
        }

        heapSize = heapSize + 1;

        return;
    }

    HeapData* heapPop(int idx)
    {
        if (heapSize <= 0 || idx < 0) //1
        {
            return nullptr;
        }

        HeapData* value = heap[idx]; //2
        heapSize = heapSize - 1;

        heap[idx] = heap[heapSize]; //3
        heapIdx[heap[idx]->rID] = idx; //4

        int current = idx; //5
        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize)
            {
                child = current * 2 + 1;
            }
            else
            {
                child = comp(heap[current * 2 + 1], heap[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
            }

            if (comp(heap[current], heap[child]))
            {
                break;
            }

            HeapData* temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;

            //6
            heapIdx[heap[current]->rID] = current;
            heapIdx[heap[child]->rID] = child;

            current = child;
        }

        //7
        if (idx > 0) {
            current = idx; //8
            while (current > 0 && comp(heap[current], heap[(current - 1) / 2]))
            {
                HeapData* temp = heap[(current - 1) / 2];
                heap[(current - 1) / 2] = heap[current];
                heap[current] = temp;

                //9
                heapIdx[heap[(current - 1) / 2]->rID] = (current - 1) / 2;
                heapIdx[heap[current]->rID] = current;

                current = (current - 1) / 2;
            }
        }
        //10
        heapIdx[value->rID] = 0;
        return value;
    }
};

MaxHeap maxheap;

struct MinHeap {
    HeapData* heap[MAX_ROBOT];
    int heapSize = 0;
    int heapIdx[MAX_ROBOT];

    void heapInit(void)
    {
        heapSize = 0;
        for (R int i = 0; i < MAX_ROBOT; i++) {
            heapIdx[i] = 0;
        }
    }

    bool comp(HeapData* idx1, HeapData* idx2) {
        if (idx1->exceptionTime > idx2->exceptionTime) {
            return true;
        }
        else if ((idx1->exceptionTime == idx2->exceptionTime) && (idx1->rID < idx2->rID)) {
            return true;
        }
        return false;
    }

    void heapPush(HeapData* value)
    {
        if (heapSize + 1 > MAX_ROBOT)
        {
            return;
        }

        heap[heapSize] = value;
        heapIdx[heap[heapSize]->rID] = heapSize; //1

        int current = heapSize;
        while (current > 0 && comp(heap[current], heap[(current - 1) / 2]))
        {
            HeapData* temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;

            //2
            heapIdx[heap[(current - 1) / 2]->rID] = (current - 1) / 2;
            heapIdx[heap[current]->rID] = current;

            current = (current - 1) / 2;
        }

        heapSize = heapSize + 1;

        return;
    }

    HeapData* heapPop(int idx)
    {
        if (heapSize <= 0 || idx < 0) //1
        {
            return nullptr;
        }

        HeapData* value = heap[idx]; //2
        heapSize = heapSize - 1;

        heap[idx] = heap[heapSize]; //3
        heapIdx[heap[idx]->rID] = idx; //4

        int current = idx; //5
        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize)
            {
                child = current * 2 + 1;
            }
            else
            {
                child = comp(heap[current * 2 + 1], heap[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
            }

            if (comp(heap[current], heap[child]))
            {
                break;
            }

            HeapData* temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;

            //6
            heapIdx[heap[current]->rID] = current;
            heapIdx[heap[child]->rID] = child;

            current = child;
        }

        //7
        if (idx > 0) {
            current = idx; //8
            while (current > 0 && comp(heap[current], heap[(current - 1) / 2]))
            {
                HeapData* temp = heap[(current - 1) / 2];
                heap[(current - 1) / 2] = heap[current];
                heap[current] = temp;

                //9
                heapIdx[heap[(current - 1) / 2]->rID] = (current - 1) / 2;
                heapIdx[heap[current]->rID] = current;

                current = (current - 1) / 2;
            }
        }
        //10
        heapIdx[value->rID] = 0;
        return value;
    }
};

MinHeap minheap;


void init(int N) {
    //wID에 따른 링크드리스트 초기화
    for (R int i = 0; i < MAX_WORK; i++) {
        Head[i].next = &Tail[i];
        Tail[i].prev = &Head[i];
    }

    rCnt = 0;
    nodeCnt = 0;
    dCnt = 0;

    maxheap.heapInit();
    minheap.heapInit();

    //N개의 로봇이 센터에 있다.
    for (R int i = 1; i <= N; i++) {
        R Robot* newRobot = &robot[i];
        newRobot->rID = i;
        newRobot->wID = 0;
        newRobot->startWorkingTime = 0;
        newRobot->exceptionnTime = 0;
        newRobot->state = CENTER;


        R HeapData* d = &data[dCnt++];
        d->rID = i;
        d->exceptionTime = 0;

        maxheap.heapPush(d);
        minheap.heapPush(d);
    }

}
//wID 의 작업에 로봇이 투입
//고장나거나 작업중인 로봇은 투입되지 않는다.
int callJob(int cTime, int wID, int mNum, int mOpt) {
    R int cnt = 0;
    R int ret = 0;
    if (mOpt > 0) { //낮은 지능 우선 방식
        while (cnt != mNum) {
            R HeapData* r = minheap.heapPop(0);
            if (robot[r->rID].state == CENTER) { //작업에 투입 가능

                robot[r->rID].state = WORK;
                robot[r->rID].wID = wID;
                robot[r->rID].startWorkingTime = cTime; //return 되는 시각에서 이 시각을 빼주면 일을 한 시간이 된다. 즉 지능개발에서 제외되어야 할 시간

                ret += r->rID; //고유번호를 합한 값

                //wID 에 노드를 추가. 꼬리 앞에 추가
                R Node* add = &node[nodeCnt++];
                add->rID = r->rID;
                add->next = &Tail[wID];
                Tail[wID].prev->next = add;
                add->prev = Tail[wID].prev;
                Tail[wID].prev = add;

                cnt++;
            }
            //minheap 에서 pop 한 데이터는 maxheap 에서도 빼준다. 동기화
            maxheap.heapPop(maxheap.heapIdx[r->rID]);
        }
    }
    else { //높은 지능 우선 방식
        while (cnt != mNum) {
            R HeapData* r = maxheap.heapPop(0);

            if (robot[r->rID].state == CENTER) { //작업에 투입 가능

                robot[r->rID].state = WORK;
                robot[r->rID].wID = wID;
                robot[r->rID].startWorkingTime = cTime; //return 되는 시각에서 이 시각을 빼주면 일을 한 시간이 된다. 즉 지능개발에서 제외되어야 할 시간

                ret += r->rID; //고유번호를 합한 값

                //wID 에 노드를 추가. 꼬리 앞에 추가
                R Node* add = &node[nodeCnt++];
                add->rID = r->rID;
                add->next = &Tail[wID];
                Tail[wID].prev->next = add;
                add->prev = Tail[wID].prev;
                Tail[wID].prev = add;

                cnt++;
            }
            //maxheap 에서 pop한 데이터는minheap 에서도 빼주자
            minheap.heapPop(minheap.heapIdx[r->rID]);
        }
    }

    return ret;
}

//센터로 복귀하고 트레이닝 바로 시작
//투입된 로봇이 고장나 복귀 못하는 경우도 있다.
void returnJob(int cTime, int wID) {
    for (R Node* p = Head[wID].next; p != &Tail[wID]; p = p->next) {
        R Robot* r = &robot[p->rID];
        r->state = CENTER;
        r->exceptionnTime += (cTime - r->startWorkingTime);
        r->wID = 0;

        R HeapData* d = &data[dCnt++];
        d->rID = p->rID;
        d->exceptionTime = r->exceptionnTime;

        maxheap.heapPush(d);
        minheap.heapPush(d);
    }

    //링크드리스트 초기화
    Head[wID].next = &Tail[wID];
    Tail[wID].prev = &Head[wID];
}

//이미 고장 났거나 센터에서 트레이닝 중인 경우 무시
void broken(int cTime, int rID) {
    if (robot[rID].state == BROKEN || robot[rID].state == CENTER) {
        return;
    }

    robot[rID].state = BROKEN;

    //링크드 리스트에서 삭제
    for (R Node* p = Head[robot[rID].wID].next; p != &Tail[robot[rID].wID]; p = p->next) {
        if (p->rID == rID) {
            //삭제
            p->prev->next = p->next;
            p->next->prev = p->prev;
            break;
        }
    }

}

//해당 로봇이 고장이 아닌 경우 무시
void repair(int cTime, int rID) {
    if (robot[rID].state != BROKEN) {
        return;
    }

    robot[rID].state = CENTER;
    robot[rID].exceptionnTime = cTime;
    robot[rID].wID = 0;

    //다시 일을 할수 있음. 힙에 넣자
    R HeapData* d = &data[dCnt++];
    d->rID = rID;
    d->exceptionTime = cTime;

    maxheap.heapPush(d);
    minheap.heapPush(d);
}

int check(int cTime, int rID) {
    if (robot[rID].state == BROKEN) {
        return 0;
    }
    else if (robot[rID].state == WORK) {
        return -robot[rID].wID;
    }
    else {
        return cTime - robot[rID].exceptionnTime;
    }
}