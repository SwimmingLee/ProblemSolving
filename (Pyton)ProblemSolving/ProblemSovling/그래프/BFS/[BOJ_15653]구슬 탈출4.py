import sys
import collections
input = sys.stdin.readline

N, M = map(int, input().split())
board = [0] * N
red, blue = 0, 0
dy = [0, 0, 1, -1]
dx = [1, -1, 0, 0]
for h in range(N):
    board[h] = input()
    for w in range(M):
        if board[h][w] == 'R':
            red = h * M + w
        elif board[h][w] == 'B':
            blue = h * M + w


def move(red, blue, dir):
    ry, rx = red // M, red % M
    by, bx = blue // M, blue % M
    status = 0

    while True:
        ny = ry + dy[dir]
        nx = rx + dx[dir]

        if board[ny][nx] == 'O':
            status |= 1
            ry = rx = -1
            break

        if (ny == by and nx == bx) or board[ny][nx] == '#':
            break

        ry, rx = ny, nx

    while True:
        ny = by + dy[dir]
        nx = bx + dx[dir]

        if board[ny][nx] == 'O':
            status |= 2
            by = bx = -1
            break

        if (ny == ry and nx == rx) or board[ny][nx] == '#':
            break

        by, bx = ny, nx

    while ry != -1:
        ny = ry + dy[dir]
        nx = rx + dx[dir]

        if board[ny][nx] == 'O':
            status |= 1
            ry = rx = -1
            break

        if (ny == by and nx == bx) or board[ny][nx] == '#':
            break

        ry, rx = ny, nx

    red = ry * M + rx
    blue = by * M + bx
    if status == 0:
        return [2, red, blue]
    elif status & 2:
        return [0, red, blue]
    else:
        return [1, red, blue]


def bfs(red, blue):
    answer = -1
    q = collections.deque()
    dist = [[-1] * (N*M) for _ in range(N*M)]

    q.append([red, blue])
    dist[red][blue] = 0

    while q:
        red, blue = q.popleft()
        for i in range(4):
            status, next_red, next_blue = move(red, blue, i)

            if status == 0:
                continue
            elif status == 1:
                answer = dist[red][blue] + 1
                return answer

            if dist[next_red][next_blue] != -1:
                continue

            dist[next_red][next_blue] = dist[red][blue] + 1
            q.append([next_red, next_blue])

    return answer


answer = bfs(red, blue)
print(answer)
