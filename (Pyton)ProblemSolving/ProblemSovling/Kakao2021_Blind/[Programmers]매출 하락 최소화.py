

def solution(sales, links):

    tree = [[] for _ in range(len(sales)+1)]
    cache = [[-1 for _ in range(2)] for _ in range(len(sales)+1)]

    # links에 주어진 조건대로 트리 구현
    # tree[node] = [children_idx, ...]
    for link in links:
        u, v = link
        tree[u].append(v)

    # sales가 10000 이하 정수이므로 DP를 하지 않으면 터지기 쉬움(?)
    # 빅오 계산은 어찌하지...? (나중에)
    # tree 순회(재귀)
    # DP로 계산하기 위해서는 상태를 정의해야 함
    # D[node, 0] : node(팀장)가 워크숍 참가할때, node 이하에 팀원들이 최소 매출 비용
    # D[node, 1] : node(팀장)가 워크숍 참가하지 않을 때, node 이하의 팀원들의 최소 매출 비용
    def calMinimumSale(node, is_join):
        # print(node, is_join)
        if cache[node][is_join] != -1:
            return cache[node][is_join]

        min_sales_cash = 0
        min_child_cash_gap = -1

        is_child = False
        for child in tree[node]:
            child_nojoin_sales_cash = calMinimumSale(child, False)
            child_join_sales_cash = calMinimumSale(child, True)

            if child_join_sales_cash <= child_nojoin_sales_cash:
                min_sales_cash += child_join_sales_cash
                is_child = True
            else:
                min_sales_cash += child_nojoin_sales_cash
                child_cash_gap = child_join_sales_cash - child_nojoin_sales_cash
                if min_child_cash_gap == -1 or min_child_cash_gap > child_cash_gap:
                    min_child_cash_gap = child_cash_gap

        if min_child_cash_gap == -1:
            min_child_cash_gap = 0

        if not is_join and not is_child:
            min_sales_cash += min_child_cash_gap

        cache[node][is_join] = min_sales_cash + \
            (sales[node-1] if is_join else 0)
        # print("[]", node, is_join, min_sales_cash,
        #   sales[node-1], cache[node][is_join])
        return cache[node][is_join]

    answer = min(calMinimumSale(1, False), calMinimumSale(1, True))
    # answer = calMinimumSale(1, False)

    return answer


print(solution([14, 17, 15, 18, 19, 14, 13, 16, 28, 17], [
      [10, 8], [1, 9], [9, 7], [5, 4], [1, 5], [5, 10], [10, 6], [1, 3], [10, 2]]))
print(solution([5, 6, 5, 3, 4], [[2, 3], [1, 4], [2, 5], [1, 2]]))
print(solution([5, 6, 5, 1, 4], [[2, 3], [1, 4], [2, 5], [1, 2]]))
print(solution([10, 10, 1, 1], [[3, 2], [4, 3], [1, 4]]))


def solution(sales, links):

    tree = [[] for _ in range(len(sales)+1)]
    cache = [[-1 for _ in range(2)] for _ in range(len(sales)+1)]

    # links에 주어진 조건대로 트리 구현
    # tree[node] = [children_idx, ...]
    for link in links:
        u, v = link
        tree[u].append(v)

    # sales가 10000 이하 정수이므로 DP를 하지 않으면 터지기 쉬움(?)
    # 빅오 계산은 어찌하지...? (나중에)
    # tree 순회(재귀)
    # DP로 계산하기 위해서는 상태를 정의해야 함
    # D[node, 0] : node(팀장)가 워크숍 참가할때, node 이하에 팀원들이 최소 매출 비용
    # D[node, 1] : node(팀장)가 워크숍 참가하지 않을 때, node 이하의 팀원들의 최소 매출 비용
    def calMinimumSale(node, is_join):
        # print(node, is_join)
        if cache[node][is_join] != -1:
            return cache[node][is_join]

        if is_join:
            min_sales_cash = 0
            for child in tree[node]:
                min_sales_cash += min(calMinimumSale(child, False),
                                      calMinimumSale(child, True))

        else:
            min_sales_cash = -1
            for join_child in tree[node]:
                sales_cash = 0
                for child in tree[node]:
                    if join_child == child:
                        sales_cash += calMinimumSale(child, True)
                    else:
                        sales_cash += min(calMinimumSale(child, False),
                                          calMinimumSale(child, True))
                if min_sales_cash == -1 or min_sales_cash > sales_cash:
                    min_sales_cash = sales_cash

        if min_sales_cash == -1:
            min_sales_cash = 0

        cache[node][is_join] = min_sales_cash + \
            (sales[node-1] if is_join else 0)
        return cache[node][is_join]

    answer = min(calMinimumSale(1, False), calMinimumSale(1, True))

    return answer
