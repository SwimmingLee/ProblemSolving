import sys
import copy

input = sys.stdin.readline
fish_board = [[0] * 4 for _ in range(4)]
fish_arr = [[0, 0, 0, 0]]
for h in range(4):
    f1, d1, f2, d2, f3, d3, f4, d4 = list(map(int, input().split()))
    fish_board[h][0] = f1
    fish_board[h][1] = f2
    fish_board[h][2] = f3
    fish_board[h][3] = f4
    fish_arr.append([f1, d1, h, 0])
    fish_arr.append([f2, d2, h, 1])
    fish_arr.append([f3, d3, h, 2])
    fish_arr.append([f4, d4, h, 3])

dxy = [[-1, 0], [-1, -1], [0, -1], [1, -1], [1, 0], [1, 1], [0, 1], [-1, 1]]


def init():
    fish_arr.sort(key=lambda x: x[0])


def solve():

    def outbound(y, x): return any([
        y < 0,
        x < 0,
        y >= 4,
        x >= 4
    ])

    def moveFish(fish_board, fish_arr):
        for i in range(1, len(fish_arr)):
            life, d, y, x = fish_arr[i]
            if life == False:
                continue

            for j in range(8):
                ny = y + dxy[(d+j+7) % 8][0]
                nx = x + dxy[(d+j+7) % 8][1]

                if outbound(ny, nx) or fish_board[ny][nx] == -1:
                    continue

                front_fish_idx = fish_board[ny][nx]

                nd = d + j
                if nd > 8:
                    nd -= 8

                fish_arr[i][1:] = nd, ny, nx
                if front_fish_idx != 0:
                    fish_arr[front_fish_idx][2:] = y, x
                fish_board[y][x], fish_board[ny][nx] = front_fish_idx, i
                break

    def dfs(y, x, fish_board, fish_arr, score):
        result = 0
        fish_idx = fish_board[y][x]
        shark_dir = fish_arr[fish_idx][1]

        fish_arr[fish_idx][0] = False

        fish_board[y][x] = -1
        #print(y, x, score)
        #print(*fish_board, sep='\n')
        #print(*fish_arr, sep='\n')
        moveFish(fish_board, fish_arr)
        fish_board[y][x] = 0
        step = 1
        #print(y, x)
        #print(*fish_board, sep='\n')
        while True:
            ny = y + dxy[(shark_dir + 7) % 8][0] * step
            nx = x + dxy[(shark_dir + 7) % 8][1] * step
            # print(ny, nx)
            if outbound(ny, nx):
                break
            if fish_board[ny][nx] == 0:
                step += 1
                continue
            tmp = dfs(ny, nx, copy.deepcopy(fish_board),
                      copy.deepcopy(fish_arr), score + fish_idx)
            if result < tmp:
                result = tmp
            step += 1
        return max(result, score + fish_idx)

    init()
    answer = dfs(0, 0, fish_board, fish_arr, 0)
    print(answer)


solve()
