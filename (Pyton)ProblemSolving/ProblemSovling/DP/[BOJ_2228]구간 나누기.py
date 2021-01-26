N, M = map(int, input().split())
arr = [0] * (N+1)
for i in range(1, N+1):
    arr[i] = int(input())

inf = 987987987
cache = [[-inf] * (M+1) for _ in range(N+1)]
psum = [0] * (N+1)
# dp(alpha, M) : [alpha~N) 의 범위에서 M의 구간을 가질 때의 최댓값
psum[0] = 0
psum[1] = arr[1]
for i in range(2, N+1):
    psum[i] = psum[i-1] + arr[i]


def solve(alpha, M):
    if M == 0:
        return 0
    if alpha > N:
        return -inf

    if cache[alpha][M] != -inf:
        return cache[alpha][M]

    res = -inf+1
    for k in range(N-alpha+1):
        tmp = solve(alpha+k+2, M-1) + psum[alpha+k] - psum[alpha-1]
        if res < tmp:
            res = tmp

    for k in range(1, N-alpha+1):
        tmp = solve(alpha+k, M)
        if res < tmp:
            res = tmp

    cache[alpha][M] = res
    return cache[alpha][M]


print(solve(1, M))
