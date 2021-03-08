import sys

sys.setrecursionlimit(1000000)
N = int(input())
lock = input()
key = input()

dp = [[[[[-1] * 2 for _ in range(10)] for _ in range(10)]
       for _ in range(10)] for _ in range(N)]


def solve(pos, rot1, rot2, rot3, flag):
    if pos >= N:
        return 0
    if dp[pos][rot1][rot2][rot3][flag] != -1:
        return dp[pos][rot1][rot2][rot3][flag]

    x = int(key[pos]) - ((int(lock[pos]) + rot1) % 10)
    res = 987987987987
    dp[pos][rot1][rot2][rot3][flag] = res
    if x == 0:
        res = min(solve(pos+1, rot2, rot3, 0, 0),
                  solve(pos+1, rot2, rot3, 0, 1))
    else:
        for step in [1, 2, 3]:
            if flag == 0:
                scala = -1
            else:
                scala = 1
            offset = step*scala + 10
            t1 = solve(pos, (rot1+offset) % 10, rot2, rot3, flag)
            t2 = solve(pos, (rot1+offset) % 10, (rot2+offset) % 10, rot3, flag)
            t3 = solve(pos, (rot1+offset) % 10, (rot2+offset) %
                       10, (rot3+offset) % 10, flag)
            tmp = min(t1, t2, t3) + 1
            if res > tmp:
                res = tmp
    dp[pos][rot1][rot2][rot3][flag] = res
    return dp[pos][rot1][rot2][rot3][flag]


answer = min(solve(0, 0, 0, 0, 0), solve(0, 0, 0, 0, 1))
print(answer)
