import sys
sys.setrecursionlimit(100000)
N = int(input())
start = input()
goal = input()

# dp(idx, left_step): idx번째 부터 시작해서 N 위치까지 가는데// i번째가 오는데 left_step번 왼쪽 회전한 만큼의 변화가 있는 상태

cache = [[-1] * 10 for _ in range(N)]


def solve(idx, left_step):
    if idx == N:
        return 0
    if cache[idx][left_step] != -1:
        return cache[idx][left_step]

    diff = int(goal[idx]) - ((int(start[idx]) + left_step) % 10)
    if diff < 0:
        diff += 10

    # idx번째 나사를 왼쪽으로 돌리는 경우
    res = solve(idx+1, (left_step+diff) % 10) + diff

    # idx번쨰 나사를 오른쪽으로 돌리는 경우
    res = min(res, solve(idx+1, left_step) + (10 - diff))

    cache[idx][left_step] = res
    return cache[idx][left_step]


print(solve(0, 0))
