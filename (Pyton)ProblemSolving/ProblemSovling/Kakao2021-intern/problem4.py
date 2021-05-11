import collections
import heapq


def solution(n, start, end, roads, traps):
    answer = 0

    traps_sz = len(traps)
    adj = [[[0 for _ in range(n+1)] for _ in range(n+1)]
           for _ in range(2 ** traps_sz)]
    for road in roads:
        u, v, c = road
        for i in range(2 ** traps_sz):
            adj[i][u][v] = c

    def makeADJ(trap, prev_trap):
        nonlocal adj

        for i in range(1, n+1):
            for j in range(1, n+1):
                if i == j:
                    continue
                if adj[prev_trap][i][j] != 0:
                    cost = adj[prev_trap][i][j]
                    adj[trap][i][j] = 0
                    adj[trap][j][i] = cost

    def dfs(start, trap_num, prev_trap_num):
        if prev_trap_num != -1:
            # print("d", trap_num)
            makeADJ(trap_num, prev_trap_num)

        for idx in range(start, traps_sz):
            dfs(idx+1, trap_num | (1 << idx), trap_num)

    dfs(0, 0, -1)
    q = []
    heapq.heappush(q, [0, 0, start])

    while q:
        total_cost, trap_num, cur_room = heapq.heappop(q)
        print(cur_room)
        if cur_room == end:
            answer = total_cost
            break

        for next_room in range(1, n+1):
            cost = adj[cur_room][next_room][trap_num]
            if cost == 0:
                continue

            next_trap_num = trap_num
            for i in range(len(traps)):
                if traps[i] == next_room:
                    next_trap_num ^= (1 << i)
                    break

            heapq.heappush(q, [total_cost + cost, next_trap_num, next_room])

    return answer


print(solution(3, 1, 3, [[1, 2, 2], [3, 2, 3]], [2]))
print(solution(4, 1, 4, [[1, 2, 1], [3, 2, 1], [2, 4, 1]], [2, 3]))
