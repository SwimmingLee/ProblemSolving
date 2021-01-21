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


def bfs(spos, cpos, start_value, dir):
    dist = [[[0] * 4 for _ in range(M)] for _ in range(N)]
    q = collections.deque()
    q.append([spos//M, spos % M, dir])
    if dir != -1:
        dist[spos//M][spos % M][dir] = start_value

    res = []
    while q:
        y, x, dir = q.popleft()

        if y == cpos // M and x == cpos % M:
            res.append([dist[y][x][dir], dir])
            continue

        for i in range(4):
            if dir == i:
                continue

            ny = y + dy[i]
            nx = x + dx[i]
            if ny < 0 or nx < 0 or ny >= N or nx >= M or board[ny][nx] == '#':
                continue

            if dir == -1:
                dist[ny][nx][i] = 1
                q.append([ny, nx, i])
            elif dist[ny][nx][i] == 0:
                dist[ny][nx][i] = dist[y][x][dir] + 1
                q.append([ny, nx, i])

    return res


paths = bfs(spos, cpos1, 0, -1)
for path in paths:
    start_value, dir = path
    # print(path)
    candis = bfs(cpos1, cpos2, start_value, dir)
    for candi in candis:
        # print("", candi)
        if answer == -1 or answer > candi[0]:
            answer = candi[0]

paths = bfs(spos, cpos2, 0, -1)
for path in paths:
    start_value, dir = path
    candis = bfs(cpos2, cpos1, start_value, dir)
    for candi in candis:
        if answer == -1 or answer > candi[0]:
            answer = candi[0]

print(answer)
