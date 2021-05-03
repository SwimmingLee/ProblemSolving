def solution(n):
    answer = []
    # depth
    # 2차원 배열 만들어서 시도해도 될듯

    board = [[0 for _ in range(n)] for _ in range(n)]

    def solve(start, height, seq, num):
        print("start", start, "height", height, "seq", seq, "num", num)
        for i in range(height):
            board[start+i][seq] = num
            num += 1

        for i in range(1, height):
            board[start+height-1][seq+i] = num
            num += 1

        for i in range(1, height-1):
            board[start+height-1-i][seq+height-1-i] = num
            num += 1

        # if start+2 >= n:
            # return
        if start+2 < n and board[start+2][seq+1] == 0:
            solve(start+2, height - 3, seq+1, num)

    solve(0, n, 0, 1)
    print(*board, sep='\n')
    for i in range(n):
        for j in range(i+1):
            answer.append(board[i][j])

    return answer


solution(1)
solution(2)
solution(3)
solution(4)
solution(5)
solution(6)
solution(7)
solution(8)
