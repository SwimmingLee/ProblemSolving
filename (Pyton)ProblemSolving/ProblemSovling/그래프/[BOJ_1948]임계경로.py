import sys
import heapq
input = sys.stdin.readline
sys.setrecursionlimit(987987987)

N = int(input())
M = int(input())
edges = [[] for _ in range(N+1)]
for _ in range(M):
    u, v, c = map(int, input().split())
    edges[u].append([v, c])
start, end = map(int, input().split())

dist = [-1 for _ in range(N+1)]
depth = [-1 for _ in range(N+1)]
child = [[] for _ in range(N+1)]


def dfs(city):
    global dist
    if dist[city] != -1:
        return dist[city]
    elif city == end:
        depth[city] = 0
        return 0

    res = 0
    for edge in edges[city]:
        next_city, cost = edge
        tmp = dfs(next_city)
        if res < tmp + cost:
            res = tmp + cost
            depth[city] = depth[next_city] + 1
            child[city] = [next_city]
        elif res == tmp + cost:
            child[city].append(next_city)
    dist[city] = res
    return dist[city]


visited = [False for _ in range(N+1)]
count = 0


def getCityCount(city):
    global visited, count
    if visited[city]:
        return
    visited[city] = True
    # print("[]", city)
    for next_city in child[city]:
        getCityCount(next_city)
        count += 1


answer = dfs(start)
getCityCount(start)
print(answer)
print(count)
