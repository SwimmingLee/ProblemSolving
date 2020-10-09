import sys
import collections
input = sys.stdin.readline

height, width = list(map(int, input().split()))
max_cell = height * width
board = [list(map(int, input().split())) for _ in range(height)]
dxy = [(-1, 0), (1, 0), (0, 1), (0, -1)]


def solve():
    choice = []
    answer = 0
    virus_pos = []
    safe_area = 0

    def outbound(ny, nx): return any([
        ny < 0,
        nx < 0,
        ny >= height,
        nx >= width,
    ])

    def getVirusPos():
        virus_pos = []
        nonlocal safe_area

        for h in range(height):
            for w in range(width):
                if board[h][w] == 2:
                    virus_pos.append([h, w])
                if board[h][w] != 1:
                    safe_area += 1

        return virus_pos

    def getSafeArea():
        visited = [[0] * width for _ in range(height)]
        for i in choice:
            board[i//width][i % width] = 1

        queue = collections.deque()
        for virus in virus_pos:
            visited[virus[0]][virus[1]] = 1
            queue.appendleft([virus[0], virus[1]])

        unsafe_area = 0
        while queue:
            y, x = queue.popleft()
            unsafe_area += 1

            for d in dxy:
                ny = y + d[0]
                nx = x + d[1]

                if outbound(ny, nx) or board[ny][nx] != 0 or visited[ny][nx]:
                    continue
                visited[ny][nx] = 1
                queue.append([ny, nx])

        for i in choice:
            board[i//width][i % width] = 0

        return safe_area - unsafe_area - 3

    def dfs(index, start):
        nonlocal answer
        if index == 3:
            tmp = getSafeArea()
            # print("tmp", tmp, choice)
            if tmp > answer:
                answer = tmp
            return

        for i in range(start, max_cell):
            if board[i//width][i % width] == 0:
                choice.append(i)
                dfs(index+1, i + 1)
                choice.pop()

    virus_pos = getVirusPos()
    dfs(0, 0)
    print(answer)


solve()
