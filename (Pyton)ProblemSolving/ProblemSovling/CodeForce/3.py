import sys
import collections

input = sys.stdin.readline
TC = int(input())
while TC:
    TC -= 1
    N = int(input())
    A = list(map(int, input().split()))
    q = collections.deque()

    for num in A:
        if not q:
            q.append(num)
        else:
            # top = q.popleft()
            # q.appendleft(top)

            if q[0] > num:
                q.appendleft(num)
            else:
                q.append(num)

    print(*q)
