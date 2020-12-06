import sys

input = sys.stdin.readline
n_people = int(input())
people_synergy = [0 for _ in range(n_people)]
for i in range(n_people):
    people_synergy[i] = list(map(int, input().split()))

# 인원을 어떻게 분리할지 완전탐색으로 분석하는 것이 좋아보인다. 
# 완전탐색을 돌릴때 스타드/링크 두 개로 분류되므로 하나의 그룹만 선택하면 나머지는 자동으로 타 그룹으로 선별되게 된다. 
# 즉 N명의 인원이 있으면 N/2명만 NCN/2만 하면된는 것이다. 생각을 해본게 어차피 모든 그룹이 다 뽑일 것이라고 생각이 든다. 중복이 발생한다. 나머지를 찾으면 2배만큼 일을 더하게 된다. 

start = []
link = []
answer = -1;
def dfs(index):
    global answer
    if len(start) > n_people//2 or len(link) > n_people//2:
        return

    if index == n_people:
        start_score, link_score = 0, 0
        for i in range(n_people//2):
            for j in range(i+1, n_people//2):
                u, v = start[i], start[j]
                start_score += people_synergy[u][v]
                start_score += people_synergy[v][u] 

                u, v = link[i], link[j]
                link_score += people_synergy[u][v] 
                link_score += people_synergy[v][u] 
                
        tmp = abs(start_score -  link_score)
        if answer == -1 or tmp < answer:
            answer = tmp
        return

    start.append(index)
    dfs(index+1)
    start.pop()

    link.append(index)
    dfs(index+1)
    link.pop()

dfs(0)
print(answer)