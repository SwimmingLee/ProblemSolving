# 배열 구하기

import sys

sys.setrecursionlimit(10001)


def solution(value, project):
    N = len(value)
    adj = [[] for _ in range(N)]
    for edge in project:
        u, v = edge
        adj[u-1].append(v-1)

    cache = [-1] * N

    def dfs(node):
        child_value = 0

        for next_node in adj[node]:
            child_value = max(child_value, dfs(next_node))

        return child_value + value[node]

    return dfs(0)


print(solution([10, 11, 8, 4, 9, 15, 17], [
      [1, 2], [1, 3], [1, 4], [3, 5], [3, 6], [4, 7]]))
