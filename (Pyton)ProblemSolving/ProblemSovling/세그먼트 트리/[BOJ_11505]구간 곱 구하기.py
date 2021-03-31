import sys
import math
input = sys.stdin.readline

mod = 1000000007
N, M, K = map(int, input().split())
A = [0] * N
size = math.ceil(math.log(N)/math.log(2))
tree = [0] * (2**(size+1))


def initSegTree(node, first, last):
    if first == last:
        tree[node] = A[first]
        return
    mid = (first + last) // 2
    initSegTree(node*2, first, mid)
    initSegTree(node*2+1, mid+1, last)
    tree[node] = (tree[node*2] * tree[node*2+1]) % mod


def querySegTree(node, first, last, left, right):
    if right < first or last < left:
        return -1
    if left <= first and last <= right:
        return tree[node]

    mid = (first + last) // 2
    n = querySegTree(node*2, first, mid, left, right)
    m = querySegTree(node*2+1, mid+1, last, left, right)
    if n == -1:
        return m
    elif m == -1:
        return n
    else:
        return (n*m) % mod


def updateSegTree(node, first, last, idx, value):
    if idx < first or last < idx:
        return
    if first == last:
        tree[node] = value
        return

    mid = (first + last) // 2
    updateSegTree(node*2, first, mid, idx, value)
    updateSegTree(node*2+1, mid+1, last, idx, value)
    tree[node] = (tree[node*2] * tree[node*2+1]) % mod


for i in range(N):
    A[i] = int(input())
initSegTree(1, 0, N-1)
for _ in range(M+K):
    a, b, c = map(int, input().split())
    if a == 1:
        updateSegTree(1, 0, N-1, b-1, c)
    elif a == 2:
        print(querySegTree(1, 0, N-1, b-1, c-1))
