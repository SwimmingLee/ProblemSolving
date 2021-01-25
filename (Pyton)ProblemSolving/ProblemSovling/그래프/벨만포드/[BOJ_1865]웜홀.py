import sys
input = sys.stdin.readline

TC = int(input())
for test_case in range(TC):
    N, M, W = map(int, input().split())
    edges = []
    answer = "NO"

    for _ in range(M):
        u, v, c = map(int, input().split())
        edges.append([u, v, c])
        edges.append([v, u, c])
    for _ in range(W):
        u, v, c, = map(int, input().split())
        edges.append([u, v, -c])

    costs = [0 for _ in range(N+1)]
    for k in range(N+1):
        for edge in edges:
            u, v, c = edge
            if costs[v] > costs[u] + c:
                costs[v] = costs[u] + c
                if k == N:
                    answer = "YES"
                    break

    print(answer)
