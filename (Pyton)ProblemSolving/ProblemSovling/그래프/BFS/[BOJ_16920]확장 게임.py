import sys
import collections
import copy
input = sys.stdin.readline

N, M, P = map(int, input().split())
S = list(map(int, input().split()))

board = [0] * N
for h in range(N):
    board[h] = input()

players_area = [0] * (P+1)
visited = [[False] * M for _ in range(N)]


def init():
    global players_area
    palyers_q = [collections.deque() for _ in range(P+1)]
    for h in range(N):
        for w in range(M):
            if board[h][w] >= '0' and board[h][w] <= '9':
                q_num = int(board[h][w])
                palyers_q[q_num].append([h, w])
                players_area[q_num] += 1
                visited[h][w] = True
    return palyers_q


def bfs(idx, visited, step):
    global players_q
    q = players_q[idx]
    # nq = collections.deque()
    cnt = 0
    for _ in range(step):
        q_sz = len(q)
        if q_sz == 0:
            break
        for _ in range(q_sz):
            y, x = q.popleft()
            for ny, nx in [[y+1, x], [y-1, x], [y, x+1], [y, x-1]]:
                if ny < 0 or ny >= N or nx < 0 or nx >= M or visited[ny][nx] or board[ny][nx] == '#':
                    continue
                visited[ny][nx] = True
                cnt += 1
                q.append([ny, nx])
        # q = copy.deepcopy(nq)
    # players_q[idx] = copy.deepcopy(nq)
    return cnt


players_q = init()


while True:
    # 각 셀별로 번갈아 가면서 bfs 실행(사이즈 입력하면서 실행)
    # 이거 하는 도중에 각 셀별로 얼마나 차있는지 확인
    # bfs에서 이동헀는지 안했는지 true/false 반환
    total_area = 0
    for i in range(1, P+1):
        area = bfs(i, visited, S[i-1])
        players_area[i] += area
        total_area += area
    if total_area == 0:
        break

for i in range(1, P+1):
    print(players_area[i], end=' ')
# print()
# print(*board)
