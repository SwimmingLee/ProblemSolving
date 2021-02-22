import sys
import heapq

input = sys.stdin.readline
V, E, K = list(map(int, input().split()))
adj = [[] for _ in range(V+1)]
for _ in range(E):
    u, v, w = list(map(int, input().split()))
    adj[u].append([w, v])

# 다익스트라처럼 돌리기
pq = []
dist = [[] for _ in range(V+1)]
heapq.heappush(pq, [0, 1])

dist[1].append(0)
while pq:
    acc_dist, cur = heapq.heappop(pq)

    for edge in adj[cur]:
        cost, next = edge
        top = dist[next][-1] if dist[next] else 987987987

        if len(dist[next]) < K:
            dist[next].append(acc_dist + cost)
            dist[next].sort()
            # dist[next] = acc_dist + cost
            heapq.heappush(pq, [acc_dist + cost, next])
        # print(dist[next], K)
        # print(dist[next])
        elif top > acc_dist + cost:
            dist[next].pop()
            dist[next].append(acc_dist + cost)
            dist[next].sort()
            # dist[next] = acc_dist + cost
            heapq.heappush(pq, [acc_dist + cost, next])


for idx in range(1, len(dist)):
    # print("[] ", dist[idx])
    if len(dist[idx]) == K:

        print(dist[idx][-1])
    else:
        print(-1)

# queue에 모두 넣어야 한다? 살짝쿵 완탐처럼 해야 한다. 꼭 필요한 것들만 넣는 것이 아니라
# 해당 큐에 모두 넣고 최솟값을 꺼내면 된다.
# 그리고 해당 노드에 K번 초과 입력데이터가 들어오면 그만 멈춰도 된다!?
