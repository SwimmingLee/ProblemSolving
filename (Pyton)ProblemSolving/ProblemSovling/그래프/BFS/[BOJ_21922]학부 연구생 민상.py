import sys
import collections

input = sys.stdin.readline

UP, DOWN, LEFT, RIGHT = 0, 1, 2, 3

N, M = map(int, input().split())
board = [0] * N

visited = [[0] * M for _ in range(N)]
q = collections.deque()
answer = 0

for r in range(N):
    board[r] = list(input().split())
    for c in range(M):
        if board[r][c] == '9':
            q.append([r, c, UP])
            q.append([r, c, DOWN])
            q.append([r, c, LEFT])
            q.append([r, c, RIGHT])
            visited[r][c] = (1 << 4)-1
            answer += 1

dyx = [[-1, 0], [1, 0], [0, -1], [0, 1]]


while q:
    y, x, d = q.popleft()

    nd = d
    if board[y][x] == '1':
        if d == RIGHT:
            nd = LEFT
        elif d == LEFT:
            nd = RIGHT
    elif board[y][x] == '2':
        if d == UP:
            nd = DOWN
        elif d == DOWN:
            nd = UP
    elif board[y][x] == '3':
        if d == UP:
            nd = RIGHT
        elif d == DOWN:
            nd = LEFT
        elif d == RIGHT:
            nd = UP
        elif d == LEFT:
            nd = DOWN
    elif board[y][x] == '4':
        if d == UP:
            nd = LEFT
        elif d == DOWN:
            nd = RIGHT
        elif d == RIGHT:
            nd = DOWN
        elif d == LEFT:
            nd = UP

    ny = y + dyx[nd][0]
    nx = x + dyx[nd][1]
    if nx < 0 or ny < 0 or ny >= N or nx >= M:
        continue

    if (visited[ny][nx] & (1 << nd)) == 0:
        if visited[ny][nx] == 0:
            answer += 1
        visited[ny][nx] |= (1 << nd)
        q.append([ny, nx, nd])

print(answer)
