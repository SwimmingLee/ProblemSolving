import sys

input = sys.stdin.readline
board_sz, n_chiken = list(map(int, input().split()))
board = [list(map(int, input().split())) for _ in range(board_sz)]

home = []
chiken = []


def solve():
    elements = []
    answer = -1

    def getChikenDist(ele):
        total_chiken_dist = 0
        for home_pos in home:
            min_chiken_dist = -1
            for i in ele:
                chiken_pos = chiken[i]
                chiken_dist = abs(
                    chiken_pos[0] - home_pos[0]) + abs(chiken_pos[1] - home_pos[1])
                if min_chiken_dist == -1 or min_chiken_dist > chiken_dist:
                    min_chiken_dist = chiken_dist

            total_chiken_dist += min_chiken_dist
        return total_chiken_dist

    def dfs(index, start, n):
        nonlocal answer
        if index == n_chiken:
            tmp = getChikenDist(elements)
            if answer == -1 or answer > tmp:
                answer = tmp
            return

        for i in range(start, n):
            elements.append(i)
            dfs(index + 1, i + 1, n)
            elements.pop()

    for i in range(board_sz):
        for j in range(board_sz):
            if board[i][j] == 1:
                home.append([i, j])
            elif board[i][j] == 2:
                chiken.append([i, j])

    dfs(0, 0, len(chiken))
    print(answer)


solve()
