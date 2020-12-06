import sys
import heapq

def djk(adj, start):
    pq = []
    visited = [False for _ in range(V+1)]
    dist = [987987897 for _ in range(V+1)]

    heapq.heappush(pq, [0, start])
    dist[start] = 0
    while pq:
        acc_dist, cur = heapq.heappop(pq)
        if visited[cur]:
            continue
        visited[cur] = True
        for edge in adj[cur]:
            next, cost = edge
            if dist[next] > dist[cur] + cost:
                dist[next] = dist[cur] + cost
                heapq.heappush(pq, [dist[next], next])
    
    return dist

def djk2(adj, start, end):
    pq = []
    visited = [False for _ in range(V+1)]
    dist = [987987897 for _ in range(V+1)]

    heapq.heappush(pq, [0, start])
    dist[start] = 0
    while pq:
        acc_dist, cur = heapq.heappop(pq)
        if visited[cur]:
            continue
        if cur == end:
            break
        visited[cur] = True
        for edge in adj[cur]:
            next, cost = edge
            if dist[next] > dist[cur] + cost:
                dist[next] = dist[cur] + cost
                heapq.heappush(pq, [dist[next], next])
    
    return dist[end]
    
    
V, E, X = list(map(int, input().split()))
adj = [[] for _ in range(V+1)]
for _ in range(E):
    u, v, w = list(map(int, input().split()))
    adj[u].append([v, w])

answer = 0
dist = djk(adj, X)
for i in range(1, V+1):
    tmp = djk2(adj, i, X) + dist[i]
    if answer < tmp:
        answer = tmp

print(answer)

