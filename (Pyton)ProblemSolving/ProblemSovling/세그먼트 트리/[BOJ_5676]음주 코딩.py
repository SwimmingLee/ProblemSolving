import sys
import math
inputs = sys.stdin.readlines()

i = 0

NOTFOUND = 2
tree = []


def initSegTree(node, first, last):
    global tree
    if first == last:
        tree[node] = A[first]
        return
    mid = (first + last) // 2
    initSegTree(node*2, first, mid)
    initSegTree(node*2+1, mid+1, last)
    tree[node] = tree[node*2] * tree[node*2+1]


def querySegTree(node, first, last, left, right):
    if last < left or right < first:
        return NOTFOUND
    if left <= first and last <= right:
        return tree[node]
    mid = (first + last) // 2
    n = querySegTree(node*2, first, mid, left, right)
    m = querySegTree(node*2+1, mid+1, last, left, right)

    if n == NOTFOUND:
        return m
    elif m == NOTFOUND:
        return n
    else:
        return n*m


def updateSegTree(node, first, last, idx, value):
    global tree
    if last < idx or idx < first:
        return
    if first == last:
        tree[node] = value
        # print("뭐야 이게", node, value)
        return

    mid = (first + last) // 2
    updateSegTree(node*2, first, mid, idx, value)
    updateSegTree(node*2+1, mid+1, last, idx, value)
    tree[node] = tree[node*2] * tree[node*2+1]


def convertNumber(n):
    if n > 0:
        return 1
    elif n < 0:
        return -1
    else:
        return 0


def convertReq(n):
    if n > 0:
        return '+'
    elif n < 0:
        return '-'
    else:
        return 0


while i < len(inputs):
    N, K = list(map(int, inputs[i].split()))
    i += 1

    size = math.ceil(math.log(N)/math.log(2))
    tree = [0] * (2**(size+1))
    A = [convertNumber(n) for n in list(map(int, inputs[i].split()))]
    i += 1
    initSegTree(1, 0, N-1)
    for _ in range(K):
        command, u, v = inputs[i].split()
        i += 1

        u, v = int(u), int(v)
        if command == 'C':
            v = convertNumber(v)
            updateSegTree(1, 0, N-1, u-1, v)
        elif command == 'P':
            n = querySegTree(1, 0, N-1, u-1, v-1)
            n = convertReq(n)
            print(n, end='')
    print()
