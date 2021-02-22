import sys

input = sys.stdin.readline

TC = int(input())
parent = []
name_dict = {}
count = 0


def find(u):
    if parent[u] <= -1:
        return u
    parent[u] = find(parent[u])
    return parent[u]


def merge(u, v):
    u = find(u)
    v = find(v)

    if u == v:
        return False

    parent[v] += parent[u]
    parent[u] = v
    return True


def name2num(name):
    global count
    if not name in name_dict:
        name_dict[name] = count
        count += 1
    return name_dict[name]


for _ in range(TC):
    F = int(input())
    parent = [-1 for _ in range(200000)]
    name_dict = dict()
    count = 0

    for _ in range(F):
        name1, name2 = input().split()
        u = name2num(name1)
        v = name2num(name2)
        merge(u, v)
        root = find(u)
        print(-parent[root])
