

def solution(enter, leave):
    room = set()
    visited = [[0] * (len(enter)+1) for _ in range(len(enter)+1)]
    visited_map = [[True] * (len(enter)+1) for _ in range(len(enter)+1)]
    answer = [-1] * len(enter)
    # print(visited)

    def solve(i, j):
        if j == len(enter):
            for i in range(1, len(enter)+1):
                for j in range(1, len(enter)+1):
                    visited_map[i][j] &= visited[i][j]
            return

        # print(i, j, room)
        if leave[j] in room:
            room.remove(leave[j])
            solve(i, j+1)
            room.add(leave[j])

        if i != len(enter):
            for man in room:
                visited[man][enter[i]] += 1
                visited[enter[i]][man] += 1
            # print("시작 전", i, j, room)
            room.add(enter[i])
            solve(i+1, j)
            room.remove(enter[i])
            # print("시작 후", i, j, room)
            for man in room:
                visited[man][enter[i]] -= 1
                visited[enter[i]][man] -= 1
    solve(0, 0)

    for i in range(1, len(enter)+1):
        visited_num = 0
        for j in range(1, len(enter)+1):
            if visited_map[i][j] == 1:
                visited_num += 1
        answer[i-1] = visited_num
    return answer


print(solution([1, 3, 2], [1, 2, 3]))
print(solution([1, 4, 2, 3], [2, 1, 3, 4]))
print(solution([3, 2, 1], [2, 1, 3]))
print(solution([3, 2, 1], [1, 3, 2]))
print(solution([1, 4, 2, 3], [2, 1, 4, 3]))
