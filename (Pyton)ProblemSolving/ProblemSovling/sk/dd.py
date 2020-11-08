import collections

elements = []


def dfs(index, n_rider):
    global elements
    if index >= n_rider:
        print(elements)
        return

    for i in range(n_rider):
        if i not in elements:
            elements.append(i)
            dfs(index+1, n_rider)
            elements.pop()


def solution(n, walls, riders, s, e):
    board = [[0]*n for _ in range(n)]
    for wall in walls:
        y, x = wall
        board[y][x] = 1

    # 각 라이더가 걸리는 시간을 구하면 된다.
    # 간단하게 BFS로 돌리면 됨
    n_rider = len(riders)
    for i in range(n_rider):
        q = collections.deque
        q.append(riders[i])
        while q:
            cur = q.pop()

    # 어느 라이더가 어느 짐을 옮기느냐를 선택해야 한다.
    dfs(0, n_rider)
    answer = 0
    return answer
