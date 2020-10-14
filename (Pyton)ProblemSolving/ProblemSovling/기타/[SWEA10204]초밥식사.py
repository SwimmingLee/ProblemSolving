TC = int(input())

c = [0] * 100000
for test_case in range(1, TC+1):
    N = int(input())
    for i in range(N):
        c[i] = list(map(int, input().split()))

    c[:N].sort(key=lambda x: (x[0] + x[1]))
    answer = 0
    idx = 0
    for x in c:
        answer += x[0] if idx % 2 == 0 else -x[1]
        idx += 1
        if idx == N:
            break
    print("#{} {}".format(test_case, answer))
