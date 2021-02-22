import sys
import heapq
input = sys.stdin.readline

inf = 9879879879

N, S, E, T = map(int, input().split())
adj = [[] for _ in range(N)]
for i in range(N):
    adj[i] = list(input())

answer = 0
pq = []
visited = [False for _ in range(N)]
dist = [inf for _ in range(N)]
heapq.heappush(pq, [0, S-1])
dist[S-1] = 0
while pq:
    _, cur = heapq.heappop(pq)
    # if visited[cur]:
    #     continue
    # visited[cur] = True
    if cur == E-1:
        print("[] ", cur)
    if cur == E-1 and dist[cur] == T:
        answer += 1
        continue

    for next in range(N):
        if int(adj[cur][next]) == 0:
            continue
        if dist[next] > dist[cur] + int(adj[cur][next]):
            dist[next] = dist[cur] + int(adj[cur][next])
            heapq.heappush(pq, [dist[next], next])

print(answer)
