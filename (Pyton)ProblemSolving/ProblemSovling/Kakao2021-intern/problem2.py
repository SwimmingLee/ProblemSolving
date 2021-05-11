def solution(places):
    answer = []

    """
    그래프 안에서 하나의 뭉태기로 모여 있어야 함
    """
    def dfs(y, x, board, N, depth):
        if depth > 2:
            return True

        if depth != 0 and board[y][x] == 'P':
            return False

        res = True
        visited[y][x] = True
        for dy, dx in [[-1, 0], [1, 0], [0, 1], [0, -1]]:
            ny = y + dy
            nx = x + dx
            if ny < 0 or nx < 0 or ny >= N or nx >= N or visited[ny][nx]:
                continue
            if board[ny][nx] != 'X':
                res = res and dfs(ny, nx, board, N, depth+1)
        return res

    for i in range(len(places)):
        board = places[i]
        N = len(board)
        visited = [[False] * N for _ in range(N)]
        result = 1
        for y in range(N):
            for x in range(N):
                if board[y][x] == 'P' and not visited[y][x]:
                    tmp = dfs(y, x, board, N, 0)
                    if tmp == False:
                        result = 0

        answer.append(result)
    return answer


print(solution([["POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"]]))
