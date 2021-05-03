import sys
input = sys.stdin.readline

N = int(input())
A = [0] * (N+1)
for i in range(N):
    A[i+1] = int(input())


parent = [-1] * (N+1)


def find(u):
    if parent[u] < 0:
        return u
    parent[u] = find(parent[u])
    return parent[u]


def merge(u, v):
    u = find(u)
    v = find(v)

    if u == v:
        return False

    parent[u] += parent[v]
    parent[v] = u
    return True


answer = []
visited = [False] * (N+1)


def dfs(u):
    global answer
    answer.append(u)

    visited[u] = True
    next = A[u]
    if not visited[next]:
        dfs(next)


for i in range(1, N+1):
    if not merge(i, A[i]):
        dfs(i)

answer.sort()
print(len(answer))
for u in answer:
    print(u)
