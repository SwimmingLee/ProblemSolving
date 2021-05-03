import sys
input = sys.stdin.readline

N, M = map(int, input().split())
rows = [0] * M
columns = [0] * M
for _ in range(M):
    u, v = map(int, input().split())
    A.append([u, v])

answer = -1
# for i in range(1, N+1):
#     for j in range(1, N+1):
#         distance = 0
#         for k in A:
#             distance += abs(k[0] - i) + abs(k[1] - j)
#         if answer == -1 or answer > distance:
#             answer = distance

for i in range(M):
    distance = 0
    for j in range(M):
        if i == j:
            continue
        distance += abs(A[i][0] - A[j][0]) + abs(A[i][1] - A[j][1])
    if answer == -1 or answer > distance:
        answer = distance

print(answer)
