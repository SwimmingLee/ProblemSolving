import heapq


def solution(n, z, roads, queries):
    answer = []
    """
    쿼리에 나올 수 있는 숫자가 최대 10^18이므로 
    BFS로 모두 탐색하려고 하면 당연히 시간이 터질 것이다

    위치0, 돈0에서 시작하는 것 맞다
    그리고 거기서 갈 수 있는 곳으로 가는 것도 맞다. 
    모든 경우를 다하려고 하면 당연히 시간이 터질 것이다. 
    """
    return answer


# [0, 1,2,3,4,5,6]
# [0,-1,1,2,3,1,4]
