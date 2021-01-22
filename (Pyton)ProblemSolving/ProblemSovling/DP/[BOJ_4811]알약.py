import sys
input = sys.stdin.readline

cache = []


def getDrug(full, half):
    global cache
    if cache[full][half] != -1:
        return cache[full][half]

    if full == 0:
        return 1
    if half == 0:
        cache[full][half] = getDrug(full-1, half+1)
        return cache[full][half]

    cache[full][half] = getDrug(full-1, half+1) + getDrug(full, half-1)
    return cache[full][half]


while True:
    N = int(input())
    if N == 0:
        break

    cache = [[-1] * ((2 * N)+1) for _ in range(N+1)]
    ans = getDrug(N, 0)
    print(ans)
