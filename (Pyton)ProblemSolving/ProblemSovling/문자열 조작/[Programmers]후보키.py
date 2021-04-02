
combination = 0
candidates = []
answer = 0


def checkCandiateKey(combination, relation):
    candidate_set = set()
    for i in range(len(relation)):
        tuple_str = ""
        for j in range(8):
            if (1 << j) & combination:
                tuple_str += relation[i][j] + "_"
        if tuple_str in candidate_set:
            return False
        candidate_set.add(tuple_str)
    return True


def dfs(relation, N, M, idx, start):
    global combination, answer
    if idx >= M:
        for candidate in candidates:
            if (combination & candidate) == candidate:
                return
        res = checkCandiateKey(combination, relation)
        if res:
            candidates.append(combination)
            answer += 1
        return

    for i in range(start, N):
        combination |= (1 << i)
        dfs(relation, N, M, idx+1, i+1)
        combination &= ~(1 << i)


def solution(relation):
    row = len(relation)
    column = len(relation[0])

    for i in range(1, column+1):
        dfs(relation, column, i, 0, 0)

    return answer


solution([["100", "ryan", "music", "2"], ["200", "apeach", "math", "2"], ["300", "tube", "computer", "3"], [
         "400", "con", "computer", "4"], ["500", "muzi", "music", "3"], ["600", "apeach", "music", "2"]])

print(answer)
