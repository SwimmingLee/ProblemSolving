import sys

input = sys.stdin.readline
N = 10
board = [0] * N
triangles = []
for i in range(N):
    board[i] = input()

"""
1. BFS/DFS로 1인 지점 확인
  1인 지점이 여러 개 있으면 바로 0 리턴
  1인 지점에서 꼭지점을 구할 수 있을까? LT, RB를 구한다
  LT==RB면 안됨(0 리턴) 

2. 어떤 방향인지 검사
  LT, RB 안에서 이등변사각형을 이루는지 검사(상하좌우 모두)
  상하좌우 검사해서 하나라도 이등변 삼각형이 되면 됨? oo

"""
sy, sx = 9, 9
ey, ex = 0, 0

def dfs(y, x, board, visited):
    global sy, sx, ey, ex

    visited[y][x] = True
    if sy > y:
        sy = y
    if ey < y:
        ey = y
    if sx > x:
        sx = x
    if ex < x:
        ex = x

    for dy, dx in [[-1, 0], [1, 0], [0, 1], [0, -1]]:
        ny = y + dy
        nx = x + dx
        if ny < 0 or nx < 0 or ny >= N or nx >= N or visited[ny][nx]:
            continue
        
        if board[ny][nx] == '1':
            dfs(ny, nx, board, visited)

def chkLeftTriangle():
    offset = 0
    for x in range(ex, sx-1, -1):
        # print("d", sy + offset, ey - offset)
        for y in range(sy, ey+1):
            if (sy + offset) <= y <= (ey - offset):
                if board[y][x] != '1':
                    return False
            else:
                if board[y][x] != '0':
                    return False
        offset += 1
    if offset != (ey-sy)//2 + 1 or (ey-sy)%2 != 0:
        return False
    return True

def chkRightTriangle():
    offset = 0
    for x in range(sx, ex+1):
        for y in range(sy, ey+1):
            if (sy + offset) <= y <= (ey - offset):
                if board[y][x] != '1':
                    return False
            else:
                if board[y][x] != '0':
                    return False
        offset += 1
    
    
    if offset != (ey-sy)//2 + 1 or (ey-sy)%2 != 0:
        return False
    return True

def chkUpTriangle():
    offset = 0
    for y in range(ey, sy-1, -1):
        for x in range(sx, ex+1):
            if (sx + offset) <= x <= (ex - offset):
                if board[y][x] != '1':
                    return False
            else:
                if board[y][x] != '0':
                    return False
        offset += 1
    if offset != (ex-sx)//2 + 1 or (ex-sx)%2 != 0:
        return False
    return True

def chkDownTriangle():
    offset = 0
    for y in range(sy, ey+1):
        for x in range(sx, ex+1):
            if (sx + offset) <= x <= (ex - offset):
                if board[y][x] != '1':
                    return False
            else:
                if board[y][x] != '0':
                    return False
        offset += 1
    if offset != (ex-sx)//2 + 1 or (ex-sx)%2 != 0:
        return False
    return True

visited = [[False] * N for _ in range(N)]
block_cnt = 0
for y in range(N):
    for x in range(N):
        if visited[y][x] or board[y][x] == '0':
            continue
        dfs(y, x, board, visited)
        block_cnt += 1

answer = []
if block_cnt != 1 or sy == ey:
    print(0)
else:
    is_ok = True
    # print(sy, ey)
    # print(sx, ex)
    if chkRightTriangle():
        answer = [[(sy+ey)//2, ex], [sy, sx], [ey, sx]]
    elif chkLeftTriangle():
        answer = [[(sy+ey)//2, sx], [sy, ex], [ey, ex]]
    elif chkUpTriangle():
        answer = [[sy, (sx+ex)//2], [ey, sx], [ey, ex]]
    elif chkDownTriangle():
        answer = [[ey, (sx+ex)//2], [sy, sx], [sy, ex]]
    else:
        is_ok = False

    if is_ok:
        answer.sort()
        for y, x in answer:
            print(y+1, x+1)
    else:
        print(0)