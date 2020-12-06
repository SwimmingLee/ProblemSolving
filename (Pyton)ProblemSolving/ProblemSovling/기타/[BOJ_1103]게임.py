# 이미 같은 자리로 오게 된다면 무한 루프가 생길 수 있음 바로 탈출
# 가장 오래동안 머물고 싶음. 음 특정 지점에서 갈 수 있는 최대의 수를 DP로 갖고 있으면 되겠는데
# 그니까 DFS 방식으로 돌리긴 하는데, 특정 지점에서 갈 수 있는 최대 수를 기록하고 있는거지

import sys
limit_number = 15000
sys.setrecursionlimit(limit_number)
input = sys.stdin.readline
N, M = list(map(int, input().split()))
board = [0 for _ in range(N)]
cache = [[-1 for _ in range(M)] for _ in range(N)]
visited = [[False for _ in range(M)] for _ in range(N)]
for row in range(N):
    board[row] = input()

dyx = [[0, 1], [0, -1], [1, 0], [-1, 0]]


# y,x에서 몇 칸 더 갈 수 있는지 판단하기
def dfs(y, x):
    global visited, cache

    if cache[y][x] != -1:
        return cache[y][x]

    def isOutBind(y, x): return any([
        y < 0,
        y >= N,
        x < 0,
        x >= M
    ])

    res = 0
    for dir in range(4):
        ny = y + dyx[dir][0] * int(board[y][x])
        nx = x + dyx[dir][1] * int(board[y][x])

        if isOutBind(ny, nx) or board[ny][nx] == 'H':
            continue

        if visited[ny][nx] == True:
            print(-1)
            exit()
            return 9999
        visited[ny][nx] = True
        res = max(res, dfs(ny, nx) + 1)
        visited[ny][nx] = False

    cache[y][x] = res
    return cache[y][x]


answer = dfs(0, 0)+1
if answer >= 9999:
    answer = -1
print(answer)


# 5 7
# 3994995
# 9999999
# 4H99399
# 9999999
# 2993994


# 4 3
# 133
# 5HH
# HHH
# 21H

# 3 4
# 3552
# 5555
# 2553

# 24 24
# 12H12H12H12H12H12H12H12H
# 2HH2HH2HH2HH2HH2HH2HH2HH
# HHHHHHHHHHHHHHHHHHHHHHHH
# 12H12H12H12H12H12H12H12H
# 2HH2HH2HH2HH2HH2HH2HH2HH
# HHHHHHHHHHHHHHHHHHHHHHHH
# 12H12H12H12H12H12H12H12H
# 2HH2HH2HH2HH2HH2HH2HH2HH
# HHHHHHHHHHHHHHHHHHHHHHHH
# 12H12H12H12H12H12H12H12H
# 2HH2HH2HH2HH2HH2HH2HH2HH
# HHHHHHHHHHHHHHHHHHHHHHHH
# 12H12H12H12H12H12H12H12H
# 2HH2HH2HH2HH2HH2HH2HH2HH
# HHHHHHHHHHHHHHHHHHHHHHHH
# 12H12H12H12H12H12H12H12H
# 2HH2HH2HH2HH2HH2HH2HH2HH
# HHHHHHHHHHHHHHHHHHHHHHHH
# 12H12H12H12H12H12H12H12H
# 2HH2HH2HH2HH2HH2HH2HH2HH
# HHHHHHHHHHHHHHHHHHHHHHHH
# 12H12H12H12H12H12H12H12H
# 2HH2HH2HH2HH2HH2HH2HH2HH
# HHHHHHHHHHHHHHHHHHHHHHHH
