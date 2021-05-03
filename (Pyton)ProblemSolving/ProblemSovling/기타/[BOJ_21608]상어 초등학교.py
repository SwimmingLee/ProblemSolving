import sys
input = sys.stdin.readline


def SearchFrinedSeat(friends_list):
    seats = []
    for y in range(N):
        for x in range(N):
            if board[y][x] != 0:
                continue
            near_friend_cnt = 0
            near_blank_cnt = 0
            for dy, dx in [[-1, 0], [1, 0], [0, -1], [0, 1]]:
                ny = y + dy
                nx = x + dx
                if ny < 0 or nx < 0 or ny >= N or nx >= N:
                    continue

                if board[ny][nx] in friends_list:
                    near_friend_cnt += 1
                elif board[ny][nx] == 0:
                    near_blank_cnt += 1

            seats.append([near_friend_cnt, near_blank_cnt, y, x])
    seats.sort(key=lambda x: (-x[0], -x[1], x[2], x[3]))
    return (seats[0][2], seats[0][3])


N = int(input())
board = [[0 for _ in range(N)] for _ in range(N)]
friends = [0 for _ in range(N*N+1)]
for fi in range(N*N):
    tmp = list(map(int, input().split()))
    student_idx, friends_list = tmp[0], tmp[1:]
    friends[student_idx] = friends_list
    y, x = SearchFrinedSeat(friends_list)
    board[y][x] = student_idx

# print(*board, sep='\n')

answer = 0
for y in range(N):
    for x in range(N):
        near_friend_cnt = 0
        student_idx = board[y][x]
        for dy, dx in [[-1, 0], [1, 0], [0, -1], [0, 1]]:
            ny = y + dy
            nx = x + dx
            if ny < 0 or nx < 0 or ny >= N or nx >= N:
                continue
            if board[ny][nx] in friends[student_idx]:
                near_friend_cnt += 1

        score_table = [0, 1, 10, 100, 1000]
        answer += score_table[near_friend_cnt]
print(answer)


"""
1. 비어있는 칸 중에 좋아하는 학생이 인접한 곳이 많은 곳
 - board 순회하면서 인접한 배열 확인하여 좋아하는 학생이 많은지 확인 ㅇㅇ 

2. 인접한 칸 중에 빈 칸이 많은 곳
 - 보드 순회하면서 동시에 인접한 빈칸도 같이 셈

3. 행이 제일 작은 곳, 열이 제일 작은 곳
 - 그리고 정렬 ㄱㄱ (-친한 인접 학생 수, -빈칸 수, 행, 열)
"""
