import sys
import collections

input = sys.stdin.readline
N, M = list(map(int, input().split()))
dyx = [[-1, 0], [1, 0], [0, 1], [0, -1]]
board = []
for _ in range(N):
    row = input()
    board.append(row)

q = collections.deque()
q.append([0, 0, 0])
been = [[[0 for _ in range(M)] for _ in range(N)] for _ in range(2)]
been[0][0][0] = 1

answer = -1
while q:
    jump, y, x = q.popleft()
    if y == N-1 and x == M-1:
        answer = been[jump][y][x]
        break

    for i in range(4):
        ny = y + dyx[i][0]
        nx = x + dyx[i][1]

        if nx < 0 or ny < 0 or ny >= N or nx >= M:
            continue

        if board[ny][nx] == '0' and been[jump][ny][nx] == 0:
            been[jump][ny][nx] = been[jump][y][x] + 1
            q.append([jump, ny, nx])

        if board[ny][nx] == '1' and jump == 0 and been[jump+1][ny][nx] == 0:
            q.append([jump+1, ny, nx])
            been[jump+1][ny][nx] = been[jump][y][x] + 1

print(answer)
