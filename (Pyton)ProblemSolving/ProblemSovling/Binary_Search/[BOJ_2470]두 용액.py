import sys
input = sys.stdin.readline

N = int(input())
liquid = list(map(int, input().split()))

liquid.sort()


def lower_bisearch(n):
    start, end = 0, N-1
    mid = 1

    res = 987987987987
    idx = 0
    while start <= end:
        mid = (start + end) // 2
        fusion = liquid[n] + liquid[mid]

        if fusion >= 0:
            end = mid - 1
            if fusion <= res:
                res = fusion
                idx = mid
        else:
            start = mid + 1

    return idx


def upper_bisearch(n):
    start, end = 0, N-1
    mid = 1

    res = -987987987987

    idx = N-1
    while start <= end:
        mid = (start + end) // 2
        fusion = liquid[n] + liquid[mid]

        if fusion > 0:
            end = mid - 1
        else:
            start = mid + 1
            if fusion >= res:
                res = fusion
                idx = mid

    return idx


res = 987987987987
answer1, answer2 = 0, 0
for i in range(len(liquid)):
    upper_idx = upper_bisearch(i)
    lower_idx = lower_bisearch(i)

    if lower_idx == i:
        pass
    if upper_idx != i and res > abs(liquid[i] + liquid[upper_idx]):
        res = abs(liquid[i] + liquid[upper_idx])
        answer1 = i
        answer2 = upper_idx
    if lower_idx != i and res > abs(liquid[i] + liquid[lower_idx]):
        res = abs(liquid[i] + liquid[lower_idx])
        answer1 = i
        answer2 = lower_idx

if answer1 < answer2:
    print(liquid[answer1], liquid[answer2])
else:
    print(liquid[answer2], liquid[answer1])
