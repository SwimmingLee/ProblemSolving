N, K = map(int, input().split())
mod = 1000000007

# next A >= A
# dp(N, A) = dp(N-1, A) + dp(N-1, A+1) + ... dp(N-1, K)
# next A < A
# dp(N, A) = dp(N-1, A의 약수가 아닌 것)

# O(N*K*K) 로 시간 초과가 남

# dp(N, A) : 길이가 N인 좋아하는 배열인데, 처음이 A로 시작하는 경우의 수
# dp(N, A) = sigma(dp(N-1, i)) - dp(N-1, A의 약수)
divisor = [[] for _ in range(K+1)]
cache = [[0] * (K+1) for _ in range(N+1)]

for i in range(1, K+1):
    for j in range(i*2, K+1, i):
        divisor[j].append(i)

for i in range(1, K+1):
    cache[1][i] = 1

sum = K
next_sum = K
for i in range(2, N+1):
    sum = next_sum
    next_sum = 0
    for j in range(1, K+1):
        # print(" start", j)
        cache[i][j] = sum
        for k in divisor[j]:
            # print("divid", k)
            cache[i][j] -= cache[i-1][k]
            cache[i][j] %= mod
            cache[i][j] += mod
            cache[i][j] %= mod
        next_sum += cache[i][j]
        next_sum %= mod


print(next_sum)
