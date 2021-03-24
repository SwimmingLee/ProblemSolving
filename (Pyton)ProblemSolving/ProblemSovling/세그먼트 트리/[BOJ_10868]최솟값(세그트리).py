import sys
import math
input = sys.stdin.readline
N, M = list(map(int, input().split()))
A = [0] * (N+1)
size = math.ceil(math.log(N)/math.log(2))
tree = [0] * (1 << (size+1))


def initSegTree(node_idx, range_first, range_last):
    if range_first == range_last:
        tree[node_idx] = A[range_last]
        return

    mid = range_first + (range_last - range_first) // 2
    initSegTree(node_idx*2, range_first, mid)
    initSegTree(node_idx*2+1, mid+1, range_last)
    tree[node_idx] = min(tree[node_idx*2], tree[node_idx*2+1])


def querySegTree(node_idx, range_first, range_last, query_first, query_last):

    if range_first > query_last or range_last < query_first:
        return -1
    if query_first <= range_first and range_last <= query_last:
        return tree[node_idx]

    mid = range_first + (range_last - range_first) // 2
    m = querySegTree(node_idx*2, range_first, mid, query_first, query_last)
    n = querySegTree(node_idx*2+1, mid+1, range_last, query_first, query_last)

    if m == -1:
        return n
    elif n == -1:
        return m
    else:
        return min(n, m)


for i in range(1, N+1):
    A[i] = int(input())

initSegTree(1, 1, N)
for _ in range(M):
    u, v = list(map(int, input().split()))
    answer = querySegTree(1, 1, N, u, v)
    print(answer)
