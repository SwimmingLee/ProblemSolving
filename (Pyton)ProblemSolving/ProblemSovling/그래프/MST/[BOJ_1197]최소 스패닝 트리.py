import sys
import collections


def find(u):
    if parent[u] == -1:
        return u
    parent[u] = find(parent[u])
    return parent[u]


def merge(u, v):
    u = find(u)
    v = find(v)

    if u == v:
        return False

    parent[v] = u
    return True


input = sys.stdin.readline
V, E = list(map(int, input().split()))
edges = []
parent = [-1 for _ in range(V+1)]
for _ in range(E):
    u, v, w = list(map(int, input().split()))
    edges.append([u, v, w])

# 가중치가 가장 적은 것들만 정렬하기
edges.sort(key=lambda x: x[2])
# 그 중에서 하나씪 뺴면서 루프가 생기는지 확인하기
answer = 0
for edge in edges:
    w, u, v = edge
    if merge(u, v):
        answer += w
print(answer)
