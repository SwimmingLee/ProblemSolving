import sys
cache = [[-1]*1001 for _ in range(1001)]
mod = 1000000009

sys.setrecursionlimit(100000)


def solve(n, m):
    if n < 0:
        return 0
    elif n == 0 and m == 0:
        return 1

    if cache[n][m] != -1:
        return cache[n][m]

    res = solve(n-1, m-1) % mod
    res += solve(n-2, m-1) % mod
    res += solve(n-3, m-1) % mod
    cache[n][m] = res % mod
    return cache[n][m]


T = int(input())
for _ in range(T):
    n, m = map(int, input().split())
    answer = solve(n, m)
    print(answer)

# dp(n, m) = dp(n-1, m)
# dp(1, 1)
