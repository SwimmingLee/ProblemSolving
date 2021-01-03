import sys
input = sys.stdin.readline
N, L = map(int, input().split())
parent = [-1 for _ in range(L+1)]
# -1이면 비워져 있는 서랍
# -2이면 채워져 있는 서랍(동시에 건드릴 수 없는 서랍)

sys.setrecursionlimit(100000)


def find(u):
    # print("find", u)
    if parent[u] <= -1:
        return u
    parent[u] = find(parent[u])
    return parent[u]


def merge(u, v):
    u = find(u)
    v = find(v)
    if u == v:
        parent[v] = -2
        return False

    parent[u] = v
    return True


for _ in range(N):
    a, b = map(int, input().split())
    u = find(a)
    v = find(b)

    negative = False
    if parent[a] == -1:
        merge(a, b)
    elif parent[b] == -1:
        merge(b, a)

    elif parent[u] == -1:
        merge(a, b)
    elif parent[v] == -1:
        merge(b, a)
    else:
        negative = True

    # print("{}", u, v, parent[u], parent[v])
    # for n in range(1, L+1):
        # print(find(n), end=' ')
    # print()
    if negative:
        print("SMECE")
    else:
        print("LADICA")
