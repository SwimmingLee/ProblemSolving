import collections

N, K = map(int, input().split())
q = collections.deque()
dist = [[-1]*2 for _ in range(500001)]

time = 0
q.append([N, 0])
dist[N][time % 2] = 0

while q:
    now, odd = q.popleft()
    if time != dist[now][odd]:
        time = dist[now][odd]

    for next in [now-1, now+1, now*2]:
        if next < 0 or next > 500000 or dist[next][1-odd] != -1:
            continue

        q.append([next, 1-odd])
        dist[next][1-odd] = dist[now][odd] + 1

ans = -1
time = 0
while K <= 500000:
    if dist[K][time % 2] != -1 and dist[K][time % 2] <= time:
        ans = time
        break
    time += 1
    K += time

print(ans)
