N, L, R = map(int, input().split())
mod = 1000000007
MAX_N = 101
cache = [[[-1] * MAX_N for _ in range(MAX_N)] for _ in range(MAX_N)]


def solve(N, L, R):
    if N < L or N < R:
        return 0
    if L == 0 or R == 0:
        return 0
    if N == 1:
        return 1

    if cache[N][L][R] != -1:
        return cache[N][L][R]

    res = solve(N-1, L-1, R)
    res += solve(N-1, L, R-1)
    res += (solve(N-1, L, R) * (N-2))
    res %= mod

    cache[N][L][R] = res
    return res


print(solve(N, L, R))
