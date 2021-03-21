
chk = [False] * 1000001


def solution(ball, order):
    answer = []
    first, last = 0, len(ball)-1
    order_idx = 0

    for n in order:
        if n == ball[first]:
            answer.append(ball[first])
            first += 1
            while chk[ball[first]] and first <= last:
                answer.append(ball[first])
                first += 1
        elif n == ball[last]:
            answer.append(ball[last])
            last -= 1
            while chk[ball[last]] and first <= last:
                answer.append(ball[last])
                last -= 1
        else:
            chk[n] = True

        if first > last:
            break

    return answer


answer = solution([11, 2, 9, 13, 24], [9, 2, 13, 24, 11])
print(answer)
answer = solution([1, 2, 3, 4, 5, 6], [6, 2, 5, 1, 4, 3])
print(answer)
