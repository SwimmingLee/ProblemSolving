import sys
import collections

input = sys.stdin.readline

board_sz = int(input())
board = [list(map(int, input().rstrip().split())) for _ in range(board_sz)]

total_num = 0
for i in range(board_sz):
    for j in range(board_sz):
        total_num += board[i][j]

ans = 1000
dy = [-1, 1, 0, 0]
dx = [0, 0, 1, -1]

dia_dy = [1, 1, -1, -1]
dia_dx = [1, -1, -1, 1]


def isBound(ny, nx, limit_y, limit_x):
    if ny < limit_y[0] or nx < limit_x[0] or ny >= limit_y[1] or nx >= limit_x[1]:
        return True
    else:
        return False


def bfs(sy, sx, limit_y, limit_x, color, board2):
    queue = collections.deque()
    #chk = [[0] * board_sz for _ in range(board_sz)]

    queue.append((sy, sx))
    #chk[sy][sx] = True
    board2[sy][sx] = color
    sum = 0

    while queue:
        y, x = queue.popleft()
        sum += board[y][x]
        for i in range(4):
            ny = y + dy[i]
            nx = x + dx[i]

            if isBound(ny, nx, limit_y, limit_x) or board2[ny][nx]:
                continue

            board2[ny][nx] = color
            queue.append((ny, nx))
    return sum


def separte(sy, sx, d1, d2):
    board2 = [[0] * board_sz for _ in range(board_sz)]

    y, x, dir = sy, sx, 0
    while dir < 4:
        board2[y][x] = 1
        y += dia_dy[dir]
        x += dia_dx[dir]
        if y == sy or y == (sy + d1 + d2) or x == (sx + d1) or x == (sx - d2):
            dir += 1

    area1_num = bfs(sy, sx-1, (0, sy+d2), (0, sx+1), 2, board2)
    area2_num = bfs(sy+d1-1, sx+d1, (0, sy + d1 + 1),
                    (sx+1, board_sz), 3, board2)
    area3_num = bfs(sy+d1+d2, sx+d1-d2+1, (sy + d1 + 1,
                                           board_sz), (sx+d1-d2, board_sz), 4, board2)
    area4_num = bfs(sy+d2+1, sx-d2, (sy + d2, board_sz),
                    (0, sx+d1-d2), 5, board2)
    area5_num = total_num - (area1_num + area2_num + area3_num + area4_num)

    min_num = min(area1_num, area2_num, area3_num, area4_num, area5_num)
    max_num = max(area1_num, area2_num, area3_num, area4_num, area5_num)

    # print(sy, sx, d1, d2)
    # for i in range(board_sz):
    #     print(board2[i])
    # print()

    return max_num - min_num


def divid(y, x):
    max_d1 = board_sz - x
    max_d2 = x + 1

    res = 10000

    for d1 in range(1, max_d1):
        for d2 in range(1, max_d2):
            if y + d1 + d2 >= board_sz:
                continue
            tmp = separte(y, x, d1, d2)
            res = min(tmp, res)

    return res


for y in range(board_sz):
    for x in range(board_sz):
        tmp = divid(y, x)
        ans = min(tmp, ans)

print(ans)
