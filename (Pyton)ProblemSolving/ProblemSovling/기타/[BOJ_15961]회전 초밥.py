import sys
input = sys.stdin.readline
N, d, k, c = list(map(int, input().split()))
susi_dish = [0] * N
susi = [0] * (d+1)
for i in range(N):
    susi_dish[i] = int(input())

answer = 0
cnt = 0
for i in range(k):
    if susi[susi_dish[i]] == 0:
        cnt += 1
    susi[susi_dish[i]] += 1

coupon = 1 if susi[c] == 0 else 0

if answer < cnt + coupon:
    answer = cnt + coupon

for i in range(0, N):
    if susi[susi_dish[i]] == 1:
        cnt -= 1
    susi[susi_dish[i]] -= 1

    if susi[susi_dish[(i+k) % N]] == 0:
        cnt += 1
    susi[susi_dish[(i+k) % N]] += 1

    coupon = 1 if susi[c] == 0 else 0

    if answer < cnt + coupon:
        answer = cnt + coupon

print(answer)
