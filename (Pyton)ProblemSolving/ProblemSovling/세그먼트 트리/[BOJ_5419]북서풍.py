import sys


def solution(island):
    cnt = 0
    for i in range(len(island)):
        for j in range(len(island)):
            if i == j:
                continue
            if island[i][0] <= island[j][0] and island[i][1] >= island[j][1]:
                cnt += 1
    return cnt


input = sys.stdin.readline
# TC = int(input())
# for _ in range(TC):
#     N = int(input())
#     island = []
#     for _ in range(N):
#         x, y = list(input().split())
#         island.append([x, y])

#     answer = solution(island)
#     print(answer)
