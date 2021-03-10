import sys

input = sys.stdin.readline

N, M, K = map(int, input().split())
edges = [[] for _ in range(N+1)]
dp = [[0] * M for _ in range(N+1)]
for _ in range(K):
    a, b, c, = map(int, input().split())
    if a >= b:
        continue
    edges[a].append([b, c])

for i in range(1, N+1):
    edges[i].sort(key=lambda x: (x[0], -x[1]))


def solution(city, cnt):
    if dp[city][cnt] != 0:
        return dp[city][cnt]

    # 도착
    if city == N:
        return 0

    # 갈 수 있는 횟수를 초과해 버릴 때
    if cnt == M-1:
        return -987987987

    # 도착 못 했지만 더 이상 갈 곳이 없을 때
    if len(edges[city]) == 0:
        return -987987987

    dp[city][cnt] = -987987987
    for edge in edges[city]:
        next_city, cost = edge
        dp[city][cnt] = max(solution(next_city, cnt+1) + cost, dp[city][cnt])

    return dp[city][cnt]


answer = solution(1, 0)
print(answer)
