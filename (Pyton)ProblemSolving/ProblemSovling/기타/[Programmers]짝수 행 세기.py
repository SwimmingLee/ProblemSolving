def solution(a):
    answer = 0

    # 행 (300,300)
    # [0,1,0]
    # [1,1,1]
    # [1,1,0]
    # [0,1,1]

    # 열에 있는 1의 갯수 a,b 동일
    # b는 각 행의 갯수가 짝수여야 함

    # a = (4, 3)
    # 각 열의 1의 갯수... 2, 4, 2
    # 그리고 행의 갯수는 짝수여야 함

    # 완탐?
    # 각 행에서 갯수가 짝수임을 만족하는 조합 찾기
    # 총 2^300 까지 로려해야 하니까 안됨
    # colC0, colC2, ---, colCcol
    # 각 열에 필요한 1의 갯수가 넘어서면 끝까지 안보고 넘어감
    # 만먁에 1의 갯수를 만족한 열이 있다면 조합을 다르게 표현할 수 있지만.. index 맞추기는 까다로움

    # 열부터 먼저 보면 어떄?
    # nC2, nCr, nCr.... 이렇게 말이지
    # 그러면서 행의 갯수가 짝수가 아니면 넘어가는거야... 이게 훨씬 더 남
    # 그런데 이건 시간복잡도가 어떻게 되지? - 이거 말고는 방법이 생각 ㄴㄴ
    # 백트리킹 조건?
    # 짝수라는 조건을 어떻게...? 백트래킹도 어려움.. ㅋ

    # DP?
    # D[2행부터 j행까지. 각 열별로 필요한 1의 갯수가 나와있음] = 이걸 만족하는 갯수

    # D[i열부터 j열까지, 각 행별로 필요한게 짝수인지 홀수 인지] = 갯수
    # 상태를 나타내는데 필요한 게 300 * 1<<300 이므로 그냥 메모리가 팡팡

    # DP[i][e] : 1행부터 주어진 조건대로 i열까지 0,1을 맞췄을 때, 짝수의 갯수가 e를 만족하는 행렬 b의 갯수
    # r 은 i열 필요한 1의 갯수
    # DP[i][rows-r] = DP[i-1][rows] * rowsCr

    # DP[i-1][0] * rowsCr => DP[i][r]
    # DP[i-1][1] * rowsCr => DP[i][r-1], DP[i][r], DP[i][r+1]
    # DP[i-1][2] * rowsCr => DP[i][r-2], DP[i][r-1], DP[i][r], DP[i][r+1], DP[i][r+2]
    # ...
    # DP[i-1][rows-1] * rowsCr => DP[i][rows-1-r], DP[i][rows-1-r+1],
    # DP[i-1][rows] * rowsCr => DP[i][rows-r]

    # DP[i][(rows-k) + (r-k)] = DP[i-1][n] * nCk * (rows-n)C(r-k)
    # DP[i][(rows-k) + (r-k)] = DP[i-1][n] * nCk * (rows-n)C(r-k)

    rows = len(a)
    columns = len(a[0])

    rotate_mat = list(map(list, zip(*a)))
    column_one = [0] * len(rotate_mat)
    for i in range(len(rotate_mat)):
        column_one[i] = rotate_mat[i].count(1)

    ele = []
    combis = [[] for _ in range(rows+1)]

    def combinatoin_(m):
        if combis[m]:
            return combis[m]
        combination(m, 0)
        return combis[m]

    def combination(m, start):
        if len(ele) == m:
            combi = [0] * rows
            for i in ele:
                combi[i] = 1
            combis[m].append(combi)
            return

        for i in range(start, rows):
            ele.append(i)
            combination(m, i+1)
            ele.pop()

    def solve(column):
        nonlocal answer
        if column == columns:
            # 각 행이 짝수이면 ok!
            for r in range(rows):
                cnt = 0
                for c in range(columns):
                    if rotate_mat[c][r] == 1:
                        cnt += 1
                if cnt % 2 != 0:
                    return

            answer += 1
            return

        combinatoin_(column_one[column])
        for combi in combis[column_one[column]]:
            rotate_mat[column] = combi
            solve(column+1)

    solve(0)
    return answer


print(solution([[0, 1, 0], [1, 1, 1], [1, 1, 0], [0, 1, 1]]))
print(solution([[1, 0, 0], [1, 0, 0]]))
print(solution([[1, 0, 0, 1, 1], [0, 0, 0, 0, 0],
                [1, 1, 0, 0, 0], [0, 0, 0, 0, 1]]))
