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

	// ���� 
	if (vh == 0) {
		for (int r = 0; r < M; r++) {
			for (int c = 0; c < M; c++) {
				object[M - r - 1][c] = tmp_object[r][c];
			}
		}
	}
	// �¿�
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
	// dir 0: ��, 1:��, 2:��, 3:��
	
	/*
	* 1. ���� ���� ��ġ(����)�� ���� üũ�ؾ��� ���� Ž��
	* 
	* �������� �Ǵ� ��� �߿� ��ֹ��� �ֳ� Ȯ��(*��ֹ��� �־ 0�̸� �� �� ����*)
	* 1-1. �ٱ������� ������ �Ǵ� ��� - �� ��ǰ �߿��� 1�� �ִ��� Ȯ��
	* 1-2. ���ʺ��� �ٱ������� �������ִ� ��� - �׷��� �� ��ǰ(0,0).. (N,N)  �ִ� �ּҸ� �����. �߿��� 1�� �ִ��� Ȯ�� 
	*       �������� ������ �Ǵµ� �̹� �ʱ������� �������� �������� (y,x) (y+N,x) �˻� - y~y+N�� ������ ����, x�� ������ 0����
	*       �� ��ǰ�߿��� 1�� ������ �̵��� �� �ִ� ������ ��ֹ�(2)�� �ٱ������� �ֳ� Ȯ�� ������ ���� - �ű⼭ �����̴� �͵� ����
	* 
	*/

	int dy[] = { -1, 1, 0, 0 };
	int dx[] = { 0, 0, 1, -1 };
	
	// �����̵�
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