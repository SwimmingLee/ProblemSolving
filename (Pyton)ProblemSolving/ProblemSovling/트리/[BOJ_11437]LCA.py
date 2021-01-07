import sys
import collections
input = sys.stdin.readline


# step1) 두 노드를 같은 깊이로 만든다.
# step1-1)각 노드의 깊이를 알아야 한다.
# step2) 두 노드를 하나 씩 올려가면서 같아 자니느 지점을 찾는다.

N = int(input())
tree = [[] for _ in range(N+1)]

for _ in range(N-1):
    u, v = map(int, input().split())
    tree[u].append(v)
    tree[v].append(u)

visitied = [False for _ in range(N+1)]
depth = [0] * (N+1)
parent = [0] * (N+1)
p = [[0] * (20) for _ in range(N+1)]

depth[1] = 0
q = collections.deque()
q.append(1)
visitied[1] = True

while q:
    x = q.popleft()
    for next in tree[x]:
        if visitied[next]:
            continue
        depth[next] = depth[x] + 1
        parent[next] = x
        visitied[next] = True
        q.append(next)

for i in range(1, N+1):
    p[i][0] = parent[i]

j = 1
while (1 << j) < N:
    for i in range(1, N+1):
        if p[i][j-1] != 0:
            p[i][j] = p[p[i][j-1]][j-1]
    j += 1


def lca(u, v):
    if depth[u] < depth[v]:
        u, v = v, u
    log = 1
    while (1 << log) <= depth[u]:
        log += 1
    log -= 1

    for i in range(log, -1, -1):
        if depth[u] - (1 << i) >= depth[v]:
            u = p[u][i]

    if u == v:
        return u
    else:
        for i in range(log, -1, -1):
            if p[u][i] != 0 and p[u][i] != p[v][i]:
                u = p[u][i]
                v = p[v][i]
        return parent[u]


M = int(input())
for _ in range(M):
    u, v = map(int, input().split())
    ancestor = lca(u, v)
    print(ancestor)
