import sys
import copy
input = sys.stdin.readline
N, M = list(map(int, input().split()))
board_ = [list(input()) for _ in range(N)]

dyx = [[-1, 0], [0, 1], [1, 0], [0, -1]]
answer = -1


def init():
    blue_pos = []
    red_pos = []
    for h in range(N):
        for w in range(M):
            if board_[h][w] == 'B':
                blue_pos = [h, w]
            elif board_[h][w] == 'R':
                red_pos = [h, w]
    return blue_pos, red_pos


def fallingBaord(pos, dir, board):
    y, x = pos
    while True:
        ny = pos[0] + dyx[dir][0]
        nx = pos[1] + dyx[dir][1]

        # 경계를 벋어난다
        if ny < 0 or nx < 0 or ny >= N or nx >= M:
            return False

       # print(board[pos[0]][pos[1]], board[ny][nx])
        #print(board[ny][nx], board[pos[0]][pos[1]])
        if board[ny][nx] == '.':
            board[pos[0]][pos[1]], board[ny][nx] = board[ny][nx], board[pos[0]][pos[1]]
            pos[0] = ny
            pos[1] = nx
        elif board[ny][nx] == 'O':
            board[pos[0]][pos[1]] = '.'
            return True
        else:
            return True if y != pos[0] or x != pos[1] else False


def dfs(depth, dir, board, red_pos, blue_pos):
    global answer
    if depth == 10:
        return

    # 구슬 내려주기
    # print(depth, dir)
    # print(*board, sep='\n')
    # print()
    red_goal = fallingBaord(red_pos, dir, board)
    blue_goal = fallingBaord(blue_pos, dir, board)
    if not red_goal:
        red_goal = fallingBaord(red_pos, dir, board)
    # print(*board, sep='\n')
    if board[blue_pos[0]][blue_pos[1]] == '.':
        return
    elif board[red_pos[0]][red_pos[1]] == '.':
        if answer == -1 or answer > depth+1:
            # print(answer)
            answer = depth+1
        return
    elif not red_goal and not blue_goal:
        return

    horizon = 0 if dir % 2 else 1
    # print("HORIZON", horizon)
    # 다음 방향 지정해주기
    for next_dir in range(4):
        if next_dir % 2 == horizon:
            # print("SDSD", next_dir)
            dfs(depth+1, next_dir, copy.deepcopy(board),
                red_pos[:], blue_pos[:])


blue_pos, red_pos = init()
for i in range(4):
    dfs(0, i, copy.deepcopy(board_), red_pos[:], blue_pos[:])
print(answer)
