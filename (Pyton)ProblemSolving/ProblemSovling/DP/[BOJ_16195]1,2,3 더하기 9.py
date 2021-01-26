import sys

sys.setrecursionlimit(1000000)
mod = 1000000009
MAX_N = 1001

# dp(n, m) = dp(n-1, m-1) + dp(n-2, m-1) + dp(n-1, m-1)
cache = [[-1] * (MAX_N+1) for _ in range(MAX_N+1)]


def solve(n, m):
    if n < 0 or m < 0:
        return 0
    elif n == 0:
        return 1

    if cache[n][m] != -1:
        return cache[n][m]

    res = solve(n-1, m-1) % mod
    res += solve(n-2, m-1) % mod
    res += solve(n-3, m-1) % mod
    cache[n][m] = res % mod
    return cache[n][m]


TC = int(input())
for _ in range(TC):
    n, m = map(int, input().split())
    answer = solve(n, m)
    print(answer)
