import collections


def solution(board, r, c):
    answer = 0

    # 어디로 어떻게 갈지는 완탐으로 해야할듯
    # DP 사용 가능? 보드 상황을 상태로 가지기는 쫌 그럼

    # 완탐 아이디어
    # 현재 위치에서 상하좌우 쭉쭉감
    # Ctrl + 방향키만 사용하는게 좋을듯? ㄴㄴ
    # 어떤 카드 상황이 있을지 모르니까 그냥 방향키까지 고려해야함
    # 적어도 백트래킹이 아니면 터질듯함

    # BFS로 돌려돌려? 마찬가지고 인형의 상태를 가지고 가기 어려움
    # DFS로 돌려돌려? 백트래킹으로 하면 가능하지 않을까? 근데 중복되는 것도 분명히 있음...
    # 일단 이전 위치로 되돌아가는 것을 막아야 함? 어떻게? visited? 이것도 현재 상태를....
    # 일단 커서위치, 몇번 인형이 선택되었는지(또는 선택안됐는지), 어떤 인형들을 처리했는지?(넘버링)
    # [4][4][7][2][1 << 6]

    # 인형의 좌표를 보고 이게 0인지 1인지는 어떻게 알까?
    # doll[4][4] 를 하나 더 만들면 가능함 그러면 0인지 1인지 알 수 있음 ㅇㅋ?
    visited = [False] * 7
    doll = [[0 for _ in range(4)] for _ in range(4)]
    ndoll = 0
    for i in range(4):
        for j in range(4):
            if board[i][j] == 0:
                continue
            if not visited[board[i][j]]:
                visited[board[i][j]] = True
                ndoll += 1
            else:
                doll[i][j] = 1

    queue = collections.deque()
    been = [[[[[-1 for _ in range(1 << 6)] for _ in range(2)]
              for _ in range(7)] for _ in range(4)] for _ in range(4)]
    queue.append([r, c, 0, 0, 0])
    been[r][c][0][0][0] = 0
    while queue:
        y, x, choice, di, state = queue.popleft()
        # print(y, x, "선택", choice, di, "state", state,
        #   been[y][x][choice][di][state])

        if state == (1 << ndoll)-1:
            answer = been[y][x][choice][di][state]
            break

        doll_idx = board[y][x]
        if doll_idx != 0:
            # Enter - 인형 뒤집기
            if choice == 0:
                if (state & (1 << (doll_idx-1))) == 0 and been[y][x][doll_idx][doll[y][x]][state] == -1:
                    been[y][x][doll_idx][doll[y][x]
                                         ][state] = been[y][x][choice][di][state] + 1

                    queue.append([y, x, doll_idx, doll[y][x], state])

            # Enter - 인형 세트 맞추기
            if choice == doll_idx and doll[y][x] != di:
                if been[y][x][0][0][state | (1 << (choice-1))] == -1:
                    been[y][x][0][0][state | (
                        1 << (choice-1))] = been[y][x][choice][di][state] + 1
                    queue.append([y, x, 0, 0, state | (1 << (choice-1))])

        for dy, dx in [[-1, 0], [1, 0], [0, 1], [0, -1]]:
            ny = y + dy
            nx = x + dx
            if ny < 0 or nx < 0 or ny >= 4 or nx >= 4:
                continue

            # 일단 이동
            if been[ny][nx][choice][di][state] == -1:
                been[ny][nx][choice][di][state] = been[y][x][choice][di][state] + 1
                queue.append([ny, nx, choice, di, state])

            cy = y
            cx = x
            while ny >= 0 and nx >= 0 and ny < 4 and nx < 4:
                cy = ny
                cx = nx
                if board[cy][cx] != 0 and (state & (1 << (board[cy][cx] - 1))) == 0:
                    break
                ny = cy + dy
                nx = cx + dx

            ny = cy
            nx = cx

            # if y == 0 and x == 0:
            # print("간다", ny, nx, choice, di, state,
            #   been[ny][nx][choice][di][state])
            # 일단 이동
            if been[ny][nx][choice][di][state] == -1:
                been[ny][nx][choice][di][state] = been[y][x][choice][di][state] + 1
                # print("간다", ny, nx, choice, di, state)
                queue.append([ny, nx, choice, di, state])

    return answer


print(solution([[1, 0, 0, 3], [2, 0, 0, 0], [0, 0, 0, 2], [3, 0, 1, 0]], 1, 0))
print(solution([[3, 0, 0, 2], [0, 0, 1, 0], [0, 1, 0, 0], [2, 0, 0, 3]], 0, 1))
