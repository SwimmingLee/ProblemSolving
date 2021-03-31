import sys
import math
input = sys.stdin.readline

N, M, K = list(map(int, input().split()))
A = [0] * N

# 배열 입력받기
for i in range(N):
    A[i] = int(input())

# 세그먼트 트리 초기화
size = math.ceil(math.log(N)/math.log(2))
tree = [0] * (1 << (size+1))


def initSegTree(node_idx, first, last):
    if first == last:
        tree[node_idx] = A[first]
        return

    mid = first + (last - first) // 2
    initSegTree(node_idx*2+1, first, mid)
    initSegTree(node_idx*2+2, mid+1, last)
    tree[node_idx] = tree[node_idx*2 + 1] + tree[node_idx*2 + 2]


def querySegTree(node_idx, first, last, query_start, query_end):
    if last < query_start or query_end < first:
        return 0
    if query_start <= first and last <= query_end:
        return tree[node_idx]
    mid = first + (last - first) // 2
    return querySegTree(node_idx*2 + 1, first, mid, query_start, query_end) + querySegTree(node_idx*2 + 2, mid+1, last, query_start, query_end)


def updateSegTree(node_idx, first, last, left, right, value):
    if right < first or last < left:
        return
    if first == last:
        tree[node_idx] += value
        return

    mid = first + (last - first) // 2
    updateSegTree(node_idx*2+1, first, mid, left, right, value)
    updateSegTree(node_idx*2+2, mid+1, last, left, right, value)
    tree[node_idx] = tree[node_idx*2+1] + tree[node_idx*2+2]


initSegTree(0, 0, N-1)

# 세그먼트 조회 및 수정
for _ in range(M+K):
    inputs = list(map(int, input().split()))
    if inputs[0] == 1:
        b, c, d = inputs[1:]
        updateSegTree(0, 0, N-1, b-1, c-1, d)
    else:
        b, c = inputs[1:]
        res = querySegTree(0, 0, N-1, b-1, c-1)
        print(res)
