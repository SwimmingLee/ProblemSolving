N = int(input())
M = int(input())
edges = []
for _ in range(M):
    u, v, c = list(map(int, input().split()))
    edges.append([u, v, c])

parent = [-1 for _ in range(N+1)]


def find(u):
    if parent[u] == -1:
        return u
    else:
        parent[u] = find(parent[u])
        return parent[u]


def merge(u, v):
    u = find(u)
    v = find(v)

    if u == v:
        return -1

    parent[u] = v


answer = 0
edges.sort(key=lambda x: x[2])
for edge in edges:
    u, v, c = edge
    if merge(u, v) != -1:
        answer += c

print(answer)
