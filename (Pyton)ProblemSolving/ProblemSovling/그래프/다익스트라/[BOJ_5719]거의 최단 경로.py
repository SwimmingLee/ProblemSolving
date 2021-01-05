import sys
import heapq
import collections
input = sys.stdin.readline

inf = 987987987

# step1 - 모든 다익스트라 경로를 구한다.
# step2 - 모든 다익스트라오 이동했던 경로를 삭제한다.
# step3 - 삭제한 엣지를 바탕을 다시 다익을 돌린다.


def forword_djk(adj, dist, s, N):
    pq = []
    dist[s] = 0
    visited = [False for _ in range(N)]
    heapq.heappush(pq, [0, s])

    while pq:
        _, cur = heapq.heappop(pq)
        if visited[cur]:
            continue
        visited[cur] = True

        for next in range(N):
            if adj[cur][next] == inf:
                continue

            if dist[next] > dist[cur] + adj[cur][next]:
                dist[next] = dist[cur] + adj[cur][next]
                heapq.heappush(pq, [dist[next], next])


def backword_djk(adj, dist, s, N):
    q = collections.deque()
    visited = [False for _ in range(N)]
    q.append(s)
    while q:
        cur = q.popleft()
        if visited[cur]:
            continue
        visited[cur] = True
        for next in range(N):
            if dist[next] == dist[cur] - adj[next][cur]:
                q.append(next)
                adj[next][cur] = inf


while True:
    N, M = map(int, input().split())
    if N == 0 and M == 0:
        break
    adj = [[inf for _ in range(N)] for _ in range(N)]
    dist = [inf for _ in range(N)]

    start, end = map(int, input().split())
    for _ in range(M):
        u, v, c = map(int, input().split())
        adj[u][v] = c

    forword_djk(adj, dist, start, N)
    backword_djk(adj, dist, end, N)

    dist = [inf for _ in range(N)]
    forword_djk(adj, dist, start, N)
    if dist[end] >= inf:
        print(-1)
    else:
        print(dist[end])
