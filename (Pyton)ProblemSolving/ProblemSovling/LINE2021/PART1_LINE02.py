def solution(inp_str):
    answer = []

    # Test1
    length = len(inp_str)
    if 8 <= length <= 15:
        pass
    else:
        answer.append(1)

    # Test2
    # 여기서는 어떤 그룹의 숫자들로 이뤄져 있는지 파악해야함
    alpha = dict()
    is_test5 = False
    is_test4 = False

    chk = [0] * 4
    chk_cnt = 0

    pre_c = -1
    test4_cnt = 0

    for c in inp_str:

        # Test5 - 같은 문자가 몇 개 나오는지 확인
        if not c in alpha:
            alpha[c] = 1
        else:
            alpha[c] += 1
            if alpha[c] >= 5:
                is_test5 = True

        # Test4 - 연속해서 몇 개 의 문자가 나오는지 확인
        if pre_c == c:
            test4_cnt += 1
            if test4_cnt >= 4:
                is_test4 = True
        else:
            test4_cnt = 1
        pre_c = c

        # Test3 - 어떤 그룹의 문자인지 확인
        if 'A' <= c <= 'Z':
            if not chk[0]:
                chk[0] = True
                chk_cnt += 1

        elif 'a' <= c <= 'z':
            if not chk[1]:
                chk[1] = True
                chk_cnt += 1

        elif '0' <= c <= '9':
            if not chk[2]:
                chk[2] = True
                chk_cnt += 1

        elif c in "~!@#$%^&*":
            if not chk[3]:
                chk[3] = True
                chk_cnt += 1

        else:
            if not 2 in answer:
                answer.append(2)

    # Test3
    if chk_cnt >= 3:
        pass
    else:
        answer.append(3)

    # Test4
    if is_test4:
        answer.append(4)

    # Test5
    if is_test5:
        answer.append(5)

    if len(answer) == 0:
        answer.append(0)
    return answer


answer = solution("AaTa+!12-3")
print(answer)
answer = solution("aaaaZZZZ)")
print(answer)
answer = solution("CaCbCgCdC888834A")
print(answer)
answer = solution("UUUUU")
print(answer)
answer = solution("ZzZz9Z824")
print(answer)
