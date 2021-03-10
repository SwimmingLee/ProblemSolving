import sys
input = sys.stdin.readline

L, R, G, B = list(map(int, input().split()))
# print("[][]", L, R, G, B)
dp = [[[[-1 for _ in range(101)] for _ in range(101)]
       for _ in range(101)] for _ in range(11)]

# print(dp)

comb_cache = [[0] * 11 for _ in range(11)]


def comb(n, r):
    if comb_cache[n][r] != 0:
        return comb_cache[n][r]

    if n == r or r == 0:
        return 1

    res = comb(n-1, r) + comb(n-1, r-1)
    comb_cache[n][r] = res

    return res


def counting_set_bit(n):
    cnt = 0
    while n:
        # print("bit ", n)
        n = n & ~(-n)
        cnt += 1
    return cnt


def get_number_of_case(layer, n_use_diode):
    if n_use_diode == 2:
        return comb(layer, layer//2)
    elif n_use_diode == 3:
        return comb(layer, layer//3) * comb(2*layer//3, layer//3)
    return 1


def solution(layer, r, g, b):
    if r < 0 or g < 0 or b < 0:
        return 0
    if layer > L:
        return 1

    print("[]", layer, r, g, b)
    if dp[layer][r][g][b] != -1:
        return dp[layer][r][g][b]

    res = 0
    num = 1
    while num < (1 << 3):
        n_use_diode = counting_set_bit(num)
        if layer % n_use_diode != 0:
            num += 1
            continue

        n_consume = layer//n_use_diode
        use_r = 1 if num & (1 << 2) else 0
        use_g = 1 if num & (1 << 1) else 0
        use_b = 1 if num & (1 << 0) else 0

        res += solution(layer+1, r - n_consume*use_r, g -
                        n_consume*use_g, b - n_consume*use_b) * get_number_of_case(layer, n_use_diode)
        num += 1

    dp[layer][r][g][b] = res
    return res


answer = solution(1, R, G, B)
print(answer)
