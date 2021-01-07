import sys
input = sys.stdin.readline

inf = 987987987987

V, E = map(int, input().split())
dist = [[inf for _ in range(V+1)] for _ in range(V+1)]
adj = [[] for _ in range(V+1)]
for _ in range(E):
    u, v, c = map(int, input().split())
    dist[u][v] = c
    adj[u].append([v, c])


for i in range(1, V+1):
    dist[i][i] = 0


for k in range(1, V+1):
    for i in range(1, V+1):
        for j in range(1, V+1):
            if dist[i][j] > dist[i][k] + dist[k][j]:
                dist[i][j] = dist[i][k] + dist[k][j]
# print(*dist, sep='\n')


answer = inf
for k in range(1, V+1):
    for i in range(k+1, V+1):
        tmp = dist[k][i] + dist[i][k]
        if tmp < answer:
            # print({"aa"})
            answer = tmp
        for j in range(i+1, V+1):
            tmp = dist[k][i] + dist[i][j] + dist[j][k]
            if tmp < answer:
                # print({"aa"})
                answer = tmp

            tmp = dist[i][k] + dist[k][j] + dist[j][k]
            if tmp < answer:
                # print({"aa"})
                answer = tmp


# visited = [False for _ in range(V+1)]
# # been = [False for _ in range(V+1)]

# print(*dist, sep='\n')


# def dfs(start, city):
#     global visited, answer
#     visited[city] = True

#     for edge in adj[city]:
#         next_city, length = edge
#         if not visited[next_city]:
#             dfs(start, next_city)
#         else:
#             tmp = dist[start][city] + \
#                 dist[start][next_city] + dist[city][next_city]
#             answer = min(tmp, answer)


# # answer = 10000?0000
# for city in range(1, V+1):
#     if visited[city]:
#         continue
#     dfs(city, city)
if answer >= inf:
    answer = -1
print(answer)
