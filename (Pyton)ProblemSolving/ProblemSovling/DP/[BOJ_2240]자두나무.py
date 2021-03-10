import sys

T, W = map(int, input().split())
fall = [0 for _ in range(T)]
dp = [[[-1]*(W+1) for _ in range(2)] for _ in range(T)]
for i in range(T):
    fall[i] = int(input())


# solution(0, 0, 0)
def solution(time, pos, w):
    if time == T:
        return 0

    if dp[time][pos][w] != -1:
        return dp[time][pos][w]

    feed = 1 if fall[time] == (pos+1) else 0

    res = solution(time+1, pos, w)
    if w < W:
        res = max(res, solution(time+1, 1-pos, w+1))

    res += feed
    dp[time][pos][w] = res
    return res


answer = max(solution(0, 0, 0), solution(0, 1, 1))
print(answer)
