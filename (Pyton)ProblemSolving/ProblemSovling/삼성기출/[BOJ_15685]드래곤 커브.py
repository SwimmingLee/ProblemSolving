import sys
iput = sys.stdin.readline

dxy = [[1, 0], [0, -1], [-1, 0], [0, 1]]
N = int(input())
board = [[0]*101 for _ in range(101)]


def generateDragon(x, y, d, g):
    board[y][x] = 1
    y = y + dxy[d][1]
    x = x + dxy[d][0]
    board[y][x] = 1

    dragon = [d]
    for gen in range(g):
        dragon_idx = len(dragon)-1
        while dragon_idx >= 0:
            d = dragon[dragon_idx]
            nd = (d + 1) % 4
            dragon.append(nd)
            y = y + dxy[nd][1]
            x = x + dxy[nd][0]
            board[y][x] = 1
            dragon_idx -= 1


def getDragonBox():
    cnt = 0
    for y in range(100):
        for x in range(100):
            if board[y][x] and board[y+1][x] and board[y][x+1] and board[y+1][x+1]:
                cnt += 1
    return cnt


for _ in range(N):
    x, y, d, g = list(map(int, input().split()))
    # 드래곤 커브 성장
    generateDragon(x, y, d, g)
    # 성장된 드래곤 커브를 어떻게 저장하고 확인할까?
    # 단순하게 board 형태로 만들면 100-100을 모두 탐색해야 한다
    # 여러 드래콘 커브의 중복처리도 그렇고 단순하게 100-100을 모두 탐색하면서 찾는 것이 좋다
    #
answer = getDragonBox()
print(answer)
