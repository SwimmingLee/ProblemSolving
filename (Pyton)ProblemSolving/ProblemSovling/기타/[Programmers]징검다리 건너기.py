def solution(stones, k):

    # [2, 4, 5, 3, 2, 1, 4, 2, 5, 1]
    """
    자신보다 같거나 작은 경우가 연속으로 있으면 빈 공간이 생긴다.

    자신보다 작은 경우만 스택에 넣는다..?
    1 2 3
    자신보다 큰 숫자가 나오면 스택에 있는걸 뺀다. 


    자신보다 같은 경우도 스택에 넣는다. 
    자신보다 작은 경우만 스택에 넣는다
    3 2 1 
    그리고 꺼낼 때 위치에서 빼면 나보다 작은걸 확인할 수 있음
    3 2 1 2 3 

    이때 k보다 크면서 가장 작은 숫자를 고르면 그게 답!
    """
    MAX_ELEMENTS = 200_000_000
    answer = MAX_ELEMENTS + 1
    stones.insert(0, MAX_ELEMENTS+1)
    stones.append(MAX_ELEMENTS+1)

    st = []
    for i in range(len(stones)):
        while len(st) != 0 and stones[st[-1]] < stones[i]:
            right = i - 1
            stone = stones[st[-1]]
            st.pop()
            left = st[-1]
            step = right - left
            if step >= k and stone < answer:
                answer = stone
        st.append(i)

    return answer


print(solution([2, 4, 5, 3, 2, 1, 4, 2, 5, 1], 3))
