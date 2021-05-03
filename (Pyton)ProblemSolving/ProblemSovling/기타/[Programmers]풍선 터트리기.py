def solution(a):
    answer = 0
    # a의 길이는 백만
    # 그냥 풀면 !백만  절대 풀 수 없음
    # 그냥 봤을 때는 DP로 하는게 맞아보임
    # DP로 상태정의를 어떻게 할건데?
    # DP[현재 수열의 상태, 찬스여부] = 이렇게 하기엔 메모리가 터져버림

    # 아니면 분할정복...?
    # a[:mid] a[mid:] mid mid+1 아니 이건 분할정복으로 못품

    # D[i:, 찬스]
    # 결국은 최후의 숫자를 1로 만들어야 함

    # 풍선을 터트리는 순서가 중요한가?
    # 중요하지 않다면 앞에서부터 순서대로 훑어도 되지 않을까?
    # 풍선을 터트리는 숫자가 중요하긴 함..
    # 그래야 다으메 어느 풍선끼리 만나는지 알 수 있음
    # 따라서 순서대로 훑어도 보기는 어려워 보임

    # 또 어떤 그리디로 풀 수 있을까?
    # 그룹 구간에서 가장 작은게 자신이라면 살아남을 수 있음
    # ㅇㅇㅋ 맞음 그 구간에서 가장 작은 숫자는 DP로 구현 가능(쌉가능)
    # .... n .... 일 때 하나만 나보다 작으면 가능함..? ㅇㅇㅋ
    # 이렇게 구현하면 NlogN만에 구현 쌉가능!!!!!

    MAX_NUMBER = 1000000000
    MAX_LENGTH = len(a)
    MAX_EXPONENTIAL = 20

    D = [[0 for _ in range(MAX_EXPONENTIAL)] for _ in range(MAX_LENGTH)]

    def initRMQ():
        # D[i][j] : [i, i + 2^j) 구간에서 최솟값
        # D[i][j] = max(D[i][j-1], D[i + (1<<(j-1))][j-1])

        for j in range(MAX_EXPONENTIAL):
            for i in range(MAX_LENGTH):
                if j == 0:
                    D[i][j] = a[i]
                else:
                    if i + (1 << j) <= MAX_LENGTH:
                        D[i][j] = min(D[i][j-1], D[i + (1 << (j-1))][j-1])

    def queryRMQ(begin, end):
        min_res = (MAX_NUMBER+1)

        if begin == end:
            return min_res

        for exp in range(20, -1, -1):
            if begin + (1 << exp) <= end:
                min_res = min(min_res, D[begin][exp])
                begin += (1 << exp)

        return min_res

    initRMQ()
    for i in range(MAX_LENGTH):
        u = queryRMQ(0, i)
        v = queryRMQ(i+1, MAX_LENGTH)

        if u >= a[i] or v >= a[i]:
            answer += 1

    return answer


print(solution([9, -1, -5]))
print(solution([-16, 27, 65, -2, 58, -92, -71, -68, -61, -33]))
