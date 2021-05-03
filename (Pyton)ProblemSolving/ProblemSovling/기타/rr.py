# import collections

# tree = collections.defaultdict(int)
tree = dict()  # (parent, cash)


def updateTree(name, money):
    # if money < 10:
    #     tree[name][1] += money
    # else:
    tree[name][1] += money - (money // 10)
    parent = tree[name][0]
    if parent != "-":
        updateTree(parent, money // 10)


def solution(enroll, referral, seller, amount):
    answer = []
    for name in enroll:
        tree[name] = [0, 0]

    for idx, name in enumerate(referral):
        tree[enroll[idx]][0] = name

    for i in range(len(seller)):
        name = seller[i]
        money = amount[i]
        # print("start", name, money*100)
        updateTree(name, money*100)
        # for key, value in tree.items():
        #     print(key, value)
        # print()

    for key, value in tree.items():
        answer.append(value[1])

    return answer

# 트리는 만 개의 노드
# selle는 십만
# 재귀적으로 접근해서 풀어야 함

# 트리는 밑에서 부터 올라가야함


print(solution(["john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"], ["-", "-", "mary",
                                                                                      "edward", "mary", "mary", "jaimie", "edward"], ["young", "john", "tod", "emily", "mary"], [12, 4, 2, 5, 10]))
