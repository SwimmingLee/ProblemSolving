
def solution(n, edges):
    answer = 0
    """
    각 노드당 하나로 잡고 하면 어떨까?
    부르트 포스로 풀면 시간초과가 날까?

    1. 루트노드에서 자식 노드를 보는데 그 중에 하나를 고르고, 나머지 노드로만 탐색한다. 
    2. 서로 다른 부모를 가지고 있지만 같은 뎁스인거를 어떻게 판단할까? 말그대로 

    1. 루트노드에서 갈 수 있는 자식노드를 모두 구한다. 
    2. 그 중 하나를 빼고 모두 자식노드를 선택한다.  
    3.  다시 1로 돌아가는데 하나뺴고 선택한 노드를 루트노드라고 생각한다. 
    """
    adj = [[] for _ in range(n)]
    # print(adj)
    for edge in edges:
        u, v = edge
        # print(u, v)
        adj[u].append(v)

    def solve(nodes):
        children = []
        for u in nodes:
            for v in adj[u]:
                children.append(v)

        res = 987987987
        for i in range(len(children)):
            res = min(res, solve(children[:i] + children[i+1:]))

        if res == 987987987:
            res = 0

        return len(nodes) + res

    answer = solve([0])
    return answer


print(solution(19, [[0, 1], [0, 2], [0, 3], [1, 4], [1, 5], [2, 6], [3, 7], [3, 8], [
      3, 9], [4, 10], [4, 11], [5, 12], [5, 13], [6, 14], [6, 15], [6, 16], [8, 17], [8, 18]]))
print(solution(14, [[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [2, 6], [
      2, 7], [3, 8], [3, 9], [3, 10], [4, 11], [4, 12], [4, 13]]))
print(solution(10, [[0, 1], [0, 2], [1, 3], [2, 4],
                    [2, 5], [2, 6], [3, 7], [3, 8], [3, 9]]))
