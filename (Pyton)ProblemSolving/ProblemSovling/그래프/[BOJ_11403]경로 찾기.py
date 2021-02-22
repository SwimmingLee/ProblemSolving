import sys
input = sys.stdin.readline

N = int(input())
adj = [[] for _ in range(N)]
for h in range(N):
    adj[h] = list(map(int, input().split()))

inf = 987987987
dist = [[inf for _ in range(N)] for _ in range(N)]

for i in range(N):
    for j in range(N):
        if adj[i][j] == 1:
            dist[i][j] = 1
        else:
            dist[i][j] = inf

for k in range(N):
    for i in range(N):
        for j in range(N):
            if dist[i][j] > dist[i][k] + dist[k][j]:
                dist[i][j] = dist[i][k] + dist[k][j]

for i in range(N):
    for j in range(N):
        if dist[i][j] >= inf:
            print(0, end=' ')
        else:
            print(1, end=' ')
    print()
