import sys
import heapq


def djk(start, end):
    pq = []
    visited = [False for _ in range(V+1)]
    dist = [987987987 for _ in range(V+1)]

    # visited[start] = True
    dist[start] = 0
    heapq.heappush(pq, [0, start])

    while pq:
        acc_dist, cur = heapq.heappop(pq)
        if cur == end:
            break
        if visited[cur]:
            continue
        visited[cur] = True
        for edge in adj[cur]:
            next, cost = edge
            # if visited[next]:
            # continue
            # visited[next] = True
            if dist[next] > dist[cur] + cost:
                dist[next] = dist[cur] + cost
                heapq.heappush(pq, [dist[next], next])

    return dist[end]


V, E = list(map(int, input().split()))
adj = [[] for _ in range(V+1)]
for _ in range(E):
    u, v, w = list(map(int, input().split()))
    adj[u].append([v, w])
    adj[v].append([u, w])
n1, n2 = list(map(int, input().split()))

answer = min(djk(1, n1) + djk(n1, n2) + djk(n2, V),
             djk(1, n2) + djk(n2, n1) + djk(n1, V))
if answer >= 987987987:
    answer = -1
print(answer)
