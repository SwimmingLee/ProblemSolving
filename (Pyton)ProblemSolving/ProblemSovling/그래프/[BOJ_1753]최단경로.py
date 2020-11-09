import collections
import heapq
import sys

input = sys.stdin.readline

V, E = list(map(int, input().split()))
start_node = int(input())
adj = [[] for _ in range(V+1)]
for _ in range(E):
    u, v, w = list(map(int, input().split()))
    adj[u].append([v, w])

costs = [987987987 for _ in range(V+1)]
visited = [False for _ in range(V+1)]
pq = []
heapq.heappush(pq, [0, start_node])  # !
costs[start_node] = 0

while pq:
    prev_cost, cur_node = heapq.heappop(pq)
    if visited[cur_node]:
        continue
    visited[cur_node] = True
    for edge in adj[cur_node]:
        next, cost = edge
        if costs[next] > prev_cost + cost:
            costs[next] = prev_cost + cost
            heapq.heappush(pq, [costs[next], next])

for i in range(1, V+1):
    if costs[i] >= 987987987:
        print("INF")
    else:
        print(costs[i])
