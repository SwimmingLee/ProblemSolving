import collections

TC = int(input())


def goosagua(N):
    q = collections.deque()
    chk = [-1 for _ in range(N)]
    come = [-1 for _ in range(N)]

    if N == 1:
        print(N)
        return

    x = 1 % N
    q.append(x)
    chk[x] = 1

    while q:
        x = q.popleft()
        for i in range(2):
            next = (x*10 + i) % N
            if chk[next] == -1:
                q.append(next)
                come[next] = x
                chk[next] = i
    x = 0
    if come[x] == -1:
        print("BRAK")
    else:
        res = ""
        while x != -1:
            res += str(chk[x])
            x = come[x]
        print(res[::-1])


for _ in range(TC):
    N = int(input())
    goosagua(N)
