import math
import sys

sys.setrecursionlimit(100000)


def solution(n, k, cmd):
    answer = ''
    """
    1. 커서 이동(위, 아래)
    step = querySeg(left, right)
    next_cur = cur + step
    
    2. 삭제
    remove_stack.append(cur)
    updateSeg(cur, 1)
    현재 커서 위치도 변경
    
    3. 복구(스택에 저장하는게 유리할듯)
    tmp = remove_stack.pop()
    updateSeg(tmp, 0)
    현재 커서 위치도 변경

    4. 모든 테이블 순회하면서 기록 빵야빵야

    어떤 자료구조로 표 저장?
    커서, 삭제 스택 
    
    [cur, cur + N] 사이에 몇 개가 삭제되었는지 알려면? 세그트리 
    
    """

    # 세그먼트 트리 초기화
    size = math.ceil(math.log(n)/math.log(2))
    tree = [0] * (1 << (size+2))

    def querySegTree(node_idx, first, last, query_start, query_end):
        if last < query_start or query_end < first:
            return 0
        if query_start <= first and last <= query_end:
            return tree[node_idx]
        mid = first + (last - first) // 2
        return querySegTree(node_idx*2 + 1, first, mid, query_start, query_end) + querySegTree(node_idx*2 + 2, mid+1, last, query_start, query_end)

    def updateSegTree(node_idx, first, last, idx, value):
        if idx < first or last < idx:
            return
        if first == last:
            tree[node_idx] = value
            return

        mid = first + (last - first) // 2
        updateSegTree(node_idx*2+1, first, mid, idx, value)
        updateSegTree(node_idx*2+2, mid+1, last, idx, value)
        tree[node_idx] = tree[node_idx*2+1] + tree[node_idx*2+2]

    def bisearchUP(cursor):
        first = cursor
        last = n-1
        res = n-1
        while first <= last:
            mid = (first + last) // 2
            # print(cursor, n-1, first, last, mid)
            # 삭제된 노드의 개수를 반환
            removed_cnt = querySegTree(0, 0, n-1, cursor, mid)
            # 삭제된 노드의 갯수가 cursor,mid까지 뺵뺵하게 있다면
            if removed_cnt == ((mid - cursor) + 1):
                first = mid + 1
            else:
                last = mid - 1
                if res > mid:
                    res = mid
        return res

    def bisearchDown(cursor):
        first = 0
        last = cursor
        res = 0
        while first <= last:
            mid = (first + last) // 2
            # print(cursor, n-1, first, last, mid)
            # 삭제된 노드의 개수를 반환
            removed_cnt = querySegTree(0, 0, n-1, mid, cursor)
            # 삭제된 노드의 갯수가 cursor,mid까지 뺵뺵하게 있다면
            if removed_cnt == ((cursor - mid) + 1):
                last = mid - 1
            else:
                first = mid + 1
                if res < mid:
                    res = mid
        return res

    table = [True] * (n+1)
    remove_stack = []
    cursor = k
    for cur_cmd in cmd:
        if cur_cmd[0] == 'D':
            step = int(cur_cmd.split()[1])
            jump = querySegTree(0, 0, n-1, cursor, cursor+step)
            cursor = cursor + step + jump
            cursor = bisearchUP(cursor)

        elif cur_cmd[0] == 'U':
            step = int(cur_cmd.split()[1])
            jump = querySegTree(0, 0, n-1, cursor-step, cursor)
            cursor = cursor - (step + jump)
            cursor = bisearchDown(cursor)

        elif cur_cmd[0] == 'C':
            remove_stack.append(cursor)
            updateSegTree(0, 0, n-1, cursor, 1)
            table[cursor] = False

            tmp = cursor
            cursor = bisearchUP(cursor)
            if cursor == tmp:
                cursor = bisearchDown(cursor)

        elif cur_cmd[0] == 'Z':
            remove_idx = remove_stack.pop()
            table[remove_idx] = True
            updateSegTree(0, 0, n-1, remove_idx, 0)
        print("커서 변경", cursor)

    for i in range(n):
        if table[i] == True:
            answer += 'O'
        else:
            answer += 'X'

    return answer


print(solution(8, 2, ["D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z"]))
print(solution(8, 2, ["D 2", "C", "U 3", "C",
                      "D 4", "C", "U 2", "Z", "Z", "U 1", "C"]))
