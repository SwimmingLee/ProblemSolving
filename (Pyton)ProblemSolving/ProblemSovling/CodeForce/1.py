
TC = int(input())
while TC:
    TC -= 1
    s = input()

    a_cnt = 0
    b_cnt = 0
    c_cnt = 0

    for c in s:
        if c == 'A':
            a_cnt += 1
        elif c == 'B':
            b_cnt += 1
        else:
            c_cnt += 1

    if a_cnt + c_cnt == b_cnt:
        print("yes")
    else:
        print("no")
