import sys
import heapq

r = open("/mnt/c/Users/swimm/Desktop/test/large_16.in", mode='rt')
input = r.readline

N, M, start_city, end_city, wallet = list(map(int, input().split()))

edges = [[] for _ in range(N+1)]
for _ in range(M):
    u, v, c = list(map(int, input().split()))
    edges[u].append([v, c])
    edges[v].append([u, c])

vistied = [False] * (N+1)

inf = 987987987
answer = inf
visited = [False] * (N+1)
dist = [inf] * (N+1)

pq = []
heapq.heappush(pq, [0, 0, start_city])
dist[start_city] = 0

while pq:
    total_cost, max_collection, city = heapq.heappop(pq)
    if total_cost > wallet:
        break

    if city == end_city and answer > max_collection:
        answer = max_collection

    for edge in edges[city]:
        next_city, cost = edge
        if total_cost + cost > wallet:
            continue
        if cost > max_collection:
            heapq.heappush(pq, [total_cost + cost, cost, next_city])
        else:
            heapq.heappush(pq, [total_cost + cost, max_collection, next_city])
if answer == inf:
    answer = -1
print(answer)
