
dy = [1, 0, -1, 0]
dx = [0, -1, 0, 1]
# dir 0 : 아래
# dir 1 : 왼쪽
# dir 2 : 위
# dir 3 : 오른쪽


def solution(maze):
    answer = 0
    y, x, dir = 0, 0, 3

    N = len(maze)

    def outbound(yy, xx):
        if 0 <= yy < N and 0 <= xx < N:
            return False
        else:
            return True

    def rotate_left(d):
        return (d+3) % 4

    def rotate_right(d):
        return (d+1) % 4

    while y != N-1 or x != N-1:
        chk_y = y + dy[rotate_left(dir)]
        chk_x = x + dx[rotate_left(dir)]

        leftwall = False
        # 왼쪽 벽이 막혀있는데 앞으로 갈 수 없다면 회전한다.
        while outbound(chk_y, chk_x) or maze[chk_y][chk_x] == 1:
            leftwall = True

            ny = y + dy[dir]
            nx = x + dx[dir]

            if outbound(ny, nx) or maze[ny][nx] == 1:
                chk_y = ny
                chk_x = nx
                dir = rotate_right(dir)
            else:
                break

        # 왼쪽 벽이 뚫려 있으면 뚫려 있는 곳으로 향한다.
        if not leftwall:
            y = chk_y
            x = chk_x
            dir = rotate_left(dir)
        else:
            y = ny
            x = nx
        answer += 1

    return answer


answer = solution([[0, 1, 0, 1], [0, 1, 0, 0], [0, 0, 0, 0], [1, 0, 1, 0]])
print(answer)
answer = solution([[0, 1, 0, 0, 0, 0], [0, 1, 0, 1, 1, 0], [0, 1, 0, 0, 1, 0], [
                  0, 1, 1, 1, 1, 0], [0, 1, 0, 0, 0, 0], [0, 0, 0, 1, 1, 0]])
print(answer)
answer = solution([[0, 1, 0, 0, 0, 0], [0, 0, 1, 0, 0, 0], [0, 0, 0, 1, 0, 0], [
                  0, 0, 0, 0, 1, 0], [0, 0, 0, 0, 0, 0], [1, 1, 1, 1, 1, 0]])
print(answer)
answer = solution([[0, 0, 0, 0, 0, 0], [1, 1, 1, 0, 1, 1], [0, 0, 0, 0, 0, 0], [
                  1, 0, 1, 1, 1, 1], [0, 0, 0, 0, 0, 0], [1, 1, 0, 1, 1, 0]])
print(answer)
