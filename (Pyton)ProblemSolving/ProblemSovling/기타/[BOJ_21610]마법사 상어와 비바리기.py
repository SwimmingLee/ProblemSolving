import sys
import collections
input = sys.stdin.readline

dy = [0, -1, -1, -1, 0, 1, 1, 1]
dx = [-1, -1, 0, 1, 1, 1, 0, -1]


def moveCloud(d, s, board, q, visited):
    for i in range(len(q)):
        y, x = q[i]
        ny = (y + dy[d]*s) % N
        nx = (x + dx[d]*s) % N

        q[i] = [ny, nx]
        board[ny][nx] += 1
        visited[ny][nx] = True

    for y, x in q:
        cnt = 0
        for i in range(1, 8, 2):
            ny = y + dy[i]
            nx = x + dx[i]

            if ny < 0 or nx < 0 or ny >= N or nx >= N:
                continue

            if board[ny][nx] > 0:
                cnt += 1
        board[y][x] += cnt


def updateCloud(board, q, visited):
    nq = []

    for i in range(N):
        for j in range(N):
            if not visited[i][j]:
                if board[i][j] >= 2:
                    nq.append([i, j])
                    board[i][j] -= 2
            else:
                visited[i][j] = False

    return nq


N, M = list(map(int, input().split()))
board = [0] * N
for i in range(N):
    board[i] = list(map(int, input().split()))

q = [[N-1, 0], [N-1, 1], [N-2, 0], [N-2, 1]]
visited = [[False] * N for _ in range(N)]
for _ in range(M):
    d, s = list(map(int, input().split()))
    moveCloud(d-1, s, board, q, visited)
    q = updateCloud(board, q, visited)

answer = 0
for i in range(N):
    for j in range(N):
        answer += board[i][j]

print(answer)
