import collections

N, M = map(int, input().split())
adj = [[] for _ in range(N+1)]
inbound = [0 for _ in range(N+1)]
for _ in range(M):
    u, v = map(int, input().split())
    adj[u].append(v)
    inbound[v] += 1


def topological_sort():
    q = collections.deque()
    for i in range(1, N+1):
        if inbound[i] == 0:
            q.append(i)

    while q:
        cur = q.popleft()
        print(cur, end=' ')
        for next in adj[cur]:
            inbound[next] -= 1
            if inbound[next] == 0:
                q.append(next)


topological_sort()
