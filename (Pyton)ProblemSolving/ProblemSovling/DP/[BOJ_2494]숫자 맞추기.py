import sys
sys.setrecursionlimit(100000)
N = int(input())
start = input()
goal = input()

# dp(idx, left_step): idx번째 부터 시작해서 N 위치까지 가는데// i번째가 오는데 left_step번 왼쪽 회전한 만큼의 변화가 있는 상태에서 목표 값까지 회전하는데 필요한 회전수

cache = [[-1] * 10 for _ in range(N)]
via = [[-1] * 10 for _ in range(N)]
mstep = [-1] * N
next = [[-1] * 10 for _ in range(N)]


def solve(idx, left_step, step):
    if idx == N:
        return 0
    if cache[idx][left_step] != -1:
        # if mstep[idx] == -1 or mstep[idx] > cache[idx][left_step]+step:
        #     mstep[idx] = cache[idx][left_step]+step
        #     # next[idx] = left_step
        #     # via[idx][left_step] = diff - 10
        return cache[idx][left_step]

    diff = int(goal[idx]) - ((int(start[idx]) + left_step) % 10)
    if diff < 0:
        diff += 10

    # idx번째 나사를 왼쪽으로 돌리는 경우
    res = solve(idx+1, (left_step+diff) % 10, step+diff) + diff
    # if mstep[idx] == -1 or mstep[idx] > res+step:
    # mstep[idx] = res+step
    next[idx][left_step] = (left_step+diff) % 10
    via[idx][left_step] = diff

    # idx번쨰 나사를 오른쪽으로 돌리는 경우
    tmp = solve(idx+1, left_step, step + 10 - diff) + (10 - diff)
    # if mstep[idx] == -1 or mstep[idx] > res+step:
    # mstep[idx] = res+step
    if res > tmp:
        res = tmp
        next[idx][left_step] = left_step
        via[idx][left_step] = diff - 10

    cache[idx][left_step] = res
    return cache[idx][left_step]


print(solve(0, 0, 0))
print(1, via[0][0])
nn = next[0][0]
for i in range(1, N):
    # print("[]", i, nn)
    print(i+1, via[i][nn])
    nn = next[i][nn]
