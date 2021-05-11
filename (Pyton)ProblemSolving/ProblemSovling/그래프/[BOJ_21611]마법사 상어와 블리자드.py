import sys
input = sys.stdin.readline

dy = [0, 1, 0, -1]
dx = [-1, 0, 1, 0]
answer = 0


def init(board, N):
    shark_list = [0] * (N*N - 1)
    sy = N//2
    sx = N//2

    left = []
    right = []
    up = []
    down = []

    cnt = 0
    dir = 0
    step = 1

    y = sy
    x = sx
    is_ok = True
    while is_ok:
        for i in range(2):
            for si in range(step):
                y = y + dy[dir]
                x = x + dx[dir]
                if y == sy:
                    if x < sx:
                        left.append(cnt)
                    else:
                        right.append(cnt)
                elif x == sx:
                    if y < sy:
                        up.append(cnt)
                    else:
                        down.append(cnt)
                shark_list[cnt] = board[y][x]
                if y == 0 and x == 0:
                    is_ok = False
                    break
                cnt += 1
            if not is_ok:
                break
            dir = (dir + 1) % 4
        step += 1

    return [up, down, left, right], shark_list


def explosion(shark_list):
    global answer
    can_explosion = True

    while can_explosion:
        if len(shark_list) == 0:
            break

        can_explosion = False
        continuous_cnt = 1
        offset = 0
        prev = shark_list[0]
        shark_list_sz = len(shark_list)
        for i in range(1, shark_list_sz):
            si = i - offset
            cur = shark_list[si]  # 중요!!
            if prev == shark_list[si]:
                continuous_cnt += 1
            else:
                if continuous_cnt >= 4:
                    shark_list = shark_list[:si -
                                            continuous_cnt] + shark_list[si:]
                    can_explosion = True
                    offset += continuous_cnt
                    answer += prev * continuous_cnt
                continuous_cnt = 1
            prev = cur

        if continuous_cnt >= 4:
            si = shark_list_sz - offset
            shark_list = shark_list[:si-continuous_cnt]
            can_explosion = True
            answer += prev * continuous_cnt

    return shark_list


def changeMarble(shark_list):
    changed_shark_list = [0] * (N*N - 1)

    prev = shark_list[0]
    continuous_cnt = 1
    csi = 0
    is_full = False
    for i in range(1, len(shark_list)):
        if prev == shark_list[i]:
            continuous_cnt += 1
        else:
            changed_shark_list[csi] = continuous_cnt
            changed_shark_list[csi+1] = prev
            csi += 2

            if csi >= len(changed_shark_list):
                is_full = True
                break

            continuous_cnt = 1

        prev = shark_list[i]

    if not is_full and prev != 0:
        changed_shark_list[csi] = continuous_cnt
        changed_shark_list[csi+1] = prev

    return changed_shark_list


N, M = list(map(int, input().split()))
board = [0] * N
for i in range(N):
    board[i] = list(map(int, input().split()))

blizard, shark_list = init(board, N)
answer = 0

for i in range(M):
    d, s = list(map(int, input().split()))

    # 블라자드 날리기!
    offset = 0
    for i in range(s):
        destroy_idx = blizard[d-1][i] - offset
        shark_list = shark_list[:destroy_idx] + shark_list[destroy_idx+1:]
        offset += 1

    # 연속 4칸 폭발!
    shark_list = explosion(shark_list)
    if len(shark_list) == 0:
        break
    # 구슬 변화
    shark_list = changeMarble(shark_list)
print(answer)


"""
1. 블리자드! 구술 파괴!
    땡기기
2. 연속4 없애기! 구술 폭파!
    땡기기
    - 링크드리스트로 구현하면 딱 좋음
3. 구술 변화! 
- 기존 구술을 나두고 복사해서 가져가는게 더 빠를 듯ㅇㅇ

"""
