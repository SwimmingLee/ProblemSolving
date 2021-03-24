import sys
input = sys.stdin.readline
N, M = map(int, input().split())

# 최솟값을 2의 배수 범위로 저장
# D[i][j] = i번째 에서 2**j 개수의 범위 중 최솟값 저장
# 그러면 아래와 같이 점화식을 구할 수 있음
# D[i][j] = D[i][j-1] + D[i + (1 << (j-1))][j-1]

D = [[0 for _ in range(17)] for _ in range(N)]

for i in range(N):
    D[i][0] = int(input())

for j in range(1, 17):
    for i in range(N):
        if i + (1 << j) - 1 < N:
            D[i][j] = min(D[i][j-1], D[i + (1 << (j-1))][j-1])


def queryRangeMinimum(first, last):
    start = first - 1
    last = last - 1
    res = 1000000001
    for exp in range(16, -1, -1):
        if start + (1 << exp) - 1 <= last:
            res = min(res, D[start][exp])
            start = start + (1 << exp)
    return res


for _ in range(M):
    u, v = map(int, input().split())
    answer = queryRangeMinimum(u, v)
    print(answer)
