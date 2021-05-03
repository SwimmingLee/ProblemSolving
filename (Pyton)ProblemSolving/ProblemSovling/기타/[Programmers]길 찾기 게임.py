import sys

sys.setrecursionlimit(10000000)


def solution(nodeinfo):
    # answer = [[]]
    """
    일단 y노드가 높은 순으로 정렬
    그리고 x노드는 작은거에서 큰걸로 시작하는걸로 해보자

    일단 트리를 만들때도 재귀적으로 만드는게 편할듯???
    규칙 잘 맞추면 포문으로도 가능하긴 할듯

    floor+1 => []
    floor => []

    node[depth] = [2, 34, 5, 6,7 ,88 ,9, 0]이런식으로 나두면 가능하지 않을까?

    다음 층에서
    7번의 왼쪽 자식 노드를 찾음 [0, 8)
    7번의 오른쪽 자식 노드르 찾음 (8, 100_000]

    노드 정보를 어떻게 저장할 것인가?
    adj
    """

    extend_nodeinfo = [[nodeinfo[i], i] for i in range(len(nodeinfo))]
    extend_nodeinfo.sort(key=lambda x: -x[0][1])

    nodes = [[]]
    pre_y = extend_nodeinfo[0][0][1]
    depth = 0
    for node_pos, idx in extend_nodeinfo:
        x, y = node_pos
        if y != pre_y:
            depth += 1
            pre_y = y
            nodes.append([])
        nodes[depth].append([x, idx])

    tree = [[-1, -1] for _ in range(len(nodeinfo))]

    def addNode(ni, depth, first, last):
        nonlocal tree
        chk = 0
        if len(nodes) <= depth+1:
            return
        for x, idx in nodes[depth+1]:
            if first <= x < nodeinfo[ni][0]:
                tree[ni][0] = idx
                addNode(idx, depth+1, first, nodeinfo[ni][0]-1)
                chk += 1

            elif nodeinfo[ni][0] < x <= last:
                tree[ni][1] = idx
                addNode(idx, depth+1, nodeinfo[ni][0]+1, last)
                chk += 1

            if chk == 2:
                break

    def preorder(u, ele):
        ele.append(u+1)
        if tree[u][0] != -1:
            preorder(tree[u][0], ele)
        if tree[u][1] != -1:
            preorder(tree[u][1], ele)

    def postorder(u, ele):
        if tree[u][0] != -1:
            postorder(tree[u][0], ele)
        if tree[u][1] != -1:
            postorder(tree[u][1], ele)
        ele.append(u+1)

    answer = [[], []]
    addNode(extend_nodeinfo[0][1], 0, 0, 100_000)
    preorder(extend_nodeinfo[0][1], answer[0])
    postorder(extend_nodeinfo[0][1], answer[1])

    return answer


print(solution([[5, 3], [11, 5], [13, 3], [3, 5],
                [6, 1], [1, 3], [8, 6], [7, 2], [2, 2]]))
