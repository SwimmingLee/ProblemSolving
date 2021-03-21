
def calc_one(cnt, n):
    if n < 10:
        return [cnt, n]

    used, res = 987987987, 0
    s = str(n)
    for i in range(0, len(s)-1):
        if s[i+1] == '0':
            continue
        print(s[:i+1], s[i+1:])

        n1 = int(s[:i+1])
        n2 = int(s[i+1:])

        tmp_used, tmp_res = calc_one(cnt+1, n1+n2)
        if tmp_used < used:
            used = tmp_used
            res = tmp_res
    return [used, res]


def solution(n):
    answer = []
    answer = calc_one(0, n)
    return answer


answer = solution(9)
print(answer)
