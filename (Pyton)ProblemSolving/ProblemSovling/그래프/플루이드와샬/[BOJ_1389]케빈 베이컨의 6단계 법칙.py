import sys
input = sys.stdin.readline

inf = 987987987
N, M = map(int, input().split())
adj = [[inf for _ in range(N+1)] for _ in range(N+1)]
dist = [[0]*(N+1) for _ in range(N+1)]

for _ in range(M):
    u, v = map(int, input().split())
    adj[u][v] = adj[v][u] = 1

for i in range(1, N+1):
    for j in range(1, N+1):
        if i == j:
            dist[i][j] = 0
        else:
            dist[i][j] = adj[i][j]

for k in range(1, N+1):
    for i in range(1, N+1):
        for j in range(1, N+1):
            if dist[i][j] > dist[i][k] + dist[k][j]:
                dist[i][j] = dist[i][k] + dist[k][j]

node_num = 1
node_sum = 987987987
for i in range(1, N+1):
    psum = 0
    for j in range(1, N+1):
        psum += dist[i][j]

    if node_sum > psum:
        node_sum = psum
        node_num = i
print(node_num)
