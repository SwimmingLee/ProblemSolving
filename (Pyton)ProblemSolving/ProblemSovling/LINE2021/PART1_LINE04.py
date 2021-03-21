def get_score(name, word):
    score = 0
    search_idx = 0

    while True:
        next_idx = name[search_idx:].find(word)
        if next_idx == -1:
            break
        search_idx += next_idx + len(word)
        score += 1

    return score


def get_string(i):


def solution(data, word):
    answer = []
    doll = [[] for in range(len(data)+1)]
    ind = [[0] for in range(len(data)+1)]

    for d in data:
        idx, name, parent_idx = d.split()
        doll[idx] = [name, parent_idx]
        ind[parent_idx] += 1

    max_score = 0
    for i in range(1, len(data)+1):
        if ind[i] != 0:
            score = get_score(doll[i][0], word)
            if score > max_score:
                answer = []
                string = get_string(doll[i])

    return answer
