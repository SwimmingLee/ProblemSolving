import sys
input = sys.stdin.readline

N = int(input())
dist = [[] for _ in range(N)]
adj = [[0 for _ in range(N)] for _ in range(N)]
for i in range(N):
    dist[i] = list(map(int, input().split()))
    for j in range(N):
        adj[i][j] = dist[i][j]

impossible = False
for k in range(N):
    for i in range(k+1, N):
        for j in range(N):
            if j == k or j == i:
                continue
            if dist[k][i] == dist[k][j] + dist[j][i]:
                adj[k][i] = adj[i][k] = 0
            elif dist[k][i] > dist[k][j] + dist[j][i]:
                impossible = True

cost = 0
for i in range(N):
    for j in range(i+1, N):
        cost += adj[i][j]
if impossible:
    print(-1)
else:
    print(cost)
