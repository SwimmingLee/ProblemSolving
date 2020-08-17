import sys

K, N = map(int, sys.stdin.readline().split())
A = [int(sys.stdin.readline()) for _ in range(K)]

start = 0
end = 2 ** 31 -1
res = 0
while start <= end:
    mid = start + (end - start) // 2;

    n_line = 0
    for x in A:
        n_line += x // mid
    if n_line >= N:
        if (res < mid):
            res = mid
        start = mid + 1
    else:
        end = mid - 1

print(res)