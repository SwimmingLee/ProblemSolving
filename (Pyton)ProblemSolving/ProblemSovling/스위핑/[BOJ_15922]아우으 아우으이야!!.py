"""
5
-5 -2
-3 0
2 5
6 10
8 12
"""

import sys
input = sys.stdin.readline

N = int(input())
answer = 0
pre_start, pre_end = map(int, input().split())
for _ in range(1, N):
    start, end = map(int, input().split())

    if end <= pre_end:
        pass
    elif start < pre_end:
        pre_end = end
    else:
        answer += (pre_end - pre_start)
        pre_start, pre_end = start, end
answer += (pre_end - pre_start)
print(answer)
