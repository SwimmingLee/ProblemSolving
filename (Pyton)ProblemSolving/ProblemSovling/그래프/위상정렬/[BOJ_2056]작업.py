import collections
import sys

input = sys.stdin.readline
N = int(input())
adj = [[] for _ in range(N+1)]
inb = [0 for _ in range(N+1)]
costs = [0 for _ in range(N+1)]
pre_costs = [0 for _ in range(N+1)]

for i in range(1, N+1):
    line = list(map(int, input().split()))
    costs[i] = line[0]
    for j in range(line[1]):
        pre_task = line[j+2]
        adj[i].append(pre_task)
        inb[pre_task] += 1

q = collections.deque()
for i in range(1, N+1):
    if inb[i] == 0:
        pre_costs[i] = costs[i]
        q.append(i)

answer = 0
while q:
    cur = q.popleft()
    answer = max(answer, pre_costs[cur])
    for next in adj[cur]:
        inb[next] -= 1
        ##
        pre_costs[next] = max(
            pre_costs[next], pre_costs[cur] + costs[next])
        if inb[next] == 0:
            q.append(next)

print(answer)
