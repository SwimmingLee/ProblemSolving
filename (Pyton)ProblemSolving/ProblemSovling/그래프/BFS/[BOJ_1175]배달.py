import collections

N, M = map(int, input().split())
board = [0] * N
dy = [0, 0, -1, 1]
dx = [1, -1, 0, 0]

answer = -1
spos, cpos1, cpos2 = 0, -1, 0

for h in range(N):
    board[h] = input()
    for w in range(M):
        if board[h][w] == 'S':
            spos = h * M + w
        elif board[h][w] == 'C':
            if cpos1 == -1:
                cpos1 = h * M + w
            else:
                cpos2 = h * M + w


def bfs(spos, cpos1, cpos2):
    dist = [[[[0] * 4 for _ in range(4)] for _ in range(M)] for _ in range(N)]
    state = 0
    dir = -1

    q = collections.deque()
    q.append([spos//M, spos % M, dir, state])

    while q:
        y, x, dir, state = q.popleft()

        if state == 3:
            return dist[y][x][dir][state]

        for next_dir in range(4):
            if dir == next_dir:
                continue

            ny = y + dy[next_dir]
            nx = x + dx[next_dir]
            if ny < 0 or nx < 0 or ny >= N or nx >= M or board[ny][nx] == '#':
                continue

            next_state = state
            if ny == cpos1 // M and nx == cpos1 % M:
                next_state |= 1
            elif ny == cpos2 // M and nx == cpos2 % M:
                next_state |= 2

            if dist[ny][nx][next_dir][next_state] == 0:
                dist[ny][nx][next_dir][next_state] = dist[y][x][dir][state] + 1
                q.append([ny, nx, next_dir, next_state])

    return -1


answer = bfs(spos, cpos1, cpos2)

print(answer)
