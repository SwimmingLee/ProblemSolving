import collections

N, K = map(int, input().split())
S = [0]*2
S[0] = input()
S[1] = input()


def bfs():
    dist = [[-1] * 2 for _ in range(N)]
    # print(dist)
    q = collections.deque()
    q.append([0, 0])
    dist[0][0] = 0

    while q:
        pos, line = q.popleft()
        for next_pos, next_line in [[pos+1, line], [pos-1, line], [pos+K, 1-line]]:
            # print(next_pos, next_line)
            if next_pos >= N:
                return 1
            if next_pos < 0 or dist[next_pos][next_line] != -1 or next_pos <= dist[pos][line] or S[next_line][next_pos] == '0':
                continue
            dist[next_pos][next_line] = dist[pos][line] + 1
            q.append([next_pos, next_line])
    return 0


answer = bfs()
print(answer)
