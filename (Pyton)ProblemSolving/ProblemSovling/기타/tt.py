
def rotate(query, board):
    dy = [1, 0, -1, 0]
    dx = [0, 1, 0, -1]
    x1, y1, x2, y2 = query

    cx, cy = x1, y1
    res = -1
    prev = board[x1][y1-1]
    dir = 0
    while dir != 4:
        nx = cx + dx[dir]
        ny = cy + dy[dir]

        tmp = board[cx-1][cy-1]
        board[cx-1][cy-1] = prev
        prev = tmp

        if res == -1 or res > tmp:
            res = tmp
        # print(board[cx-1][cy-1], end=' ')

        if (nx == x1 or nx == x2):
            if (ny == y1 or ny == y2):
                dir += 1
        cx = nx
        cy = ny

    return res


def solution(rows, columns, queries):
    answer = []

    # board - (rows, columns) 생성
    board = [[r*columns + c for c in range(1, columns+1)] for r in range(rows)]

    for query in queries:
        min_value = rotate(query, board)
        # print(*board, sep='\n')
        answer.append(min_value)

    return answer


print(solution(6, 6, [[2, 2, 5, 4], [3, 3, 6, 6], [5, 1, 6, 3]]))
