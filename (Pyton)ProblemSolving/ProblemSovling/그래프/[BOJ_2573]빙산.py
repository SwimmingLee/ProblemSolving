import sys
import collections

dyx = [[-1, 0], [1, 0], [0, 1], [0, -1]]


def bfs(h, w, visited):
    q = collections.deque()
    q.appendleft([h, w])
    visited[h][w] = True
    while q:
        y, x = q.popleft()
        for i in range(4):
            ny = y + dyx[i][0]
            nx = x + dyx[i][1]
            if ny < 0 or nx < 0 or ny >= N or nx >= M or visited[ny][nx] or board[ny][nx] == 0:
                continue
            q.append([ny, nx])
            visited[ny][nx] = True


def getArea(time):
    visited = [[False for _ in range(M)] for _ in range(N)]
    n_area = 0
    for h in range(N):
        for w in range(M):
            if board[h][w] != 0 and not visited[h][w]:
                # print(h, w)
                if n_area >= 1:
                    return time
                bfs(h, w, visited)
                n_area += 1
    if n_area == 0:
        return 0
    return -1


def meltIce(board):
    copy_board = [[0 for _ in range(M)] for _ in range(N)]
    for y in range(N):
        for x in range(M):
            if board[y][x] == 0:
                continue

            sea_cnt = 0
            for i in range(4):
                ny = y + dyx[i][0]
                nx = x + dyx[i][1]
                if ny < 0 or nx < 0 or ny >= N or nx >= M:
                    continue
                if board[ny][nx] == 0:
                    sea_cnt += 1
            copy_board[y][x] = max(board[y][x] - sea_cnt, 0)

    # board = copy_board
    # print(board)
    return copy_board


input = sys.stdin.readline
N, M = list(map(int, input().split()))
board = []
for _ in range(N):
    row = list(map(int, input().split()))
    board.append(row)

time = 0
while True:
    board = meltIce(board)
    time += 1
    # print(*board, sep='\n')
    answer = getArea(time)
    if answer != -1:
        break
print(answer)
