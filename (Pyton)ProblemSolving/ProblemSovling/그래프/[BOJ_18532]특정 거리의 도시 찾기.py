import sys
import collections
input = sys.stdin.readline

n_city, n_road, k, start = list(map(int, input().split()))
adj = [[] for _ in range(n_city)]
for _ in range(n_road):
    u, v = list(map(int, input().split()))
    adj[u-1].append(v-1)


been = [-1 for _ in range(n_city)]
q = collections.deque()
q.append(start-1)
been[start-1] = 0

answer = []
while q:
    cur = q.popleft()
    if been[cur] == k:
        answer.append(cur)
    elif been[cur] > k:
        break

    for next in adj[cur]:
        if been[next] != -1:
            continue
        been[next] = been[cur] + 1
        q.append(next)

if answer:
    answer.sort()
    for element in answer:
        print(element+1)
else:
    print(-1)
