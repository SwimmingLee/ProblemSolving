import sys
import collections
input = sys.stdin.readline


def BFS(sy, sx, tvisitied):
    visited = [[False] * N for _ in range(N)]

    q = collections.deque()
    common_block_cnt = 0
    rainbow_block_cnt = 0

    visited[sy][sx] = True
    color = board[sy][sx]
    q.append([sy, sx])

    while q:
        y, x = q.popleft()
        if board[y][x] == color:
            common_block_cnt += 1
            tvisitied[y][x] = True
        elif board[y][x] == 0:
            rainbow_block_cnt += 1

        for dy, dx in [[-1, 0], [1, 0], [0, 1], [0, -1]]:
            ny = y + dy
            nx = x + dx
            if ny < 0 or nx < 0 or ny >= N or nx >= N or visited[ny][nx]:
                continue

            if board[ny][nx] == color or board[ny][nx] == 0:
                visited[ny][nx] = True
                q.append([ny, nx])

    return (common_block_cnt + rainbow_block_cnt, rainbow_block_cnt)


def removeBlock(sy, sx, board):
    visited = [[False] * N for _ in range(N)]

    q = collections.deque()
    block_cnt = 0

    color = board[sy][sx]
    q.append([sy, sx])
    visited[sy][sx] = True
    while q:
        y, x = q.popleft()
        board[y][x] = -2
        block_cnt += 1
        for dy, dx in [[-1, 0], [1, 0], [0, 1], [0, -1]]:
            ny = y + dy
            nx = x + dx
            if ny < 0 or nx < 0 or ny >= N or nx >= N or visited[ny][nx]:
                continue

            if board[ny][nx] == color or board[ny][nx] == 0:

                visited[ny][nx] = True
                q.append([ny, nx])

    return block_cnt ** 2


def gravity(board):
    for x in range(N):
        insert_yidx = N-1
        tmp_column = [-2] * N
        for search_yidx in range(N-1, -1, -1):
            if board[search_yidx][x] >= 0:
                tmp_column[insert_yidx] = board[search_yidx][x]
                insert_yidx -= 1
            elif board[search_yidx][x] == -1:
                tmp_column[search_yidx] = -1
                insert_yidx = search_yidx - 1

        for y in range(N):
            board[y][x] = tmp_column[y]


def rotateCCW_HalfPi(board):
    for y in range(N):
        board[y] = board[y][::-1]
    board = list(map(list, zip(*board)))


N, M = list(map(int, input().split()))
board = [0] * N
for bi in range(N):
    board[bi] = list(map(int, input().split()))

score = 0
while True:
    blocks = []
    tvisited = [[False] * N for _ in range(N)]
    for y in range(N):
        for x in range(N):
            if board[y][x] > 0 and not tvisited[y][x]:
                block_cnt, rainbow_block_cnt = BFS(y, x, tvisited)
                if block_cnt < 2:
                    continue
                blocks.append([block_cnt, rainbow_block_cnt, y, x])

    if len(blocks) == 0:
        break
    blocks.sort(key=lambda x: (-x[0], -x[1], -x[2], -x[3]))

    score += removeBlock(blocks[0][2], blocks[0][3], board)
    # print("haah")
    # print(*board, sep='\n')
    # print(score)
    gravity(board)
    for y in range(N):
        board[y] = board[y][::-1]

    board = list(map(list, zip(*board)))
    gravity(board)
    # print(*board, sep='\n')
print(score)

"""
1. 크기가 가장 큰 블럭 조각을 찾는다 - 무지개 많은거, 행, 열이 큰거
 - 블럭 돌아다니면서 BFS 고고! 블럭 수, 무지개 블럭 수, 반환

 - 다 돌고 나면 (-블럭 수, -무지개 블럭 수 , -행 , -열) 정렬  
2. 블럭 제거 후 점수 획득
 - 블럭 제거 할 때 BFS 한 번 더 ㄱㄱ 그리고 블럭 숫자의 제곱을 접수해 더해줌 ㅇㅇ
 
3. 중력
- 검은색 블럭은 중력 영향 ㄴㄴ
- 밑에서부터 하나씩 탐색 ㄱㄱ 
- 그런데 search_idx = -1로 검은 블럭을 만나면 insert_idx = search_idx+1로 변경해버림
- 이떄 search_idx에 블럭이 있으면 board[insert_idx] = board[search_idx] 해버림
- insert_idx=> 블럭을 넣어주면 올라감, search_idx=>얘는 그냥 증가

4. 90도 반시계 회전
  board[r] = board[r][::-1]

  board = zip(*board)

5. 중력 작용

"""
