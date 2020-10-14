import sys

input = sys.stdin.readline

board_sz, n_shark, n_remain = list(map(int, input().split()))
board = [list(map(int, input().split())) for _ in range(board_sz)]
shark_dirs = list(map(int, input().split()))
shark_priority_dirs = [[[]] * 4 for _ in range(n_shark)]
for i in range(n_shark):
    for j in range(4):
        shark_priority_dirs[i][j] = (list(map(int, input().split())))
dyx = [[-1, 0], [1, 0], [0, -1], [0, 1]]
# shark_idx, start_time
remain_board = [[ [] for _ in range(board_sz)] for _ in range(board_sz)]

# 맵 상태 
# 상어 상태
shark = [[] for _ in range(n_shark)]
alive_shark = [[True] for _ in range(n_shark)]
alive_shark_cnt = n_shark
def init():
    global shark
    for h in range(board_sz):
        for w in range(board_sz):
            shark_idx = board[h][w]
            if shark_idx != 0:
                shark[shark_idx -1] = [h, w]

def remainSmell(t):
    global remain_board
    for i in range(n_shark):
        if alive_shark[i]:
            y, x = shark[i]
            # print(*remain_board, sep ='\n')
            remain_board[y][x] = [i, t]


def moveShark(t):
    global alive_shark_cnt
    # global shark
    # global board
    # global alive_shark
    # global shark_dirs

    for i in range(n_shark):
        if alive_shark[i]:
            y, x = shark[i]
            d = shark_dirs[i]-1

            # 주변에 갈 수 있는 곳이 있는지 확인(냄새 없는 곳)
            shark_update = False
            for j in range(4):
                # print(shark_priority_dirs[i])
                next_dir = shark_priority_dirs[i][d][j]-1
                ny = y + dyx[next_dir][0]
                nx = x + dyx[next_dir][1]
                if ny >= 0 and nx >= 0 and ny < board_sz and nx < board_sz:
                    if len(remain_board[ny][nx]) == 0 or remain_board[ny][nx][1] + n_remain <= t:
                        # print(remain_board[ny][nx])
                        shark[i][0] = ny
                        shark[i][1] = nx
                        shark_dirs[i] = next_dir+1
                        shark_update = True
                        board[y][x] = 0
                        # print("Shark", i, d, next_dir)
                        if board[ny][nx] != 0:
                            alive_shark[i] = False
                            alive_shark_cnt -= 1
                        else:   
                            board[ny][nx] = i+1
                            
                        break
            if shark_update:
                continue
            
            # 자신의 냄새 있는 곳으로 이동할 수 있는 지 확인
            for j in range(4):
                next_dir = shark_priority_dirs[i][d][j]-1
                ny = y + dyx[next_dir][0]
                nx = x + dyx[next_dir][1]
                if ny >= 0 and nx >= 0 and ny < board_sz and nx < board_sz:
                    if len(remain_board[ny][nx]) == 0 or remain_board[ny][nx][0] == i:
                        shark[i][0] = ny
                        shark[i][1] = nx
                        shark_dirs[i] = next_dir+1
                        shark_update = True
                        board[y][x] = 0
                        if board[ny][nx] != 0:
                            alive_shark[i] = False
                            alive_shark_cnt -= 1
                        else:
                            board[ny][nx] = i+1

                        break
            if shark_update:
                continue

# 상어 이동
# 번호 순서대로 상어 이동하는 것이 좋을듯

# 맵 상태를 저장해야 한다. y, x로 남겨두는 것이 좋을 듯
# 상어의 정보를 가지고 잇는 것도 필요하다. 

# 상어 이동이 1000이 넘어가면 끝나도록 해야 한다. 

t = 0
init()
while t < 1000:
    remainSmell(t)
    moveShark(t)
    if alive_shark_cnt == 1:
        break
    t += 1
    # print(*board, sep='\n')
    # print()
print(t+1 if t < 1000 else -1)
