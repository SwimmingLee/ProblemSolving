import sys

adj = []
visited = []
answer = 0

sys.setrecursionlimit(10000000)


def solve(u, a):
    global answer, visited, adj
    visited[u] = True
    for next in adj[u]:
        if not visited[next]:
            tmp = solve(next, a)
            answer += abs(tmp)
            a[u] += tmp
    return a[u]


def solution(a, edges):
    global adj, visited, answer
    """
    모든 가중치를 더해서 0이 되면 ok, 아니면 다 모든 노드를 0으로 만들 수 없음
    """

    node_sz = len(a)
    adj = [[] for _ in range(node_sz)]
    for edge in edges:
        u, v = edge
        adj[u].append(v)
        adj[v].append(u)

    sum_a = 0
    for n in a:
        sum_a += n

    if sum_a != 0:
        return -1

    visited = [False for _ in range(node_sz)]

    solve(0, a)
    if a[0] != 0:
        return -1
    return answer


print(solution([-5, 0, 2, 1, 2], [[0, 1], [3, 4], [2, 3], [0, 3]]))
print(solution([0, 0, 0, 0, 0], [[0, 1], [3, 4], [2, 3], [0, 3]]))
