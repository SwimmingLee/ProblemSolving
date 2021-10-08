import heapq
import sys

input = sys.stdin.readline
TC = int(input())
while TC:
    TC -= 1
    N = int(input())
    A = list(map(int, input().split()))
    answer = []

    pq = []
    for idx, sociability in enumerate(A):
        if sociability > 0:
            heapq.heappush(pq, [-sociability, idx+1])

    while len(pq) >= 2:
        u_social, u_idx = heapq.heappop(pq)
        v_social, v_idx = heapq.heappop(pq)

        answer.append([u_idx, v_idx])

        if u_social != -1:
            heapq.heappush(pq, [u_social+1, u_idx])
        if v_social != -1:
            heapq.heappush(pq, [v_social+1, v_idx])

    print(len(answer))
    for u, v in answer:
        print(u, v)
