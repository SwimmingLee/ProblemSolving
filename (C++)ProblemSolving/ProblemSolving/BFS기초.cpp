int board[10][10];

#define QUEUE_SIZE 100

struct Point {
	int y;
	int x;
	Point(int y, int x): y(y), x(x) {}
	Point() {}
};

struct Queue {
	Point arr[QUEUE_SIZE];
	int front;
	int rear;

	Queue(): front(0), rear(0) {

	}
	bool empty() {
		return front == rear;
	}
	void push(Point n) {
		arr[rear++] = n;
		rear %= QUEUE_SIZE;
	}
	Point pop() {
		Point res = arr[front++];
		front %= QUEUE_SIZE;
		return res;
	}
};

int board_sz;
void bfs_init(int N, int map[10][10])
{
	board_sz = N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			board[r][c] = map[r][c];
		}
	}
}

int bfs(int x1, int y1, int x2, int y2)
{
	x1 -= 1;
	y1 -= 1;
	x2 -= 1;
	y2 -= 1;

	int dy[] = { 0, 0, -1, 1 };
	int dx[] = { -1, 1, 0, 0 };
	int been[10][10];
	for (int r = 0; r < board_sz; r++) {
		for (int c = 0; c < board_sz; c++) {
			been[r][c] = -1;
		}
	}
	Queue q;

	q.push(Point(y1, x1));
	been[y1][x1] = 0;

	while (!q.empty()) {
		Point p1 = q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = p1.y + dy[i];
			int nx = p1.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= board_sz || nx >= board_sz || board[ny][nx] == 1 || been[ny][nx] != -1) continue;
			
			q.push(Point(ny, nx));
			been[ny][nx] = been[p1.y][p1.x] + 1;
		}
	}
	return been[y2][x2];
}
