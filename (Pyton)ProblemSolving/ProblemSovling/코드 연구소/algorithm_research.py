import sys


def checkContinousNum(N):
    str_num = str(N)
    str_len = len(str_num)

    is_ok = True
    prev = 0
    for idx, n in enumerate(str_num):
        if prev == n:
            under_score = 10 ** (str_len - idx - 1)
            N = (N // under_score) * under_score + under_score
            is_ok = False
            break
        prev = n

    if not is_ok:
        N = checkContinousNum(N)

    return N


def solution(N):
    nn = checkContinousNum(N+1)
    return nn


print(solution(56), 57)
print(solution(55), 56)
print(solution(1765), 1767)
print(solution(3298), 3401)
print(solution(44432), 45010)
print(solution(98), 101)
print(solution(100000), 101010)
print(solution(1), 2)
print(solution(9999999999), 10101010101)
print(solution(1221), 1230)
