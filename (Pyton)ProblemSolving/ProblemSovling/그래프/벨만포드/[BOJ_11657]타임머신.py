import sys
N, M = map(int, input().split())
inf = 987987987
costs = [inf for _ in range(N+1)]
edges = []
for _ in range(M):
    u, v, c = map(int, input().split())
    edges.append([u, v, c])

costs[1] = 0
negative_loop = False
for k in range(N+1):
    for edge in edges:
        u, v, c = edge
        if costs[u] != inf and costs[v] > costs[u] + c:
            costs[v] = costs[u] + c
            if k == N:
                negative_loop = True

if negative_loop:
    print(-1)
else:
    for i in range(2, N+1):
        print(costs[i] if costs[i] != inf else -1)
