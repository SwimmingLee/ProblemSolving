import sys
import heapq

input = sys.stdin.readline

N, M, K = list(map(int, input().split()))
fireballs = []
collision_fireballs = []
dyx = [[-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1]]


for _ in range(M):
    fireball = list(map(int, input().split()))
    fireballs.append(fireball)


def collide(collision_fireballs):
    global fireballs
    y, x = collision_fireballs[0][:2]
    collision_cnt = len(collision_fireballs)
    collision_mass, collision_vel = 0, 0
    direction = 0
    for fb in collision_fireballs:
        collision_mass += fb[2]
        collision_vel += fb[3]
        if collision_fireballs[0][4] % 2 != fb[4] % 2:
            direction = 1

    mass = collision_mass // 5
    if mass == 0:
        return

    vel = collision_vel // collision_cnt

    for i in range(4):
        fireballs.append([y, x, mass, vel, direction])
        direction += 2


def pujigi():
    global fireballs
    global collision_fireballs
    """ """

    new_fireballs = []
    n_fireball = len(fireballs)

    # 파이어볼 이동
    while fireballs:
        fireball = fireballs.pop()
        y, x, m, s, d = fireball
        ny = y + dyx[d][0]*s
        ny = ny if 1 <= ny <= N else (ny-1) % N + 1
        """ """
        nx = x + dyx[d][1]*s
        nx = nx if 1 <= nx <= N else (nx-1) % N + 1
        """ """
        heapq.heappush(new_fireballs, [ny, nx, m, s, d])

    # 파이어볼 충돌
    if new_fireballs:
        """"""
        prev = heapq.heappop(new_fireballs)
        collision_fireballs = [prev]

    while new_fireballs:
        cur = heapq.heappop(new_fireballs)

        if prev[0] == cur[0] and prev[1] == cur[1]:

            collision_fireballs.append(cur)
        else:
            # 충돌이 났으면 충돌 처리
            if len(collision_fireballs) > 1:
                collide(collision_fireballs)
            # 충돌이 안나면 그냥 fireball에 넣어주면 된다.
            else:
                fireballs.append(prev)
            prev = cur
            collision_fireballs = [cur]

    # 끝 예외처리
    if len(collision_fireballs) > 1:
        """"""
        collide(collision_fireballs)
    elif M > 0:
        """"""
        fireballs.append(prev)


for _ in range(K):
    pujigi()

answer = 0
for fb in fireballs:
    answer += fb[2]
print(answer)
