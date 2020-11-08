import sys
import collections

N, K = list(map(int, input().split()))

q = collections.deque()
been = [-1 for _ in range(200001)]
parent = [-1 for _ in range(200001)]
q.append(N)
been[N] = 0


def validation(x): return all([
    x >= 0,
    x <= 200000
])


answer = -1
while q:
    x = q.popleft()
    if x == K:
        answer = been[x]
        break

    if validation(x-1) and been[x-1] == -1:
        q.append(x-1)
        been[x-1] = been[x] + 1
        parent[x-1] = x
    if validation(x+1) and been[x+1] == -1:
        q.append(x+1)
        been[x+1] = been[x] + 1
        parent[x+1] = x
    if validation(x*2) and been[x*2] == -1:
        q.append(x*2)
        been[x*2] = been[x] + 1
        parent[x*2] = x


print(answer)
st = [K]
while st:
    x = st.pop()
    if x != -1:
        st.append(x)
        st.append(parent[x])
    else:
        break

st = st[::-1]
for n in st:
    print(n, end=' ')
