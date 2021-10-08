TC = int(input())

while TC:
    TC -= 1
    N = int(input())
    A = list(map(int, input().split()))

    # cnt = 0
    answer = []
    for left in range(N-1):
        min_idx = left
        for right in range(left+1, N):
            if (A[min_idx] > A[right]):
                min_idx = right

        if (min_idx != left):
            A = A[:left] + A[min_idx:right+1] + A[left:min_idx] + A[right+1:]
            # cnt += 1
            answer.append([left, right, min_idx - left])

    # print("answer: ", len(answer))
    print(len(answer))
    if (answer):
        for l, r, d in answer:
            print(l+1, r+1, d)
            # print("answer :", l+1, r+1, d)
