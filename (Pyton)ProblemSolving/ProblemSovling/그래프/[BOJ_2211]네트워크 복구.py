import sys
import heapq
input = sys.stdin.readline

def djk(adj, V, start):
    pq = []
    visited = [False for _ in range(V+1)]
    dist = [987987987 for _ in range(V+1)]

    dist[start] = 0
    heapq.heappush(pq, [dist[start], start, start])
    egdes = []
    while pq:
        acc_cost, cur, prev = heapq.heappop(pq)
        
        if visited[cur]:
            continue
        visited[cur] = True
        if cur != prev:
            egdes.append([prev, cur])
        for edge in adj[cur]:
            next, cost = edge
            if dist[next] > dist[cur] + cost:
                dist[next] = dist[cur] + cost
                heapq.heappush(pq, [dist[next], next, cur])

    return egdes
        
    

V, E = list(map(int, input().split()))
adj = [[] for _ in range(V+1)]
for _ in range(E):
    u, v, w = list(map(int, input().split()))
    adj[u].append([v, w])
    adj[v].append([u, w])

edges = djk(adj, V, 1)
print(len(edges))
for edge in edges:
    print(edge[0], edge[1])