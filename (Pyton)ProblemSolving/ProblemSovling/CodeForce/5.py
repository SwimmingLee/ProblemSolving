import sys


def tickSize(r, c):
    k = 0
    while r - k >= 0 and c - k >= 0 and c + k < m:
        if board[r-k][c-k] != '.' and board[r-k][c+k] != '.':
            k += 1
        else:
            break
    return k - 1


def paintTick(r, c, sz):
    for k in range(sz+1):
        board[r-k][c-k] = board[r-k][c+k] = '#'


def ticks():
    for r in range(n-1, -1, -1):
        for c in range(m):
            if board[r][c] != '.':
                sz = tickSize(r, c)
                if sz >= k:
                    paintTick(r, c, sz)

    for r in range(n):
        for c in range(m):
            if board[r][c] == '*':
                return False

    return True


input = sys.stdin.readline
TC = int(input())
while TC:
    TC -= 1
    n, m, k = list(map(int, input().split()))

    board = [0] * n
    for i in range(n):
        board[i] = list(input())

    if ticks():
        print("yes")
    else:
        print("no")
