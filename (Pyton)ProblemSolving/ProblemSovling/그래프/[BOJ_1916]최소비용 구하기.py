import sys
import heapq
import collections

input = sys.stdin.readline

n_city = int(input())
n_bus = int(input())
adj = [[] for _ in range(n_city+1)]
costs = [987987987 for _ in range(n_city+1)]

for _ in range(n_bus):
    u, v, w = list(map(int, input().split()))
    adj[u].append([v, w])
    #adj[v].append([u, w])

start, end = list(map(int, input().split()))
pq = []
heapq.heappush(pq, [0, start])
costs[start] = 0

while pq:
    prev_cost, cur = heapq.heappop(pq)
    for edge in adj[cur]:
        next, cost = edge
        if costs[next] > prev_cost + cost:
            costs[next] = prev_cost + cost
            heapq.heappush(pq, [costs[next], next])
            #print("[] ", cur, next, cost, costs[next])

print(costs[end])
