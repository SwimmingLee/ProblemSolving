
paper = input()
bridge = [0] * 2
bridge[0] = input()
bridge[1] = input()

dp = [[[-1 for _ in range(2)] for _ in range(20)] for _ in range(100)]


def solution(n, paper_idx, bridge_idx):
    if paper_idx == len(paper):
        return 1

    if dp[n][paper_idx][bridge_idx] != -1:
        return dp[n][paper_idx][bridge_idx]

    res = 0
    for pos in range(n, len(bridge[bridge_idx])):
        if bridge[bridge_idx][pos] == paper[paper_idx]:
            res += solution(pos + 1, paper_idx + 1, 1 - bridge_idx)
    dp[n][paper_idx][bridge_idx] = res
    return res


answer = solution(0, 0, 0) + solution(0, 0, 1)
print(answer)
