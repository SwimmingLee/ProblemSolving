import sys
input = sys.stdin.readline

# input
width, n_line, height = list(map(int, input().split()))
board = [[0] * (width-1) for _ in range(height)]
answer = -1

for i in range(n_line):
    h, w = list(map(int, input().split()))
    board[h-1][w-1] = 1


def isSetable(idx):
    if board[idx//(width-1)][idx % (width-1)] == 1:
        return False
    if (idx % (width-1)) == 0 and (idx % (width-1)) == width-2:
        return True
    if (idx % (width-1)) == 0:
        if board[(idx+1)//(width-1)][(idx+1) % (width-1)] == 0:
            return True
        else:
            return False
    if (idx % (width-1)) == width-2:
        if board[(idx-1)//(width-1)][(idx-1) % (width-1)] == 0:
            return True
        else:
            return False
    if board[(idx+1)//(width-1)][(idx+1) % (width-1)] == 0 and board[(idx-1)//(width-1)][(idx-1) % (width-1)] == 0:
        return True

    return False


def isSuccess():
    for w in range(width):
        line_w = w
        for h in range(height):
            if line_w != width-1 and board[h][line_w]:
                line_w += 1
            elif line_w != 0 and board[h][line_w-1]:
                line_w -= 1

        if w != line_w:
            return False

    return True


def dfs(index, start):
    global board, answer
    if isSuccess():
        if answer == -1 or answer > index:
            answer = index
        return

    if index == 3:
        return

    for i in range(start, (width-1) * height):
        if isSetable(i):
            board[i//(width-1)][i % (width-1)] = 1
            dfs(index+1, i+1)
            board[i//(width-1)][i % (width-1)] = 0


dfs(0, 0)
print(answer)
