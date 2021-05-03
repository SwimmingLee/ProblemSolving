
def solution(blocks):
    answer = []
    """
    피라미드 꼭대기서부터 내려오면서 순회하기
    
    해당 층을 검사할 때, 
     1) 알아볼 수 있는 블록에서 왼쪽으로 가기 
     2) 알아볼 수 있는 블록에서 오른쪽으로 가기 

    자신 인덱스에서 부모 인덱스를 어떻게 접근? 
    자기 층: floor 
    (0,1)-> 0 (1,2)->1 (2,3)->2
     - 자기 자신의 인덱스를 올려주면 됨
    """
    N = len(blocks)
    board = [[0] * N for _ in range(N)]
    board[0][0] = blocks[0][1]
    for floor in range(1, N):
        bi, value = blocks[floor]
        board[floor][bi] = value

        for i in range(bi, floor):
            board[floor][i+1] = board[floor-1][i] - board[floor][i]
        for i in range(bi-1, -1, -1):
            board[floor][i] = board[floor-1][i] - board[floor][i+1]

    for floor in range(N):
        for bi in range(floor+1):
            answer.append(board[floor][bi])
    return answer


print(solution([[0, 50], [0, 22], [2, 10], [1, 4], [4, -13]]))
print(solution([[0, 92], [1, 20], [2, 11], [1, -81], [3, 98]]))
