def solution(enter, leave):
    answer = []
    N = len(enter)
    visited_person = [[] for _ in range(N+1)]

    for i in range(1, N+1):
        # i 사람보다 먼저 들어온 사람/ 늦게 들어온 사람 그룹 분할
        first_enter, last_enter = [], []
        enter_idx = 0
        for j in range(N):
            if i == enter[j]:
                enter_idx = j
                first_enter = enter[:j]
                last_enter = enter[j+1:]
                break

        # i 사람보다 먼저 나간 사람 / 늦게 나간 살마 그룹 분할
        first_leave, last_leave = [], []
        leave_idx = 0
        for j in range(N):
            if i == leave[j]:
                leave_idx = j
                first_leave = leave[:j]
                last_leave = leave[j+1:]
                break

        cnt = 0
        for u in last_leave:
            if u in first_enter:
                if not u in visited_person[i]:
                    visited_person[i].append(u)
                if not i in visited_person[u]:
                    visited_person[u].append(i)
                # u_enter = False
                # for j in range(leave_idx+1, N):
                #     if leave[j] in first_leave:
                #         continue
                #     if not leave[j] in visited_person[i]:
                #             visited_person[i].append(leave[j])
                #     if leave[j] == u:
                #         break

                # if not i in visited_person[u]:
                #     visited_person[u].append(i)

        for u in last_enter:
            if u in first_leave:
                # if not u in visited_person[i]:
                #     visited_person[i].append(u)

                u_leave = False
                for j in range(enter_idx+1, N):
                    if not enter[j] in visited_person[i]:
                        visited_person[i].append(enter[j])
                    if not i in visited_person[enter[j]]:
                        visited_person[enter[j]].append(i)
                    if enter[j] == u:
                        break
                # if not i in visited_person[u]:
                #     visited_person[u].append(i)

    for i in range(1, N+1):
        answer.append(len(visited_person[i]))

    return answer


answer = solution([1, 3, 2], [1, 2, 3])
print(answer)
