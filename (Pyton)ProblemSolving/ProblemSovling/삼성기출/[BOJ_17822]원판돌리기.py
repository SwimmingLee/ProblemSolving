import sys

input = sys.stdin.readline

# 원판 회전 시키기

# 원판에서 인접하면서 같은 숫자 찾기
# 인접하면서도 같으 숫자가 있으면 모두 지우기
# 인접하면서도 같은 숫자가 없으면 원판 평균을 구하고
# 평균보다 큰 수 에서 +- 1을 처리해주기

N, M, T = list(map(int, input().split()))
board = [list(map(int, input().split())) for _ in range(N)]
dx = [-1, 1]


def rotateCircle(h, d, k):
    circle = board[h][dx[d]*k:] + board[h][:dx[d]*k]
    board[h] = circle


def searchNearNum():
    near_nums = []
    for h in range(N):
        for w in range(M):
            if board[h][w] != -1 and board[h][(w-1+M) % M] == board[h][w]:
                near_nums.append([h, w])
                near_nums.append([h, (w-1+M) % M])

    for w in range(M):
        for h in range(1, N):
            if board[h][w] != -1 and board[h-1][w] == board[h][w]:
                near_nums.append([h, w])
                near_nums.append([h-1, w])
    if near_nums:
        for num in near_nums:
            y = num[0]
            x = num[1]
            board[y][x] = -1
    else:
        sum_circle = 0
        num_circle = 0
        for h in range(N):
            for w in range(M):
                if board[h][w] != -1:
                    sum_circle += board[h][w]
                    num_circle += 1
        if num_circle == 0:
            return
        avg_circle = sum_circle / num_circle
        for h in range(N):
            for w in range(M):
                if board[h][w] != -1:
                    if board[h][w] > avg_circle:
                        board[h][w] -= 1
                    elif board[h][w] < avg_circle:
                        board[h][w] += 1


for _ in range(T):
    x, d, k = list(map(int, input().split()))
    h = x
    while h <= N:
        rotateCircle(h-1, d, k)
        h += x
    searchNearNum()


sum_circle = 0
for h in range(N):
    for w in range(M):
        if board[h][w] != -1:
            sum_circle += board[h][w]

print(sum_circle)
