void rotate_cw(int M, int object[4][4], int count)
{
	count %= 4;
	int tmp_object[4][4];
	
	for (int i = 0; i < count; i++) {
		for (int r = 0; r < M; r++) {
			for (int c = 0; c < M; c++) {
				tmp_object[r][c] = object[r][c];
			}
		}

		for (int r = 0; r < M; r++) {
			for (int c = 0; c < M; c++) {
				object[c][M - r - 1] = tmp_object[r][c];
			}
		}
	}
}

void rotate_ccw(int M, int object[4][4], int count)
{
	count %= 4;
	int tmp_object[4][4];

	for (int i = 0; i < count; i++) {
		for (int r = 0; r < M; r++) {
			for (int c = 0; c < M; c++) {
				tmp_object[r][c] = object[r][c];
			}
		}

		for (int r = 0; r < M; r++) {
			for (int c = 0; c < M; c++) {
				object[M-c-1][r] = tmp_object[r][c];
			}
		}
	}
}

void flip(int M, int object[4][4], int vh)
{
	int tmp_object[4][4];
	for (int r = 0; r < M; r++) {
		for (int c = 0; c < M; c++) {
			tmp_object[r][c] = object[r][c];
		}
	}

	// 상하 
	if (vh == 0) {
		for (int r = 0; r < M; r++) {
			for (int c = 0; c < M; c++) {
				object[M - r - 1][c] = tmp_object[r][c];
			}
		}
	}
	// 좌우
	else if (vh == 1) {
		for (int r = 0; r < M; r++) {
			for (int c = 0; c < M; c++) {
				object[r][M-c-1] = tmp_object[r][c];
			}
		}
	}
}

int _object[4][4];
int obj_sz;
int _board[10][10];
int board_sz;
int sy, sx;

void initObject(int size, int object[4][4])
{
	obj_sz = size;
	for (int r = 0; r < obj_sz; r++) {
		for (int c = 0; c < obj_sz; c++) {
			_object[r][c] = object[r][c];
		}
	}
	sy = sx = 0;
}

void initBoard(int size, int board[10][10])
{
	board_sz = size;
	for (int r = 0; r < board_sz; r++) {
		for (int c = 0; c < board_sz; c++) {
			_board[r][c] = board[r][c];
		}
	}
}

int max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a > b ? b : a;
}

void move(int dir, int count)
{
	// dir 0: 상, 1:하, 2:우, 3:좌
	
	/*
	* 1. 보드 시작 위치(가상)로 부터 체크해야할 부위 탐색
	* 
	* 움직여야 되는 대상 중에 장애물이 있나 확인(*장애물이 있어도 0이면 갈 수 있음*)
	* 1-1. 바깥쪽으로 나가야 되는 경우 - 내 부품 중에서 1이 있는지 확인
	* 1-2. 애초부터 바깥쪽으로 나가져있는 경우 - 그러면 내 부품(0,0).. (N,N)  최대 최소를 맞춘다. 중에서 1이 있는지 확인 
	*       왼쪽으로 나가야 되는데 이미 초기지점이 왼쪽으로 가있으면 (y,x) (y+N,x) 검사 - y~y+N이 음수면 무시, x가 음수면 0으로
	*       내 부품중에서 1이 있으면 이동할 수 있는 공간에 장애물(2)나 바깥세상이 있나 확인 있으면 못감 - 거기서 움직이는 것도 멈춤
	* 
	*/

	int dy[] = { -1, 1, 0, 0 };
	int dx[] = { 0, 0, 1, -1 };
	
	// 좌측이동
	for (int i = 0; i < count; i++) {
		bool can_move = true;

		for (int r = sy; r < sy + obj_sz; r++) {
			for (int c = sx; c < sx + obj_sz; c++) {
				if (r < 0 || c < 0 || r >= board_sz || c >= board_sz) continue;
				if (_object[r - sy][c - sx] == 1) {
					int nr = r + dy[dir];
					int nc = c + dx[dir];
					if (nr < 0 || nc < 0 || nr >= board_sz || nc >= board_sz || _board[nr][nc] == 2) {
						can_move = false;
						return;
					}
				}
			}
		}


		if (can_move) {
			sy = sy + dy[dir];
			sx = sx + dx[dir];
		}
		//else {
		//}
	}
	
}

void getBoard(int board[10][10])
{
	for (int r = 0; r < obj_sz; r++) {
		for (int c = 0; c < obj_sz; c++) {
			board[r][c] = _board[r][c];
		}
	}
	for (int r = sy; r < sy + obj_sz; r++) {
		for (int c = sx; c < sx + obj_sz; c++) {
			if (r < 0 || c < 0 || r >= board_sz || c >= board_sz) {
				continue;
			}
			board[r][c] = _object[r-sy][c-sx];
		}
	}
}