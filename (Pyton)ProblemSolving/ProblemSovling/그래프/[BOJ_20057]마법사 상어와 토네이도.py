import sys
import math
input = sys.stdin.readline
N = int(input())
board = [[0] * N for _ in range(N)]
for i in range(N):
    board[i] = list(map(int, input().split()))

"""
1. 토네이도 방향으로 이동하며 움직여야 한다. 
  1-1. (N/2, N/2) 부터 시작한다. 왼쪽 , 아래 1번 오른쪽, 위 2번, ... 반복하다가 0,0에 오면 멈춤 

2. 움직이면서 모래를 뿌려야 한다. 
  2-1. 모래를 뿌릴 때, 모래가 이동할 수 있는 위치를 룩업 테이블로 생성
       모래가 뿌려지는 것 y // 10 floor(y / 100 * 7) 
       위치 + 뿌려지는 비율 같이 매칭되도록 
  2-2. 룩업 테이블 모든 위치를 검사하면서 보드 바깥으로 나가는 것들을 더해준다. 

"""
dy = [0, 1, 0, -1]
dx = [-1, 0, 1, 0]
y, x = N//2, N//2


spit_dy = [[-2, -1, -1, -1, 0, 1, 1, 1, 2, 0],
           [0, 1, 0, -1, 2, 1, 0, -1, 0, 1],
           [-2, -1, -1, -1, 0, 1, 1, 1, 2, 0],
           [0, -1, 0, 1, -2, -1, 0, 1, 0, -1]]

spit_dx = [[0, -1, 0, 1, -2, -1, 0, 1, 0, -1],
           [-2, -1, -1, -1, 0, 1, 1, 1, 2, 0],
           [0, 1, 0, -1, 2, 1, 0, -1, 0, 1],
           [-2, -1, -1, -1, 0, 1, 1, 1, 2, 0]]

spit_rate = [2, 10, 7, 1, 5, 10, 7, 1, 2]


def splitSand(y, x, dir):
    out_sand = 0
    sand = board[y][x]
    for i in range(10):
        ny = y + spit_dy[dir][i]
        nx = x + spit_dx[dir][i]

        scattered_sand = 0
        if i == 9:
            scattered_sand = board[y][x]
        else:
            scattered_sand = math.floor(sand * (spit_rate[i] / 100))

        if ny < 0 or nx < 0 or ny >= N or nx >= N:
            out_sand += scattered_sand
        else:
            board[ny][nx] += scattered_sand
        board[y][x] -= scattered_sand

    return out_sand


answer = 0
is_finish = False
forward_limit = 1
while not is_finish:
    for direction in range(4):
        if is_finish:
            break

        for forward_cnt in range(forward_limit):
            ny = y + dy[direction]
            nx = x + dx[direction]

            answer += splitSand(ny, nx, direction)
            y, x = ny, nx

            if y == 0 and x == 0:
                is_finish = True
                break

        if direction % 2 == 1:
            forward_limit += 1


print(answer)
