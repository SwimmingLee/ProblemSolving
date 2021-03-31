import sys
import math
input = sys.stdin.readline

N, M = map(int, input().split())
A = [0] * N
size = math.ceil(math.log(N)/math.log(2))
max_tree = [0] * (2**(size+1))
min_tree = [0] * (2**(size+1))


def initSegTree(node, first, last):
    if first == last:
        max_tree[node] = A[first]
        min_tree[node] = A[first]
        return
    mid = (first + last) // 2
    initSegTree(node*2, first, mid)
    initSegTree(node*2+1, mid+1, last)
    max_tree[node] = max(max_tree[node*2], max_tree[node*2+1])
    min_tree[node] = min(min_tree[node*2], min_tree[node*2+1])


def querySegTree(node, first, last, left, right):
    if right < first or last < left:
        return (-1, -1)

    if left <= first and last <= right:
        return (min_tree[node], max_tree[node])

    mid = (first + last) // 2
    n1, m1 = querySegTree(node*2, first, mid, left, right)
    n2, m2 = querySegTree(node*2+1, mid+1, last, left, right)

    if n1 == -1:
        return (n2, m2)
    elif n2 == -1:
        return (n1, m1)
    else:
        return (min(n1, n2), max(m1, m2))


for i in range(N):
    A[i] = int(input())

initSegTree(1, 0, N-1)

for _ in range(M):
    u, v = map(int, input().split())
    print(*querySegTree(1, 0, N-1, u-1, v-1))
