import sys
input = sys.stdin.readline

dy = [0, 1, 0, -1]
dx = [-1, 0, 1, 0]


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
        for ji in range(2):
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
    destroy_cnt = 1
    while destroy_cnt != 0 and len(shark_list) != 0:
        destroy_cnt = 0
        prev = shark_list[0]
        cnt = 1
        offset = 0
        shark_list_sz = len(shark_list)
        max_sz = shark_list_sz  # 중요!!
        for i in range(1, shark_list_sz):
            si = i - offset
            # if shark_list[si] == 0:
            #     max_sz = i
            #     break

            cur = shark_list[si]  # 중요!!
            if prev == shark_list[si]:
                cnt += 1
            else:
                if cnt >= 4:
                    shark_list = shark_list[:si-cnt] + shark_list[si:]
                    destroy_cnt += 1
                    offset += cnt
                    answer += prev * cnt
                cnt = 1
            prev = cur

        if cnt >= 4:
            si = shark_list_sz - offset
            shark_list = shark_list[:si-cnt]
            destroy_cnt += 1
            answer += prev * cnt

    if len(shark_list) == 0:
        break

    # 구슬 변화
    new_shark_list = [0] * (N*N - 1)
    prev = shark_list[0]
    cnt = 1
    nsi = 0
    is_full = False
    for i in range(1, len(shark_list)):
        # if shark_list[i] == 0:
        #     break

        if prev == shark_list[i]:
            cnt += 1
        else:
            new_shark_list[nsi] = cnt
            new_shark_list[nsi+1] = prev
            nsi += 2
            if nsi >= len(new_shark_list):
                is_full = True
                break
            cnt = 1
        prev = shark_list[i]
    if not is_full and prev != 0:
        new_shark_list[nsi] = cnt
        new_shark_list[nsi+1] = prev

    shark_list = new_shark_list

    # print(shark_list)

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
