import sys

sys.setrecursionlimit(1000000)

N = int(input())
wines = [0] * N
for i in range(N):
    wines[i] = int(input())

dp = [[0]*2 for _ in range(N)]


def solve(pos, cnt):
    if pos >= N or cnt >= 2:
        return 0

    if dp[pos][cnt] != 0:
        return dp[pos][cnt]

    t1 = solve(pos+1, cnt+1)
    t2 = solve(pos+2, 0)
    t3 = solve(pos+3, 0)
    dp[pos][cnt] = max(t1, t2, t3) + wines[pos]
    return dp[pos][cnt]


answer = max(solve(0, 0), solve(1, 0), solve(2, 0))
print(answer)
