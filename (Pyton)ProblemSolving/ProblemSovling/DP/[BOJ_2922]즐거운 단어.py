import sys
input = sys.stdin.readline

word = input()
contain_L = False
for i in range(len(word)):
    if word[i] == 'L':
        contain_L = True

# N 3 3
# N 3 3
dp = [[[-1 for _ in range(3)] for _ in range(3)] for _ in range(100)]
dp1 = [[[-1 for _ in range(3)] for _ in range(3)] for _ in range(100)]


def solution(n, ja, mo):
    if ja >= 3 or mo >= 3:
        return 0
    if n == len(word)-1:
        return 1

    if dp[n][ja][mo] != -1:
        return dp[n][ja][mo]

    res = 0
    if word[n] == '_':
        res += solution(n+1, ja+1, 0) * 21
        res += solution(n+1, 0, mo+1) * 5
    else:
        if word[n] in "AEIOU":
            res += solution(n+1, 0, mo+1)
        else:
            res += solution(n+1, ja+1, 0)
    dp[n][ja][mo] = res
    return res


def solution1(n, ja, mo):
    if ja >= 3 or mo >= 3:
        return 0
    if n == len(word)-1:
        return 1

    if dp1[n][ja][mo] != -1:
        return dp1[n][ja][mo]
    res = 0
    if word[n] == '_':
        res += solution1(n+1, ja+1, 0) * 20
        res += solution1(n+1, 0, mo+1) * 5
    else:
        if word[n] in "AEIOU":
            res += solution1(n+1, 0, mo+1)
        else:
            res += solution1(n+1, ja+1, 0)
    dp1[n][ja][mo] = res
    return res


answer = solution(0, 0, 0)
tmp = 0
if not contain_L:
    tmp = solution1(0, 0, 0)
print(answer-tmp)
