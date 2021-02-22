import heapq

N, M = map(int, input().split())
adj = [[] for _ in range(N+1)]
inb = [0 for _ in range(N+1)]

for _ in range(M):
    u, v = map(int, input().split())
    adj[u].append(v)
    inb[v] += 1

pq = []
for i in range(1, N+1):
    if inb[i] == 0:
        heapq.heappush(pq, i)

while pq:
    cur = heapq.heappop(pq)
    print(cur, end=' ')
    for next in adj[cur]:
        inb[next] -= 1
        if inb[next] == 0:
            heapq.heappush(pq, next)
