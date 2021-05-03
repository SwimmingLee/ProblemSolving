def solution(s):
    answer = []

    remove_cnt = 0
    trans_cnt = 0
    while s != "1":
        cnt = 0
        for i in range(len(s)):
            if s[i] == '0':
                cnt += 1

        n = len(s) - cnt
        remove_cnt += cnt

        s = ""
        while n:
            s += str(n % 2)
            n //= 2

        s = s[::-1]
        trans_cnt += 1

    answer = [trans_cnt, remove_cnt]
    return answer


print(solution("110010101001"))
print(solution("01110"))
print(solution("1111111"))
