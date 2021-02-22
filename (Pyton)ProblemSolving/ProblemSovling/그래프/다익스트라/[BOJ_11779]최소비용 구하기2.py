import heapq
import sys

input = sys.stdin.readline
n_city = int(input())
n_bus = int(input())
adj = [[] for _ in range(n_city + 1)]
for _ in range(n_bus):
    u, v, c = map(int, input().split())
    adj[u].append([v, c])
start_city, end_city = map(int, input().split())


def printPath(parent, u, path):
    if u == 0:
        return 0
    depth = printPath(parent, parent[u], path)
    path.append(u)

    return depth + 1


def djk():
    inf = 987987987
    pq = []
    chk = [False for _ in range(n_city + 1)]
    dist = [inf for _ in range(n_city + 1)]
    parent = [0 for _ in range(n_city + 1)]

    dist[start_city] = 0
    heapq.heappush(pq, [dist[start_city], start_city])

    while pq:
        cost, cur_city = heapq.heappop(pq)
        if chk[cur_city]:
            continue
        chk[cur_city] = True
        for edge in adj[cur_city]:
            next_city, cost = edge
            if dist[next_city] > dist[cur_city] + cost:
                dist[next_city] = dist[cur_city] + cost
                heapq.heappush(pq, [dist[next_city], next_city])
                parent[next_city] = cur_city
    print(dist[end_city])
    path = []
    depth = printPath(parent, end_city, path)
    print(depth)
    for city in path:
        print(city, end=' ')


djk()
